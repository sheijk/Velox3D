/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VFRAMEBUFFEROBJECTCONTEXT_2005_11_04_H
#define V3D_VFRAMEBUFFEROBJECTCONTEXT_2005_11_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVRenderContext.h>
#include <V3d/Graphics/VDisplaySettings.h>
#include "VOffscreenContextBase.h"

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VFrameBufferObjectContext : public VOffscreenContextBase
{
public:
	VFrameBufferObjectContext(
		const VDisplaySettings& in_DisplaySettings,
		IVRenderContext* in_pParentContext);

	virtual ~VFrameBufferObjectContext();

	virtual void MakeCurrent();
	virtual void SwapBuffers();
	virtual void BindAsTexture(vuint in_nTextureUnit);
	virtual void UnbindTexture();

protected:
	enum NoInitMarker { NoInit };

	virtual vbool IsFormatValid(const VDisplaySettings& in_Settings);

	VFrameBufferObjectContext(
		const VDisplaySettings& in_DisplaySettings,
		IVRenderContext* in_pParentContext,
		NoInitMarker);

	GLuint m_TextureId;
	GLuint m_FBOId;
	GLuint m_DepthBufferId;
	GLuint m_StencilBufferId;

	vuint m_nTextureUnit;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VFRAMEBUFFEROBJECTCONTEXT_2005_11_04_H

