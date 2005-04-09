#ifndef V3D_IVFILESYSTEM_H
#define V3D_IVFILESYSTEM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/VFS/VFlags.h>
#include <v3d/VFS/IVBufferStream.h>
#include <v3d/VFS/IVDirectory.h>
#include <v3d/VFS/IVFile.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VServicePtr.h>

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
	typedef VPointer<IVBufferStream>::SharedPtr FileStreamPtr;
	typedef VPointer<IVDirectory>::SharedPtr DirectoryPtr;
	
	IVFileSystem(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent) {};

	virtual FileStreamPtr OpenFile(
		VStringParam in_strPathAndName,
		VAccessModeFlags in_Access) = 0;

	/** get directory info */
	virtual IVDirectory* GetDir(VStringParam in_strDir = "/") = 0;

	virtual vbool ExistsDir(VStringParam in_strDir) = 0;
	virtual vbool ExistsFile(VStringParam in_strFile) = 0;
	virtual vbool Exists(VStringParam in_strFSObject) = 0;
};

typedef VServicePtr<IVFileSystem> VFileSystemPtr;
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
