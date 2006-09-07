/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCUBEMAPTEXTURE_2005_11_30_H
#define V3D_VCUBEMAPTEXTURE_2005_11_30_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVTexture.h>
#include <V3d/Image/VImage.h>

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VCubeMapTexture : public IVTexture
{
public:
	VCubeMapTexture(
		const image::VImage& in_Front,
		const image::VImage& in_Back,
		const image::VImage& in_Left,
		const image::VImage& in_Right,
		const image::VImage& in_Top,
		const image::VImage& in_Bottom);

	virtual ~VCubeMapTexture();

	virtual void Bind(vuint in_nTextureUnit = 0);
	virtual void Unbind();

private:
	vuint m_nTextureUnit;
	GLuint m_TextureId[6];
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VCUBEMAPTEXTURE_2005_11_30_H

