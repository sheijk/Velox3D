#include "VBaseTexture.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VBaseTexture::VBaseTexture(const image::VImage& in_Image, TextureType in_Type)
{
	switch(m_textureType)
	{
	case TextureType_2D:
		{
			VTexture2D* pTexture2D = new VTexture2D(in_Image);

			break;
		}
	case TextureType_Cube:
		{
			// TODO: Tja, ich muss noch das Cubemap Interface schreiben -- lars
			break;
		}
	case TextureType_Sphere:
		{
			// TODO: Tja, ich muss noch das Spheremap Interface schreiben -- lars
			break;
		}
	}
}

VBaseTexture::~VBaseTexture()
{
}

void VBaseTexture::Bind()
{
	glBindTexture(m_iTextureTarget, &m_iTextureID);
}

void VBaseTexture::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

VTexture2D::VTexture2D(const image::VImage& in_Image) : m_iTextureTarget(GL_TEXTURE_2D)
{
}

VTexture2D::~VTexture2D()
{
}

void VTexture2D::Bind()
{
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_iTextureID);
}

void VTexture2D::Unbind()
{
	glDeleteTextures(1, &m_iTextureID);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------