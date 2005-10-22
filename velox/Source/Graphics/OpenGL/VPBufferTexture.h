#ifndef V3D_VPBUFFERTEXTURE_H
#define V3D_VPBUFFERTEXTURE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/OpenGL.h>

#include <V3d/Graphics/IVTexture.h>
#include "../../Graphics/OpenGL/Context/VPBufferWindowContext.h"

#include <string>
//----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Pixel Buffer Texture Interface for Render to Texture
 *
 * @author lars
 */
class VPBufferTexture : public IVTexture
{
public:

	VPBufferTexture(VPBufferWindowContext* in_pContext);
	virtual ~VPBufferTexture();

	/**
	 * @see v3d::graphics::IVTexture::Bind
	 */
	void Bind();

	/**
	 * @see v3d::graphics::IVTexture::Unbind
	 */
	void Unbind();

private:
	VPBufferWindowContext* m_pContext;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::graphics::VPBufferTexture, v3d::graphics::IVTexture);

#endif //V3D_VPBUFFERTEXTURE_H