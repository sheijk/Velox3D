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
protected:
	const GLint m_nTextureId;
	const GLenum m_nTextureTarget;

public:
	/** create a state disabling texturing like follows: noTexState = VTextureState(NoTexture); */
	enum NoTex { NoTexture };

protected:
	///**
	// * Erzeugt eine Textur State zum ausschalten von Texturing
	// */
	//VTextureState(NoTex) : 
	//	m_nTextureId(0), 
	//	m_nTextureTarget(-1)
	//{
	//}

	/**
	 * Erzeugt einen Texture State der die gegebene Textur bindet
	 */
	VTextureState(GLint in_nTextureId, GLenum in_nTextureTarget) :
		m_nTextureId(in_nTextureId),
		m_nTextureTarget(in_nTextureTarget)
	{
	}

public:
	virtual void Apply() const
	{
		glBindTexture(m_nTextureTarget, m_nTextureId);
//		glEnable(m_nTextureTarget);
	}
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
