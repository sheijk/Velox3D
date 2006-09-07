/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VPBUFFERTEXTURE_H
#define V3D_VPBUFFERTEXTURE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/OpenGL.h>

#include <V3d/Graphics/IVTexture.h>
#include "../../Graphics/OpenGL/Context/VOffscreenContextBase.h"

#include <string>
//----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Pixel Buffer Texture Interface for Render to Texture
 *
 * @author lars
 */
class VPBufferTexture : public IVTexture
{
public:
	VPBufferTexture(VOffscreenContextBase* in_pContext);
	virtual ~VPBufferTexture();

	/**
	 * @see v3d::graphics::IVTexture::Bind
	 */
	void Bind(vuint in_nTextureUnit = 0);

	/**
	 * @see v3d::graphics::IVTexture::Unbind
	 */
	void Unbind();

private:
	VOffscreenContextBase* m_pContext;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
V3D_TYPEINFO_WITHPARENT(v3d::graphics::VPBufferTexture, v3d::graphics::IVTexture);

#endif //V3D_VPBUFFERTEXTURE_H
