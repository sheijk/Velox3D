#include "VSimpleVfs.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>

#include <v3d/VFS/IVStreamFactory.h>
#include <v3d/VFS/IVAccessRights.h>
#include <v3d/VFS/VIOException.h>
#include <v3d/VFS/IVDataProviderPool.h>
#include <v3d/VFS/VMountOptions.h>

#include <v3d/XML/IVXMLService.h>

#include "VFile.h"
#include "VDirectory.h"
#include "VAccessRights.h"
#include "VfsUtils.h"
#include "VxmlIniReader.h"

#include <algorithm>
#include <string>

#include <boost/filesystem/operations.hpp>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

IVDataProvider& GetDataProvider(std::string in_strId)
{
	//TODO: make static member and cache data prov. pool

	IVDataProviderPool* pDPP = QueryObject<IVDataProviderPool>("vfs.dpp");

	return pDPP->GetDataProvider(in_strId.c_str());
}

/**
 * standard c'tor
 */
VSimpleVfs::VSimpleVfs(
					   VStringParam in_strName, 
					   VStringParam in_strCfgFile,
					   VNamedObject* in_pParent)
	: IVFileSystem(in_strName, in_pParent)
{
	// create root dir
	m_pRootDir = new VDirectory(
		"",
		"",
		boost::filesystem::current_path().string(),
		VAccessRights::CreateRODirAR(VAccessRights::DeletingForbidden));
	m_pRootDirSP.Assign(m_pRootDir);

	// create some dirs/files for testing:

	// add some files
	//m_pRootDir->AddFile(VDirectory::FilePtr(new VFile("manual.file")));
	//m_pRootDir->AddFile(VDirectory::FilePtr(new VFile("another.file.here")));
	//VDirectory* pDir(new VDirectory("a.dir", ""));
	//pDir->AddFile(VDirectory::FilePtr(new VFile("nested.file")));
	//pDir->AddFile(VDirectory::FilePtr(new VFile("2nd.nested.file")));
	//m_pRootDir->AddSubdir(VDirectory::DirPtr(pDir));


	// mount a (real) directory:

	// set mount options
	VMountOptions mountOpt(
		"mount'd.dir", 
		"vfstestdir", 
		"", 
		"localfs", 
		VAccessRights::CreateDirAR(VAccessRights::DeletingForbidden)
		);

	// get localfs data provider and let it create a mounted dir
	// add dir to vfs dir structure
	//m_pRootDir->AddSubdir(
	//	GetDataProvider("localfs").CreateMountedDir(mountOpt)
	//	);

	// load vfs.xml file
	ParseInitFile();
}

void VSimpleVfs::ParseInitFile()
{
	// create visitor
	VXmlIniReader reader(m_pRootDir);
	
	// get xml service
	xml::IVXMLService* pXmlServ = QueryObject<xml::IVXMLService>("xml.service");

	// let it parse the ini file
	pXmlServ->ParseLocalXMLFile("vfs.xml", &reader);
}

/**
 * d'tor
 */
VSimpleVfs::~VSimpleVfs()
{
}

IVFileSystem::FileStreamPtr VSimpleVfs::OpenFile(
	VStringParam in_strPathAndName,
	VAccessModeFlags in_Access)
{
	IVDirectory* pDir;
	
	// get dir
	pDir = GetDir(in_strPathAndName);

	// get file
	std::string strPathAndName = in_strPathAndName;
	std::string strFileName;
	strFileName.assign(
		std::find(strPathAndName.rbegin(), strPathAndName.rend(), '/').base(),
		strPathAndName.end() );

	// open it
	VDirectory::FileIter fileIter = std::find_if(
		pDir->Files().Begin, pDir->Files().End, VCompareFSOName(strFileName));

	if( fileIter == pDir->Files().End )
	{
		std::string errorMsg = "file \"";
		errorMsg += strFileName;
		errorMsg += "\" does not exist";

		V3D_THROW(VIOException, errorMsg.c_str());
	}

	IVFile::FileStreamPtr pFileStream = fileIter->Open(in_Access);

	return pFileStream;
}

//TODO: testen

IVDirectory* VSimpleVfs::GetDir(VStringParam in_strDir)
{
	if( in_strDir[0] != '/' )
	{
		V3D_THROW(VIOException, "paths must start with '/', \""
			+ VString(in_strDir) + "\" is illegal"
			);
	}

	IVDirectory* pCurrDir = m_pRootDirSP.Get();

	std::string pathAndName = in_strDir;
	std::string::iterator pos = pathAndName.begin();
	std::string::iterator substrEnd = pos;
	const std::string::iterator end(pathAndName.end());
	std::string currDirName = "/";
	std::string fileName;

	while((substrEnd = std::find(++pos, end, '/')) != end)
	{		
		// get current dir name
		currDirName.assign(pos, substrEnd);

		// find it in current directory
		VDirectory::DirIter nextDir = pCurrDir->SubDirs().Begin;
		VDirectory* tmp = (VDirectory*)&(*nextDir);
		VCompareFSOName fsoCmp(currDirName);
		while( nextDir != pCurrDir->SubDirs().End )
		{
            if( fsoCmp(*nextDir) ) break;
			++nextDir;
		}

		//VDirectory::DirIter nextDir = std::find_if(
		//	pCurrDir->SubDirs().Begin, pCurrDir->SubDirs().End, 
		//	VCompareFSOName(currDirName));

		if(nextDir == pCurrDir->SubDirs().End)
		{
			V3D_THROW(VIOException, "could not find directory \"" 
				+ VString(currDirName.c_str()) + "\"");
		}

		pCurrDir = &(*nextDir);

		pos = substrEnd;
	}

	fileName.assign(pos, substrEnd);

	// return dir
	return pCurrDir;
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
