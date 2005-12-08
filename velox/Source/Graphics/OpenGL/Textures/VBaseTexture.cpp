#include "VBaseTexture.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VBaseTexture::VBaseTexture()
{
	m_iTextureTarget = 0;
	m_iTextureID = 0;
	m_nTextureUnit = 0;
}

VBaseTexture::VBaseTexture(const image::VImage& in_Image, GLenum in_TextureTarget) : 
	m_iTextureTarget(in_TextureTarget)
{
	m_nTextureUnit = 0;
	m_iTextureID = 0;
}

VBaseTexture::~VBaseTexture()
{
}

void VBaseTexture::Bind(vuint in_nTextureUnit)
{
	m_nTextureUnit = in_nTextureUnit;
	glEnable(m_iTextureTarget);
	glActiveTexture(GL_TEXTURE0 + m_nTextureUnit);
	glBindTexture(m_iTextureTarget, m_iTextureID);
}

void VBaseTexture::Unbind()
{
	glActiveTexture(GL_TEXTURE0 + m_nTextureUnit);
	glBindTexture(m_iTextureTarget, 0);
	glDisable(m_iTextureTarget);
	glActiveTexture(GL_TEXTURE0);
}

GLint VBaseTexture::GetTextureId() const
{
	return m_iTextureID;
}

GLenum VBaseTexture::GetTextureTarget() const
{
	return m_iTextureTarget;
}

/*VCubemapPosX::VCubemapPosX(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_POSITIVE_X)
{
	m_iTextureID = in_TextureID;
}

VCubemapPosX::~VCubemapPosX()
{
}

void VCubemapPosX::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X, m_iTextureID);
}

void VCubemapPosX::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VCubemapNegX::VCubemapNegX(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_NEGATIVE_X)
{
	m_iTextureID = in_TextureID;
}

VCubemapNegX::~VCubemapNegX()
{
}

void VCubemapNegX::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, m_iTextureID);
}

void VCubemapNegX::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VCubemapPosY::VCubemapPosY(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_POSITIVE_Y)
{
	m_iTextureID = in_TextureID;
}

VCubemapPosY::~VCubemapPosY()
{
}

void VCubemapPosY::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, m_iTextureID);
}

void VCubemapPosY::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VCubemapNegY::VCubemapNegY(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y)
{
	m_iTextureID = in_TextureID;
}

VCubemapNegY::~VCubemapNegY()
{
}

void VCubemapNegY::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, m_iTextureID);
}

void VCubemapNegY::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VCubemapPosZ::VCubemapPosZ(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_POSITIVE_Z)
{
	m_iTextureID = in_TextureID;
}

VCubemapPosZ::~VCubemapPosZ()
{
}

void VCubemapPosZ::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, m_iTextureID);
}

void VCubemapPosZ::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VCubemapNegZ::VCubemapNegZ(const image::VImage& in_Image, int in_TextureID) :  VBaseTexture(in_Image, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
{
	m_iTextureID = in_TextureID;
}

VCubemapNegZ::~VCubemapNegZ()
{
}

void VCubemapNegZ::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, m_iTextureID);
}

void VCubemapNegZ::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}
*/
//-----------------------------------------------------------------------------
}}// namespace v3d::graphics
//-----------------------------------------------------------------------------