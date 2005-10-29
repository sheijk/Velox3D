#ifndef V3D_VOFFSCREENDEVICERESTYPE_H
#define V3D_VOFFSCREENDEVICERESTYPE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Image/VImage.h>
#include <V3d/Resource.h>
#include <V3d/Graphics/IVRenderContext.h>
#include "../../Graphics/OpenGL/Context/VPBufferWindowContext.h"
#include "../../Graphics/OpenGL/VOpenGLDevice.h"

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
*/
class VOffscreenDeviceResType : public resource::IVResourceType
{ 
	std::vector<VTypeInfo> m_ManagedTypes;

public:
	VOffscreenDeviceResType();
	virtual ~VOffscreenDeviceResType();

	virtual VRangeIterator<VTypeInfo> CreatedTypes();
	virtual VRangeIterator<VTypeInfo> ManagedTypes();

	virtual vbool Generate(
		resource::VResource* in_pResource, 
		VTypeInfo in_Type);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VOFFSCREENDEVICERESTYPE_H
