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
	virtual ~IVAccessRights() = 0;

	virtual vbool AllowCreateFile() = 0;
	virtual vbool AllowCreateDir() = 0;
	virtual vbool AllowDelete() = 0;
	virtual vbool AllowDeleteChild() = 0;
	virtual vbool AllowReadAccess() = 0;
	virtual vbool AllowWriteAccess() = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VACCESSRIGHTS_H
