#ifndef V3D_IVFILESYSTEM_H
#define V3D_IVFILESYSTEM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/VFS/VFlags.h>
#include <v3d/VFS/IVOfflineStream.h>
#include <v3d/VFS/IVDirectory.h>
#include <v3d/VFS/IVFile.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Virtual File System
 * - mount and unmount data
 * - open files
 * - access a virtual directory structure
 */
class IVFileSystem : public VNamedObject
{
public:
	typedef VPointer<IVOfflineStream>::SharedPtr FileStreamPtr;
	typedef VPointer<IVDirectory>::SharedPtr DirectoryPtr;
	
	IVFileSystem(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent) {};

	virtual FileStreamPtr OpenFile(
		VStringParam in_strPathAndName,
		VAccessModeFlags in_Access) = 0;

	/** get directory info */
	virtual IVDirectory* GetDir(VStringParam in_strDir = "/") = 0;

//	virtual void MoveDir() = 0;
//	virtual void Mount() = 0;
//	virtual void Unmount() = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVFILESYSTEM_H
