/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VFixedFunctionPass.h"
//-----------------------------------------------------------------------------

#include "../VTextureStateCategory.h"
#include "../VMiscStateCategory.h"
#include <V3d/Core/RangeIter.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VMiscStateCategory* VFixedFunctionPass::m_pMiscStateCategory = 0;
VTextureStateCategory* VFixedFunctionPass::m_pTextureStateCategory = 0;

/**
 * standard c'tor
 */
VFixedFunctionPass::VFixedFunctionPass(
	RenderStateList in_DefaultStates, const VRenderPass& in_Pass)
	:
	VRenderStateList(in_DefaultStates)
{
	// create texture state
	V3D_ASSERT(m_pTextureStateCategory != 0);

	IVRenderState* pTextureState = m_pTextureStateCategory->CreateState(in_Pass);
	SetState(pTextureState);

	// create misc state
	V3D_ASSERT(m_pMiscStateCategory != 0);

	IVRenderState* pMiscState = m_pMiscStateCategory->CreateState(in_Pass);
	SetState(pMiscState);
}

/**
 * d'tor
 */
VFixedFunctionPass::~VFixedFunctionPass()
{
}

vbool VFixedFunctionPass::CanRealize(const VRenderPass& in_Pass)
{
	// check if all states are known
	for(vuint stateNum = 0; stateNum < in_Pass.GetStateCount(); ++stateNum)
	{
		const VState& state(in_Pass.State(stateNum));

		if( ! StateTypeKnown(state.GetName().AsCString()) )
			return false;
	}

	return true;
}

vbool VFixedFunctionPass::StateTypeKnown(const std::string& in_Type)
{
	return true;
	//if( in_Type == "vshader" || in_Type == "pshader" )
	//	return false;
	//else
	//	return true;
}

void VFixedFunctionPass::SetCategories(
	VTextureStateCategory* in_pTextureStateCategory,
	VMiscStateCategory* in_pMiscStateCategory)
{
	m_pTextureStateCategory = in_pTextureStateCategory;
	m_pMiscStateCategory = in_pMiscStateCategory;
}

VRangeIterator<IVParameter> VFixedFunctionPass::Parameters()
{
	return CreateEmptyIterator<IVParameter>();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

