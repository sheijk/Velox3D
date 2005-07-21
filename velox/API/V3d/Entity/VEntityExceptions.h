#ifndef V3D_VENTITYEXCEPTIONS_2004_10_09_H
#define V3D_VENTITYEXCEPTIONS_2004_10_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

V3D_DECLARE_EXCEPTION(VEntityException, VException);
V3D_DECLARE_EXCEPTION(VMissingPartException, VEntityException);
V3D_DECLARE_EXCEPTION(VPartAlreadyPresentException, VEntityException);

V3D_DECLARE_EXCEPTION(VSceneParserException, VEntityException);
V3D_DECLARE_EXCEPTION(VNoParserForTypeException, VSceneParserException);
V3D_DECLARE_EXCEPTION(VTypeAlreadyRegisteredException, VSceneParserException);
V3D_DECLARE_EXCEPTION(VPartParseException, VSceneParserException);

//-----------------------------------------------------------------------------
}} // namespace v3d:entity
//-----------------------------------------------------------------------------
#endif // V3D_VENTITYEXCEPTIONS_2004_10_09_H
