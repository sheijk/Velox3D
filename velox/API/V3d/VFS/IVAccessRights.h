#ifndef V3D_VACCESSRIGHTS_H
#define V3D_VACCESSRIGHTS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Access rights for directories and files
 */
class IVAccessRights
{
public:
	virtual ~IVAccessRights() {};

	/** allow to create a file inside dir */
	virtual vbool AllowCreateFile() const = 0;

	/** allow to create a subdirectory */
	virtual vbool AllowCreateDir() const = 0;
	
	/** allow element to be deleted */
	virtual vbool AllowDelete() const = 0;
	
	//virtual vbool AllowDeleteChild() = 0;
	
	/** allow read access (files: open for reading, dirs: access content */
	virtual vbool AllowReadAccess() const = 0;
	
	/** allow writing (file: open for writing, dir: child files permission */
	virtual vbool AllowWriteAccess() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VACCESSRIGHTS_H
