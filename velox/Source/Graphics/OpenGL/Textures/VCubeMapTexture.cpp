/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include "VCubeMapTexture.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/GraphicsExceptions.h>

#include <vector>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::image;

namespace {
	void CreateTexture(const VImage& image, GLenum in_TextureTarget)
	{
		V3D_ASSERT(image.GetWidth() > 0);
		V3D_ASSERT(image.GetHeight() > 0);
		V3D_ASSERT(image.GetPixelData() != 0);

		const vbyte* temp = image.GetPixelData();

		//GLuint id;
		//glGenTextures(1, &id);
		//glBindTexture(in_TextureTarget, id);

		glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri( in_TextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( in_TextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( in_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri( in_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

		gluBuild2DMipmaps(
			in_TextureTarget, 
			GL_RGB, 
			image.GetWidth(), 
			image.GetHeight(),
			GL_RGB,
			GL_UNSIGNED_BYTE, 
			image.GetPixelData()
			);
	}

	const vuint FRONT_NUM = 0;
	const vuint BACK_NUM = 1;
	const vuint LEFT_NUM = 2;
	const vuint RIGHT_NUM = 3;
	const vuint TOP_NUM = 4;
	const vuint BOTTOM_NUM = 5;
}

namespace {
	vuint SquareSize(const VImage& image)
	{
		if( image.GetWidth() == image.GetHeight() )
		{
			return image.GetWidth();
		}
		else
		{
			return -1;
		}
	}
}

void VCubeMapTexture::ExceptionOnUnmatchingSize(const VImage& image)
{
	if( SquareSize(image) != m_nSize || m_nSize <= 0 )
	{
		V3D_THROW(VGraphicException, 
			"all images of cube map must be square and the same size > 0" );
	}
}

VCubeMapTexture::VCubeMapTexture(
	const VImage& in_Front,
	const VImage& in_Back,
	const VImage& in_Left,
	const VImage& in_Right,
	const VImage& in_Top,
	const VImage& in_Bottom)
{
	m_nSize = SquareSize( in_Front );
	ExceptionOnUnmatchingSize( in_Back );
	ExceptionOnUnmatchingSize( in_Left );
	ExceptionOnUnmatchingSize( in_Right );
	ExceptionOnUnmatchingSize( in_Top );
	ExceptionOnUnmatchingSize( in_Bottom );

	glGenTextures( 1, &m_TextureId );
	glBindTexture( GL_TEXTURE_CUBE_MAP, m_TextureId );

	CreateTexture(in_Front, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	CreateTexture(in_Back, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	CreateTexture(in_Left, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	CreateTexture(in_Right, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	CreateTexture(in_Top, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	CreateTexture(in_Bottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);

	glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );

	m_nTextureUnit = 0;
}

VCubeMapTexture::VCubeMapTexture(vuint in_nSize)
{
	const vuint componentCount = 3;
	const GLenum pixelFormat = GL_RGB;
	const GLenum pixelDataType = GL_UNSIGNED_BYTE;

	std::vector<vuint8> pixels;
	pixels.resize( componentCount * in_nSize * in_nSize );

	m_nSize = in_nSize;

	glGenTextures( 1, &m_TextureId );
	glBindTexture( GL_TEXTURE_CUBE_MAP, m_TextureId );

	for(vuint side = 0; side < 6; ++side)
	{
		const GLenum textureTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X + side;

		glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri( textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri( textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

		gluBuild2DMipmaps(
			textureTarget, 
			pixelFormat,
			m_nSize,
			m_nSize,
			pixelFormat,
			pixelDataType,
			&pixels[0]
			);
	}

	glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
	m_nTextureUnit = 0;
}

VCubeMapTexture::~VCubeMapTexture()
{
	glDeleteTextures( 1, &m_TextureId );
	//glDeleteTextures(6, m_TextureId);
}

void VCubeMapTexture::Bind(vuint in_nTextureUnit)
{
	//TODO: textur matrix aus kamera (view matrix) position berechnen
	m_nTextureUnit = in_nTextureUnit;
	glActiveTexture(GL_TEXTURE0 + m_nTextureUnit);
	glBindTexture( GL_TEXTURE_CUBE_MAP, m_TextureId );
	//glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, m_TextureId[FRONT_NUM]);
	//glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, m_TextureId[BACK_NUM]);
	//glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X, m_TextureId[RIGHT_NUM]);
	//glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, m_TextureId[LEFT_NUM]);
	//glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, m_TextureId[TOP_NUM]);
	//glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, m_TextureId[BOTTOM_NUM]);

	const GLenum texGenMode = GL_REFLECTION_MAP;
	const GLenum texPlane = GL_EYE_PLANE;

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_Q);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, texGenMode);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, texGenMode);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, texGenMode);
	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, texGenMode);

	float sfact[4] = { 1, 0, 0, 0 };
	float tfact[4] = { 0, 1, 0, 0 };
	float rfact[4] = { 0, 0, 1, 0 };
	float qfact[4] = { 0, 0, 0, 1 };
	glTexGenfv(GL_S, texPlane, sfact);
	glTexGenfv(GL_T, texPlane, tfact);
	glTexGenfv(GL_R, texPlane, rfact);
	glTexGenfv(GL_Q, texPlane, qfact);

	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	//glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	//glEnable(GL_TEXTURE_GEN_R);

	glEnable(GL_TEXTURE_CUBE_MAP);
}

void VCubeMapTexture::Unbind()
{
//	glActiveTexture(GL_TEXTURE0 + m_nTextureUnit);
	glDisable(GL_TEXTURE_CUBE_MAP);
//	glActiveTexture(GL_TEXTURE0);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	glDisable(GL_TEXTURE_CUBE_MAP);
}

vuint VCubeMapTexture::GetSize() const
{
	return m_nSize;
}

GLuint VCubeMapTexture::GetTextureId() const
{
	return m_TextureId;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

