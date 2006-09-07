/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VUNTEXTURED_H
#define V3D_VUNTEXTURED_H
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
 * Untextured Interface
 *
 * @author lars
 */
class VUntextured : public VBaseTexture
{
public:

	VUntextured();
	VUntextured(const image::VImage& in_Image, int in_TextureID);
	virtual ~VUntextured();

	/**
	 * @see v3d::graphics::IVTexture::Bind
	 */
	void Bind(vuint in_nTextureUnit = 0);

	/**
	 * @see v3d::graphics::IVTexture::Unbind
	 */
	void Unbind();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif //V3D_UNTEXTURED_H
