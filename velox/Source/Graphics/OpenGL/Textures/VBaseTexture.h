/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VBASETEXTURE_H
#define V3D_VBASETEXTURE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/OpenGL.h>

#include <V3d/Graphics/IVTexture.h>
#include <V3d/Image/VImage.h>

#include <string>
//----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Base Texture Interface, here bind and Unbind all Textures
 *
 * @author lars
 */
class VBaseTexture : public IVTexture
{
public:
	VBaseTexture();
	VBaseTexture(const image::VImage& in_Image, GLenum in_TextureTarget);
	virtual ~VBaseTexture();

	/**
	 * @see v3d::graphics::IVTexture::Bind
	 */
	virtual void Bind(vuint in_nTextureUnit = 0);

	/**
	 * @see v3d::graphics::IVTexture::Unbind
	 */
	virtual void Unbind();

	GLint GetTextureId() const;
	GLenum GetTextureTarget() const;

protected:

	GLenum m_iTextureTarget;
	GLuint m_iTextureID;
	vuint m_nTextureUnit;
};

//class VCubemapPosX : public VBaseTexture
//{
//	VCubemapPosX(const image::VImage& in_Image, int in_TextureID);
//	virtual ~VCubemapPosX();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Bind
//	 */
//	void Bind();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Unbind
//	 */
//	void Unbind();
//};
//
//class VCubemapNegX : public VBaseTexture
//{
//public:
//
//	VCubemapNegX(const image::VImage& in_Image, int in_TextureID);
//	virtual ~VCubemapNegX();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Bind
//	 */
//	void Bind();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Unbind
//	 */
//	void Unbind();
//};
//
//class VCubemapPosY : public VBaseTexture
//{
//public:
//
//	VCubemapPosY(const image::VImage& in_Image, int in_TextureID);
//	virtual ~VCubemapPosY();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Bind
//	 */
//	void Bind();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Unbind
//	 */
//	void Unbind();
//};
//
//class VCubemapNegY : public VBaseTexture
//{
//public:
//
//	VCubemapNegY(const image::VImage& in_Image, int in_TextureID);
//	virtual ~VCubemapNegY();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Bind
//	 */
//	void Bind();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Unbind
//	 */
//	void Unbind();
//};
//
//class VCubemapPosZ : public VBaseTexture
//{
//public:
//
//	VCubemapPosZ(const image::VImage& in_Image, int in_TextureID);
//	virtual ~VCubemapPosZ();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Bind
//	 */
//	void Bind();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Unbind
//	 */
//	void Unbind();
//};
//
//class VCubemapNegZ : public VBaseTexture
//{
//public:
//
//	VCubemapNegZ(const image::VImage& in_Image, int in_TextureID);
//	virtual ~VCubemapNegZ();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Bind
//	 */
//	void Bind();
//
//	/**
//	 * @see v3d::graphics::IVTexture::Unbind
//	 */
//	void Unbind();
//};
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO_WITHPARENT(v3d::graphics::VBaseTexture, v3d::graphics::IVTexture);
//-----------------------------------------------------------------------------
#endif //V3D_BASETEXTURE_H
