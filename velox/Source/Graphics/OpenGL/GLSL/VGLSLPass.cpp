#include "VGLSLPass.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VShaderCategory* VGLSLPass::s_pShaderCategory = 0;

/**
 * standard c'tor
 */
VGLSLPass::VGLSLPass(RenderStateList in_DefaultStates, const VRenderPass& in_Pass)
	: VRenderStateList(in_DefaultStates)
{
	V3D_ASSERT(s_pShaderCategory != NULL);
	VShaderState* pShaderState = s_pShaderCategory->CreateState(in_Pass);
	
	SetState(pShaderState);

	if( pShaderState->GetShader() != 0 )
	{
		AddParameters(pShaderState->GetShader()->Parameters());
	}
}

/**
 * d'tor
 */
VGLSLPass::~VGLSLPass()
{
}

vbool VGLSLPass::CanRealize(const VRenderPass& in_Pass)
{
	return VShaderCategory::CanCreateStateFrom(in_Pass);
}

void VGLSLPass::SetCategories(VShaderCategory* in_pShaderCategory)
{
	s_pShaderCategory = in_pShaderCategory;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------