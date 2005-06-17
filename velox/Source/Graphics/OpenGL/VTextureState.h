#ifndef V3D_VTEXTURESTATE_H
#define V3D_VTEXTURESTATE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "IVOpenGLRenderState.h"

#include <V3d/OpenGL.h>

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
		m_lastTexture.Unbind();
		m_texture.Bind();
		m_lastTexture = m_texture;
	}

private:

	IVTexture        m_texture;
	static IVTexture m_lastTexture;
};

class VTextureState2D : public VTextureState
{
public:
	VTextureState2D(GLint in_nTextureId) :
		VTextureState(in_nTextureId, GL_TEXTURE_2D)
	{}

	virtual void Apply() const
	{
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_CUBE_MAP);
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_nTextureId);
	}
};

class VTextureStateUntextured : public IVOpenGLRenderState
{
public:
	virtual void Apply() const
	{
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_CUBE_MAP);
		glDisable(GL_TEXTURE_2D);
	}
};

class VTextureStatePosX : public VTextureState
{
public:
	VTextureStatePosX(GLint in_nTextureId)
		: VTextureState(in_nTextureId, GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB)
	{}
};

class VTextureStateNegX : public VTextureState
{
public:
	VTextureStateNegX(GLint in_nTextureId)
		: VTextureState(in_nTextureId, GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB)
	{}
};

class VTextureStatePosY : public VTextureState
{
public:
	VTextureStatePosY(GLint in_nTextureId)
		: VTextureState(in_nTextureId, GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB)
	{}
};

class VTextureStateNegY : public VTextureState
{
public:
	VTextureStateNegY(GLint in_nTextureId)
		: VTextureState(in_nTextureId, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB)
	{}
};

class VTextureStatePosZ : public VTextureState
{
public:
	VTextureStatePosZ(GLint in_nTextureId)
		: VTextureState(in_nTextureId, GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB)
	{}
};

class VTextureStateNegZ : public VTextureState
{
public:
	VTextureStateNegZ(GLint in_nTextureId)
		: VTextureState(in_nTextureId, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB)
	{}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATE_H