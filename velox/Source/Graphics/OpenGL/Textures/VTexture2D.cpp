#include "VTexture2D.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VTexture2D::VTexture2D(const image::VImage& in_Image, int in_TextureID) :  
	VBaseTexture(in_Image, GL_TEXTURE_2D)
{
	m_iTextureID = in_TextureID;
}

VTexture2D::~VTexture2D()
{
	glDeleteTextures(1, &m_iTextureID);
}

//-----------------------------------------------------------------------------
}}// namespace v3d::graphics
//-----------------------------------------------------------------------------