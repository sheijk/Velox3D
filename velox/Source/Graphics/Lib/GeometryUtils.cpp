//-----------------------------------------------------------------------------
#include <V3dLib/Graphics/Geometry/VGeometryUtil.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

v3d::graphics::VMaterialDescription::TextureRef* CreateTextureRef(
	v3d::graphics::IVDevice& device, 
	v3d::image::VImage& image)
{
	using namespace v3d::graphics;

	VMaterialDescription::TextureRef* tr = 
		new VMaterialDescription::TextureRef();

	tr->nWidth = image.GetWidth();
	tr->nHeight = image.GetHeight();

	VByteBuffer buf(&(image.GetData()), VByteBuffer::CopyData);

	tr->hData = device.CreateBuffer(
		IVDevice::Texture, &buf, VBufferBase::DropData);

	return tr;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
