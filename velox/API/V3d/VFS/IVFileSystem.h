#ifndef V3D_IVFILESYSTEM_H
#define V3D_IVFILESYSTEM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/Core/SmartPtr/VGuards.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Virtual File System
 * - mount and unmount data
 * - open files
 * - access directory structure
 */
class IVFileSystem : public VNamedObject
{
public:
	typedef VPointer<IVOfflineStream>::AutoPtr FileStreamPtr;

	virtual FileStreamPtr OpenFile(VStringParam in_strPathAndName) = 0;

//	typedef ... DirectoryIteratorPtr;
//	typedef ... FileIteratorPtr;

//	virtual DirectoryIterator GetRootDir() =0;
//	virtual void MoveDir() = 0;
//	virtual void Mount() = 0;
//	virtual void Unmount() = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVFILESYSTEM_H
