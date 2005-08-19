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
	cgSetPassState(m_Pass);
	V3D_CHECK_CG_ERROR();

	m_pMaterial->ApplyParameters();
}

void VCGFXPass::Unbind()
{
	m_pMaterial->UnapplyParameters();

	cgResetPassState(m_Pass);
	V3D_CHECK_CG_ERROR();
}

vbool VCGFXPass::CanRealize(const VRenderPass& in_Pass)
{
	return false;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
