#ifndef V3D_VTEXTURESTATE_H
#define V3D_VTEXTURESTATE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "IVOpenGLRenderState.h"

#include <Windows.h>
#include <gl/GL.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VTextureState : public IVOpenGLRenderState
{
	GLint m_nTextureId;
	vbool m_bNoTexture;
public:
	enum NoTex { NoTexture };

	VTextureState(NoTex) : m_nTextureId(0), m_bNoTexture(true) 
	{
	}

	VTextureState(GLint in_nTextureId) : 
	m_nTextureId(in_nTextureId),
		m_bNoTexture(false)
	{
	}

	virtual void Apply() const
	{
		if( m_bNoTexture )
		{
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			//glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, m_nTextureId);
			glEnable(GL_TEXTURE_2D);
		}
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATE_H
