#include "VFileSysTest.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <v3d/VFS/IVFileSystem.h>
#include <v3d/VFS/IVDirectory.h>
#include <v3d/VFS/IVFile.h>
#include <v3d/VFS/VIOException.h>
#include <v3d/VFS/VAccessRightsFlags.h>
#include <v3d/VFS/IVAccessRights.h>

#include <iostream>
#include <algorithm>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------
using namespace std;
using namespace v3d::vfs;

VFileSysTest::VFileSysTest()
{
	IVTestManager* pTestManager = 0;

	// register unit test
	pTestManager = QueryObject<IVTestManager>("testmngr");

	if( ! pTestManager ) 
	{
		V3D_THROW(VException, "test manager could not be found");
	}

	pTestManager->AddCommonTest(this);
}

VFileSysTest::~VFileSysTest()
{
}

void VFileSysTest::GetTestInfo(
	VString& out_TestName, 
	VString& out_SubjectName)
{
	// set the name
	out_TestName = "VFileSysTest";

	// specifiy the subject of the whole thing
	out_SubjectName = "IVFileSystem";
}

std::string GetARInfo(const IVAccessRights* pAR)
{
	std::string res = "-----";

	if( pAR->AllowReadAccess() ) res[0] = 'r';
	if( pAR->AllowWriteAccess() ) res[1] = 'w';
	if( pAR->AllowDelete() ) res[2] = 'x';
	if( pAR->AllowCreateDir() ) res[3] = 'd';
	if( pAR->AllowCreateFile() ) res[4] = 'f';

	return res;
}

void PrintDirInfo(const IVDirectory& in_Dir, vuint in_prefWS)
{
	// construct info:
	// preceding whitespace
	std::string strOut(in_prefWS, ' ');

	// name
	strOut += in_Dir.GetName().AsCString();
	strOut += '/';

	// access rights

	// output info
	cout << "[" << GetARInfo(in_Dir.GetAccessRights()) << "]" << strOut << "\n";
}

void PrintFileInfo(const IVFile& in_File, vuint in_prefWS)
{
	// construct string:
	// preceding whitespace
	string strOut(in_prefWS, ' ');

	// name
	strOut += in_File.GetName();

	// access rights
	
	// output info
	cout << "[" << GetARInfo(in_File.GetAccessRights()) << "]" << strOut << "\n";
}

template<typename T>
class VInfoPrinter
{
public:
	typedef void (*InfoPrintFunc)(const T&, vuint);

private:
	vuint m_nIndent;
	InfoPrintFunc m_pInfoPrintFunc;

public:
	VInfoPrinter(vuint in_nIndent, InfoPrintFunc in_pInfoPrintFunc) 
		: m_nIndent(in_nIndent), m_pInfoPrintFunc(in_pInfoPrintFunc)
	{};

	void operator()(const T& in_Dir)
	{
		m_pInfoPrintFunc(in_Dir, m_nIndent);
	}
};

void PrintDirContent(const IVDirectory& in_Dir, vuint in_prefWS)
{
	// print dir info
	PrintDirInfo(in_Dir, in_prefWS);

	// for all dirs print out their info, indented
	for_each(
		in_Dir.SubDirs().Begin, 
		in_Dir.SubDirs().End, 
		VInfoPrinter<IVDirectory>(in_prefWS + 2, &PrintDirContent) );

	// for all files print out info
	for_each(
		in_Dir.Files().Begin, in_Dir.Files().End,
		VInfoPrinter<IVFile>(in_prefWS + 2, &PrintFileInfo) );
}

void OutputFSDirStructure()
{
	vuint fileCount = 0;
	vuint dirCount = 0;
	
	// used to easily be able output somewhere else
	ostream& out = cout;

	// print header
	out << "--------------------------------------------------\n";
	out << "Virtual File System Structure:                    \n\n";

	// print dir structure:
	try
	{
		// get root dir
		IVFileSystem* pFS = QueryObject<IVFileSystem>("vfs.fs");
		IVDirectory* pRootDir = pFS->GetDir();

		// print content
		PrintDirContent(*pRootDir, 0);
	}
	catch(VException e)
	{
		V3D_UNITTEST_ERROR_STATIC(e.GetErrorString());
	}

	// print footer
	out << "--------------------------------------------------\n";
	out << fileCount << " files in " << dirCount << " dirs" << endl;
}

void CheckStreamContent(
	IVStream& in_Stream, 
	const vchar* in_pContent, 
	vint in_nMaxSize)
{
	vchar testChar;
	vuint readPos = 0;
	in_Stream.SetPos(IVStream::Begin, 0);

	while(readPos < in_nMaxSize && in_Stream.Read(&testChar, 1) == 1)
	{
		cout << in_pContent[readPos];

		if( testChar != in_pContent[readPos++] )
		{
			V3D_UNITTEST_ERROR_STATIC("Stream had wrong content");
		}
	}

	cout << endl;
}

void CheckTestFile()
{
	// get vfs
	IVFileSystem* pFS = QueryObject<IVFileSystem>("vfs.fs");

	// open file directly and test it
	IVFileSystem::FileStreamPtr pFileStream = 
		pFS->OpenFile("/mount'd.dir/testfile.txt", VReadAccess);

	pFileStream.Release();
	pFileStream = pFS->OpenFile("/mount'd.dir/testfile.txt", VReadAccess);

	vchar expectedFileContent[] = "Dies ist ein Textfile";

	CheckStreamContent(
		*pFileStream, expectedFileContent, 
		strlen(expectedFileContent));
}

void CheckAccessRights()
{
	// open file for reading
	IVFileSystem::FileStreamPtr pFileStream
		= QueryObject<IVFileSystem>("vfs.fs")
		->OpenFile("/mount'd.dir/testfile.txt", VReadAccess);

	vchar testString[] = "lalala";

	try
	{
		pFileStream->Write(testString, 4);

		V3D_UNITTEST_ERROR_STATIC("could write to read-only file");
	}
	catch(VIllegalOperationException e)
	{
		// ok, this should happen
	}
	catch(...)
	{
		V3D_UNITTEST_ERROR_STATIC("unknown error occured when trying to "
			"write to read-only stream. VIllegalOperationException expected");
	}
}

void CheckCreateDelete()
{
	//TODO: delete dir.. :)

	VAccessRightsFlags accFlags;

	// create a dir
	IVFileSystem* pFS = QueryObject<IVFileSystem>("vfs.fs");

	IVDirectory* pDir = pFS->GetDir("/mount'd.dir/");

	pDir->CreateSubdir("testCreateDir", accFlags);
	
	// check whether it exists

	OutputFSDirStructure();

	// delete it
	pDir->DeleteSubdir("testCreateDir");

	// check if it's gone

	// create file
	accFlags.allowCreateDir = false;
	accFlags.allowCreateFile = false;

	pDir->CreateFile("createTest.file", accFlags);

	OutputFSDirStructure();

	// delete file
	pDir->DeleteFile("createTest.file");

	OutputFSDirStructure();
}

void VFileSysTest::ExecuteTest()
{
	// output all mounted files and dirs
	OutputFSDirStructure();

	//TODO: test file mounting

	// read test file
	CheckTestFile();
	CheckAccessRights();
	CheckCreateDelete();
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
