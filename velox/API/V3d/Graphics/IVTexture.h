#ifndef V3D_IVTEXTURE_H
#define V3D_IVTEXTURE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

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
	virtual void Bind() = 0;
	
	/**
	 * Unbind Texture
	 */
	virtual void Unbind() = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_IVTEXTURE_H