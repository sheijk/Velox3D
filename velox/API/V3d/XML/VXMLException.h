#ifndef V3D_VXMLEXCEPTION_H
#define V3D_VXMLEXCEPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------

	V3D_DECLARE_EXCEPTION(VXMLException, VException);
	V3D_DECLARE_EXCEPTION(VXMLAttributeException, VXMLException);
	V3D_DECLARE_EXCEPTION(VXMLVistorException, VXMLException);
	V3D_DECLARE_EXCEPTION(VXMLTinyXMLException, VXMLException);


//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VXMLEXCEPTION_H