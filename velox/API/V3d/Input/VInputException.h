#ifndef V3D_VINPUTEXCEPTION_H
#define V3D_VINPUTEXCEPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
V3D_DECLARE_EXCEPTION(VInputException, VException);
V3D_DECLARE_EXCEPTION(VCreationException, VInputException);
V3D_DECLARE_EXCEPTION(VIllegalKeyIdentifierException, VInputException);
V3D_DECLARE_EXCEPTION(VUpdateException, VInputException);

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VINPUTEXCEPTION_H