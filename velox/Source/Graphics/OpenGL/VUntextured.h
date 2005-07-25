#ifndef V3D_VUNTEXTURED_H
#define V3D_VUNTEXTURED_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/OpenGL.h>

#include "VBaseTexture.h"
#include <V3d/Image/VImage.h>

#include <string>
//----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Untextured Interface
 *
 * @author lars
 */
class VUntextured : public VBaseTexture
{
public:

	VUntextured();
	VUntextured(const image::VImage& in_Image, int in_TextureID);
	virtual ~VUntextured();

	/**
	 * @see v3d::graphics::IVTexture::Bind
	 */
	void Bind();

	/**
	 * @see v3d::graphics::IVTexture::Unbind
	 */
	void Unbind();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif //V3D_UNTEXTURED_H