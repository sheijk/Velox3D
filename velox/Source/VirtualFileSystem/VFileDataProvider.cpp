#include "VFileDataProvider.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/VFS/IVAccessRights.h>

#include "VFile.h"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------
namespace fs = boost::filesystem;


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
	const VMountOptions& in_MountOptions)
{
	VDirectory* pDirectory = new VDirectory(
		in_MountOptions.GetName().AsCString(), "");
	DirPtr pDirAP(pDirectory);

	// add files and directories to dir
	AddDirContent(*pDirectory, in_MountOptions.GetSource().AsCString());

	return pDirAP;
}

/**
 * Adds the content of a (real) directory to the VDirectory. Recursively
 * loads all subdirectories
 */
void VFileDataProvider::AddDirContent(VDirectory& io_Dir, fs::path in_Dir)
{
	const fs::directory_iterator dirEnd;
	fs::directory_iterator dirIt(in_Dir);

	// add content of current dir
	for( ; dirIt != dirEnd; ++dirIt )
	{
		// iter points to a directory
		if( fs::is_directory(*dirIt) )
		{
			// create virtual subdir
			VDirectory* pDir = new VDirectory((*dirIt).leaf(), "");
			
			// enter dir and add it's content
			AddDirContent(*pDir, *dirIt);

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

			io_Dir.AddFile(VDirectory::FilePtr(new VFile(fileOpt)));
		}
	}
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
