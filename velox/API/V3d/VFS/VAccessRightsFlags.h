#ifndef V3D_VACCESSRIGHTSFLAGS_H
#define V3D_VACCESSRIGHTSFLAGS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Flags for access rights. Contains the same information like
 * IVAccessRights but can be constructed more easily.
 */
struct VAccessRightsFlags
{
	VAccessRightsFlags() : allowRead(false), allowWrite(false),
		allowDelete(false), allowCreateDir(false), allowCreateFile(false) {};

	vbool allowRead;
	vbool allowWrite;
	vbool allowDelete;
	vbool allowCreateDir;
	vbool allowCreateFile;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VACCESSRIGHTSFLAGS_H
