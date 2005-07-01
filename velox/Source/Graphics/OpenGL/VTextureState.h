#ifndef V3D_VTEXTURESTATE_H
#define V3D_VTEXTURESTATE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "IVOpenGLRenderState.h"

#include <V3d/OpenGL.h>
#include <V3d/Graphics/IVTexture.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * @author sheijk
 */
class VTextureState : public IVOpenGLRenderState
{
public:
	virtual void Apply() const
	{
		m_pLastTexture -> Unbind();
		m_pTexture -> Bind();
		m_pLastTexture = m_pTexture;
	}

private:

	IVTexture*        m_pTexture;
	static IVTexture* m_pLastTexture;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATE_H