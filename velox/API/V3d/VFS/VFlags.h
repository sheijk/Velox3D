#ifndef V3D_VFLAGS_H
#define V3D_VFLAGS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

enum VCreationFlags
{
	VCreateNew,
	VCreateAlways,
	VOpenExisting,
	VOpenAlways,
	VTruncate
};

enum VAccessModeFlags
{
	VReadAccess = 1,
	VWriteAccess = 2,
	VRWAccess = 3
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VFLAGS_H
