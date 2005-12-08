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

private:
	GLuint m_TextureId;
	GLuint m_FBOId;
	GLuint m_DepthBufferId;
	GLuint m_StencilBufferId;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VFRAMEBUFFEROBJECTCONTEXT_2005_11_04_H
