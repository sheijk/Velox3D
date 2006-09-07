/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VFileDataProvider.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/VFS/IVAccessRights.h>
#include <v3d/VFS/VIOException.h>

#include <V3d/VFS/IVFileSystem.h>
#include "VAccessRights.h"
#include "VFile.h"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/exception.hpp>

#include <fstream>
#include <boost/filesystem/path.hpp>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------
namespace fs = boost::filesystem;

//TODO: clean this mess up
// defined in VSimpleVfs.cpp
extern boost::filesystem::path s_WorkingDir;

IVStreamFactory* VFileDataProvider::s_pStreamFact = 0;

/**
 * standard c'tor
 */
VFileDataProvider::VFileDataProvider()
{
	m_strType = "localfs";

	//TODO: move reg. from ...DLL.cpp here
	// register at data provider pool
}

/**
 * d'tor
 */
VFileDataProvider::~VFileDataProvider()
{
}

/**
 * Returns the vfs's stream factory. If pointer to it is not yet in
 * cache (s_pStreamFact), it is retrieved
 */
IVStreamFactory* VFileDataProvider::GetStreamFactory()
{
	if( s_pStreamFact == 0 )
	{
		s_pStreamFact = QueryObject<IVStreamFactory>("vfs.strfact");
	}

	return s_pStreamFact;
}

VStringRetVal VFileDataProvider::GetId() const
{
	return VStringRetVal(m_strType.c_str());
}

IVDataProvider::StreamPtr VFileDataProvider::OpenFile(
	VStringParam in_strSource, VAccessModeFlags in_Access)
{
	return GetStreamFactory()->CreateFileStream(
		in_strSource, 
		VOpenExisting, 
		in_Access);
}

IVDataProvider::DirPtr VFileDataProvider::CreateMountedDir(
	IVDirectory* in_pParent,
	const VMountOptions& in_MountOptions)
{
	using namespace boost::filesystem;

	path sourcePath;

	try {
		sourcePath = s_WorkingDir;
		sourcePath /= in_MountOptions.GetSource().AsCString();
	}
	catch(const boost::filesystem::filesystem_error& e) {
		std::string msg = e.what();
	}

	VDirectory* pDirectory = new VDirectory(
		in_pParent,
		in_MountOptions.GetName().AsCString(), 
		in_MountOptions.GetType().AsCString(),
		//in_MountOptions.GetSource().AsCString(),
		sourcePath.string(),
		in_MountOptions.GetAccessRights());

	DirPtr pDirAP(pDirectory);

	// add files and directories to dir
	AddDirContent(
		*pDirectory, 
		//in_MountOptions.GetSource().AsCString(),
		sourcePath,
		in_MountOptions.GetAccessRights());

	return pDirAP;
}

/**
 * Adds the content of a (real) directory to the VDirectory. (subdirectories
 * are initially emtpy, fill them with VFileDataProvider::Update, they should
 * do this themselfes on demand)
 */
void VFileDataProvider::AddDirContent(
	VDirectory& io_Dir, 
	fs::path in_Dir,
	VDirectory::SharedAccessRightsPtr in_pAR)
{
	//TODO: bessere Angabe der Zugriffsrechte

	// check if dir is a directory
	if( fs::exists(in_Dir) && fs::is_directory(in_Dir) )
	{
		const fs::directory_iterator dirEnd;
		fs::directory_iterator dirIt(in_Dir);

		VFile::SharedAccessRightsPtr pFileAccRights( 
			VAccessRights::CreateFileAR(
				GetAccMode(*in_pAR), 
				GetDelMode(in_pAR->AllowDelete())) );

		// add content of current dir
		for( ; dirIt != dirEnd; ++dirIt )
		{
			// iter points to a directory
			if( fs::is_directory(*dirIt) )
			{
				// create virtual subdir
				VDirectory* pDir = new VDirectory(
					&io_Dir,
					(*dirIt).leaf(),
					m_strType,
					(*dirIt).string(),
					in_pAR);
				
				// enter dir and add it's content
				//AddDirContent(*pDir, *dirIt, in_pAR);

				// add it to current dir
				io_Dir.AddSubdir(VDirectory::DirPtr(pDir));
			}
			// iter points to a file
			else
			{
				// add file
				VFile::CreationInfo fileOpt;
				fileOpt.name = dirIt->leaf();
				fileOpt.type = "localfs";
				fileOpt.source = dirIt->string();
				fileOpt.pAccRights = pFileAccRights;

				io_Dir.AddFile(VDirectory::FilePtr(new VFile(fileOpt)));
			}
		}
	}
	//TODO: exception filesystem_error abfangen statt man. pruefung?
	else
	{
		V3D_THROW(VElementNotFoundException, std::string(
			"could not find file \""
			+ in_Dir.string() + "\"").c_str());
	}
}

IVDataProvider::DirPtr VFileDataProvider::CreateDir(
	const VMountOptions& in_Options)
{
	V3D_THROW(VException, "not implemented, yet");

	//// build the path + dirname
	////TODO: auf "\" am ende pruefen
	//fs::path dirPath(in_Options.GetSource() + "/" + in_Options.GetName().AsCString());

	//// create the dir
	//try
	//{
	//	fs::create_directory(dirPath);
	//}
	//catch(fs::filesystem_error&)
	//{
	//	V3D_THROW(VElementNotFoundException, std::string(
	//		"could not create directory \""
	//		+ dirPath.string() + "\"").c_str() );
	//}

	//// create an IVDirectory representing it
	//DirPtr pDir(new VDirectory(
	//	dirPath.leaf(),
	//	"localfs",
	//	dirPath.string(),
	//	in_Options.GetAccessRights()
	//	));

	//// return it
	//return pDir;
}

void VFileDataProvider::DeleteDir(VStringParam in_strDir)
{
	try
	{
		// remove dir
		fs::remove( fs::path(in_strDir) );
	}
	catch(fs::filesystem_error&)
	{
		V3D_THROW(VIOException, 
			"unknown error occured, please correct function");
	}
}

void CreateEmptyFile(const std::string& filePathName)
{
	std::ofstream file(filePathName.c_str());
}

IVDataProvider::FilePtr VFileDataProvider::CreateFile(
	const VMountOptions& in_Options)
{
	// build full path and name
	fs::path pathAndName(
		in_Options.GetSource() + "/" + in_Options.GetName().AsCString());

	if( fs::exists(pathAndName) )
		V3D_THROW(VIOException, "file already exists");

	try
	{
		// create the file
		CreateEmptyFile(pathAndName.string());

		// create a file object representing it
		VFile::CreationInfo fileInfo;
		fileInfo.name = in_Options.GetName().AsCString();
		fileInfo.source = pathAndName.string().c_str();
		fileInfo.type = in_Options.GetType().AsCString();
		fileInfo.pAccRights = in_Options.GetAccessRights();
		
		VFile* pFile = new VFile(fileInfo);
		return FilePtr(pFile);
	}
	catch(fs::filesystem_error&)
	{
		V3D_THROW(VIOException, "eehm.. this should never happen");
	}
}

void VFileDataProvider::DeleteFile(VStringParam in_strSource)
{
	// delete file
	try
	{
		fs::remove(fs::path(in_strSource));
	}
	catch(fs::filesystem_error&)
	{
		V3D_THROW(VIOException, "this should never happen");
	}
}

vbool VFileDataProvider::IsDirectory(VStringParam in_strPossibleDir)
{
	fs::path dirPath(s_WorkingDir);
	dirPath /= in_strPossibleDir;
	//fs::path dirPath(in_strPossibleDir);

	if( fs::exists(dirPath) && fs::is_directory(dirPath) )
		return true;
	else
		return false;
}

vbool VFileDataProvider::IsFile(VStringParam in_strPossibleFile)
{
	fs::path filePath(s_WorkingDir);
	filePath /= in_strPossibleFile;
	//fs::path filePath(in_strPossibleFile);

	if( fs::exists(filePath) && ! fs::is_directory(filePath) )
		return true;
	else
		return false;
}

void VFileDataProvider::UpdateDir(const std::string& path, VDirectory* io_pDir)
{
	try
	{
		if( boost::filesystem::exists(fs::path(path, fs::native)) )
		{
			AddDirContent(
				*io_pDir, 
				fs::path(path, fs::native), 
				SharedPtr(new VAccessRights(*io_pDir->GetAccessRights())));
		}
	}
	catch(fs::filesystem_error& e)
	{
		V3D_THROW(VIOException, e.what());
	}
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

