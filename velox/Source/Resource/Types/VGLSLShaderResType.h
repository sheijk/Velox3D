#ifndef V3D_VGLSLSHADERRESTYPE_2006_03_01_H
#define V3D_VGLSLSHADERRESTYPE_2006_03_01_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Resource/IVResourceType.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VGLSLShaderResType : public resource::IVResourceType
{
public:
	VGLSLShaderResType();
	virtual ~VGLSLShaderResType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VGLSLSHADERRESTYPE_2006_03_01_H
