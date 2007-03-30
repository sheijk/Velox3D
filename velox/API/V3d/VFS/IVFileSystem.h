/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVFILESYSTEM_H
#define V3D_IVFILESYSTEM_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VNamedObject.h>
#include <V3d/Core/SmartPtr/VGuards.h>
#include <V3d/VFS/VFlags.h>
#include <V3d/VFS/IVBufferStream.h>
#include <V3d/VFS/IVDirectory.h>
#include <V3d/VFS/IVFile.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Virtual File System
 * - mount and unmount data
 * - open files
 * - access a virtual directory structure
 *
 * Deprecated: use the resource system instead
 * fileStream = GetResourceData<IVFileStream>(path);
 */
class IVFileSystem : public VNamedObject
{
public:
	typedef VSharedPtr<IVBufferStream> FileStreamPtr;
	typedef VSharedPtr<IVDirectory> DirectoryPtr;
	
	IVFileSystem(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent) {};

	virtual FileStreamPtr OpenFile(
		VStringParam in_strPathAndName,
		VAccessModeFlags in_Access) = 0;

	/** The working dir at the time the vfs was created */
	virtual std::string GetWorkingDir() const = 0;

	/** Change the working dir. "Local" file mountings in the vfs.xml file
	 * will be relative to this path. Effective at the time of mounting. Thus
	 * changing the current dir will not affect previously mounted files. Will
	 * not change the current directory of the operating system
	 */
	virtual void SetWorkingDir(const std::string& in_strNewWorkingDir) = 0;

	/** Returns whether a file or directory named workdir/in_strPath exists */
	virtual vbool ExistsFile(const std::string& in_strPath) const = 0;

	///** get directory info */
	virtual IVDirectory* GetDir(VStringParam in_strDir = "/") = 0;

	virtual vbool ExistsDir(VStringParam in_strDir) const = 0;
	virtual vbool ExistsFile(VStringParam in_strFile) const = 0;
	virtual vbool Exists(VStringParam in_strFSObject) const = 0;

	/** mount resources as described inside the xml file */
	virtual void MountFromXML(VStringParam in_strFileName) = 0;

	/** prints all file and directory names to vout */
	virtual void DumpFileSystem() const = 0;
	/** prints all file and directory names starting at the given dir to vout */
	virtual void DumpDir(vfs::IVDirectory& dir, const std::string& prefix) const = 0;
};

typedef VServicePtr<IVFileSystem> VFileSystemPtr;

inline void DumpFileSystem() { VFileSystemPtr()->DumpFileSystem(); }

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
template<>
inline v3d::vfs::IVFileSystem* v3d::QueryService<v3d::vfs::IVFileSystem>()
{
	return QueryObject<v3d::vfs::IVFileSystem>("vfs.fs");
}
//-----------------------------------------------------------------------------
#endif // V3D_IVFILESYSTEM_H

