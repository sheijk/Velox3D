#ifndef V3D_IVTEXTURE_H
#define V3D_IVTEXTURE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

//----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Texture interface, for all Texture types.
 *
 * @author lars
 */
// TODO: Dokumentation noch etwas genauer machen! -- Lars
class IVTexture
{
public:

	IVTexture() {};
	~IVTexture() {};
	
	/**
	 * Bind Texture
	 */
	virtual void Bind(vuint in_nTextureUnit = 0) = 0;
	
	/**
	 * Unbind Texture
	 */
	virtual void Unbind() = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO(v3d::graphics::IVTexture);
//-----------------------------------------------------------------------------
#endif // V3D_IVTEXTURE_H