#include "VCGFXPass.h"
//-----------------------------------------------------------------------------

#include "VCGFXMaterial.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VCGFXPass::VCGFXPass(RenderStateList in_DefaultStates, 
	CGpass in_Pass, CGeffect in_Effect, CGtechnique in_Technique,
	VCGFXMaterial* in_pMaterial)
	:
	VRenderStateList(in_DefaultStates)
{
	m_Pass = in_Pass;
	m_Effect = in_Effect;
	m_Technique = in_Technique;
	m_pMaterial = in_pMaterial;

	VCGFXState* pState = new VCGFXState(this);
	SetState(pState);
}

/**
 * d'tor
 */
VCGFXPass::~VCGFXPass()
{
}

void VCGFXPass::Bind()
{
	// set model view matrix
	//CGparameter mvp = cgGetEffectParameterBySemantic(m_Effect, "ModelViewProjection");
	//V3D_ASSERT(mvp != 0);
	//cgGLSetStateMatrixParameter(mvp, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

	m_pMaterial->ApplyAutoParameters();

	cgSetPassState(m_Pass);
}

void VCGFXPass::Unbind()
{
	cgResetPassState(m_Pass);
}

vbool VCGFXPass::CanRealize(const VRenderPass& in_Pass)
{
	return false;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
