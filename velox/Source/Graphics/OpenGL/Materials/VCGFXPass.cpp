/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VCGFXPass.h"
//-----------------------------------------------------------------------------

#include "VCGFXMaterial.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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

void VCGFXPass::Bind(const VOpenGLDevice* in_pDevice)
{
	cgSetPassState(m_Pass);
	V3D_CHECK_CG_ERROR();

	m_pMaterial->ApplyParameters(in_pDevice);
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

