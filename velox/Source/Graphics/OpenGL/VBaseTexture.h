#ifndef V3D_VBASETEXTURE_H
#define V3D_VBASETEXTURE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVTexture.h>

#include <string>
//----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Base Texture Interface, here bind and Unbind all Textures
 *
 * @author lars
 */
class VBaseTexture : public IVTexture
{
	typedef enum {
		TextureType_None = 0,
		TextureType_2D = 1,
		TextureType_Cube = 2,
		TextureType_Sphere = 3
	} TextureType;

public:

	VBaseTexture(const image::VImage& in_Image, TextureType in_Type);
	virtual ~VBaseTexture();

	/**
	 * @see v3d::graphics::IVTexture::Bind
	 */
	virtual void Bind() = 0;

	/**
	 * @see v3d::graphics::IVTexture::Unbind
	 */
	virtual void Unbind() = 0;

protected:

	GLenum      m_iTextureTarget;
	int         m_iTextureID;
	std::string m_strFilename;
};

/**
 * 2D Texture Interface
 *
 * @author lars
 */
class VTexture2D : public VBaseTexture
{
public:

	VTexture2D(const image::VImage& in_Image);
	virtual ~VTexture2D();

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
#endif //V3D_BASETEXTURE_H