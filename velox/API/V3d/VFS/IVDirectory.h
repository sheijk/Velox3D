/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVDirectory_H
#define V3D_IVDirectory_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>
#include <V3d/VFS/IVFileSysObject.h>
#include <V3d/VFS/IVFile.h>
#include <V3d/VFS/VAccessRightsFlags.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Represents a directory. Use it to access sub dirs, files, 
 * create and delete files and subdirs
 */
class IVDirectory : public IVFileSystemObject
{
public:
	//TODO: documentation
	virtual ~IVDirectory() {};

	typedef VRangeIterator<IVDirectory> DirIter;
	typedef VRangeIterator<IVFile> FileIter;

	typedef VRangeIterator<const IVDirectory> ConstDirIter;
	typedef VRangeIterator<const IVFile> ConstFileIter;

	/** get sub directory iterators */
	virtual DirIter SubDirs() = 0;
	virtual ConstDirIter SubDirs() const = 0;

	/** get file iterators */
	virtual FileIter Files() = 0;
	virtual ConstFileIter Files() const = 0;

	// Create/Delete File/Dir
	/** create a sub directory */
	virtual IVDirectory& CreateSubdir(
		VStringParam in_strName,
		const VAccessRightsFlags& in_AccessRights) = 0;

	/** delete a subdirectory */
	virtual void DeleteSubdir(VStringParam in_strName) = 0;

	/** create a file */
	virtual void CreateFile(
		VStringParam in_strName,
		const VAccessRightsFlags& in_AccessRights) = 0;

	/** delete file */
	virtual void DeleteFile(VStringParam in_strName) = 0;

	virtual IVDirectory* GetParent() = 0;
	virtual const IVDirectory* GetParent() const = 0;

	virtual std::string GetQualifiedName() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDirectory_H

