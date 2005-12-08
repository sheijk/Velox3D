#ifndef V3D_VTEXTURE2D_H
#define V3D_VTEXTURE2D_H
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
 * 2D Texture Interface
 *
 * @author lars
 */
class VTexture2D : public VBaseTexture
{
public:
	VTexture2D(const image::VImage& in_Image, int in_TextureID);
	virtual ~VTexture2D();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO_WITHPARENT(v3d::graphics::VTexture2D, v3d::graphics::VBaseTexture);
//-----------------------------------------------------------------------------
#endif //V3D_VTEXTURE2D_H