#ifndef V3D_VINPUTEXCEPTIONS_H
#define V3D_VINPUTEXCEPTIONS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
V3D_DECLARE_EXCEPTION(VInputException, VException);
V3D_DECLARE_EXCEPTION(VCreationException, VInputException);
V3D_DECLARE_EXCEPTION(VUpdateException, VInputException);
V3D_DECLARE_EXCEPTION(VIllegalDevicePartException, VInputException);
V3D_DECLARE_EXCEPTION(VIllegalButtonException, VIllegalDevicePartException);
V3D_DECLARE_EXCEPTION(VIllegalAxisException, VIllegalDevicePartException);
V3D_DECLARE_EXCEPTION(VIllegalKeyException, VIllegalDevicePartException)

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VINPUTEXCEPTIONS_H