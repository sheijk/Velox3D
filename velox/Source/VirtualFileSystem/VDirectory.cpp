#include "VDirectory.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/VFS/IVAccessRights.h>
#include <v3d/Core/Wrappers/VSTLDerefIteratorPol.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VDirectory::VDirectory()
{
}

VDirectory::VDirectory(
	std::string in_strName, 
	SharedAccessRightsPtr in_pAccessRights)
{
	m_strName = in_strName;

	m_pAccessRights = in_pAccessRights;
}

/**
 * d'tor
 */
VDirectory::~VDirectory()
{
}

VStringRetVal VDirectory::GetName() const
{
	return VStringRetVal(m_strName.c_str());
}

VStringRetVal VDirectory::GetPath() const
{
	return VStringRetVal(m_strPath.c_str());
}

IVFileSystemObject::AccessRightsPtr VDirectory::GetAccessRights() const
{
	return m_pAccessRights.Get();
}

IVDirectory::DirIterRange VDirectory::SubDirs()
{
	typedef VSTLDerefIteratorPol<DirList::iterator, IVDirectory> DirIterPol;

	return DirIterRange(
		DirIter(new DirIterPol(m_Dirs.begin())),
		DirIter(new DirIterPol(m_Dirs.end())) );
}

IVDirectory::ConstDirIterRange VDirectory::SubDirs() const
{
	typedef VSTLDerefIteratorPol<
		DirList::const_iterator, 
		const IVDirectory
	> DirIterPol;

	return ConstDirIterRange(
		ConstDirIter(new DirIterPol(m_Dirs.begin())),
		ConstDirIter(new DirIterPol(m_Dirs.end())) );
}

IVDirectory::FileIterRange VDirectory::Files()
{
	typedef VSTLDerefIteratorPol<FileList::iterator, IVFile> FileIterPol;

	return FileIterRange(
		FileIter(new FileIterPol(m_Files.begin())),
		FileIter(new FileIterPol(m_Files.end())) );
}

IVDirectory::ConstFileIterRange VDirectory::Files() const
{
	typedef VSTLDerefIteratorPol<
		FileList::const_iterator, 
		const IVFile
	> FileIterPol;

	return ConstFileIterRange(
		ConstFileIter(new FileIterPol(m_Files.begin())),
		ConstFileIter(new FileIterPol(m_Files.end())) );
}

void VDirectory::AddSubdir(DirPtr in_pSubdir)
{
	m_Dirs.push_back(in_pSubdir);
}

void VDirectory::AddFile(FilePtr in_pFile)
{
	m_Files.push_back(in_pFile);
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
