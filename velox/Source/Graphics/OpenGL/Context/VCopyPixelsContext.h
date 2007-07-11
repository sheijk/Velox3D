/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCOPYPIXELSCONTEXT_2005_11_04_H
#define V3D_VCOPYPIXELSCONTEXT_2005_11_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "VOffscreenContextBase.h"

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VCopyPixelsContext : public VOffscreenContextBase
{
public:
	VCopyPixelsContext(
		const VDisplaySettings& in_DisplaySettings,
		IVRenderContext* in_pParentContext);

	virtual ~VCopyPixelsContext();

	virtual void MakeCurrent();
	virtual void SwapBuffers();

	virtual void BindAsTexture(vuint in_nTextureUnit);
	virtual void UnbindTexture();

private:
	GLuint m_TextureId;
	vuint m_nTextureWidth;
	vuint m_nTextureHeight;
};

//-----------------------------------------------------------------------------
}
} // namespace v3d::graphics
V3D_TYPEINFO_WITHPARENT(v3d::graphics::VCopyPixelsContext, v3d::graphics::VOffscreenContextBase);
//-----------------------------------------------------------------------------
#endif // V3D_VCOPYPIXELSCONTEXT_2005_11_04_H
