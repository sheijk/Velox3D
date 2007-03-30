/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VCGFXState.h"
//-----------------------------------------------------------------------------

#include "VCGFXPass.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

IVStateCategory* VCGFXState::s_pCategory = 0;
VCGFXPass* VCGFXState::s_pLastPass = 0;

VCGFXStateCategory::VCGFXStateCategory()
{
	VCGFXState::SetStateCategory(this);
}

IVRenderState* VCGFXStateCategory::CreateState(const VRenderPass& in_Pass)
{
	return new VCGFXState(0);
}

//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VCGFXState::VCGFXState(VCGFXPass* in_pPass)
{
	m_pPass = in_pPass;
}

/**
 * d'tor
 */
VCGFXState::~VCGFXState()
{
}

void VCGFXState::Apply(const VOpenGLDevice* in_pDevice) const
{
	if( s_pLastPass != 0 )
		s_pLastPass->Unbind();

	if( m_pPass != 0 )
		m_pPass->Bind(in_pDevice);

	s_pLastPass = m_pPass;
}

const IVStateCategory* VCGFXState::GetCategory() const
{
	V3D_ASSERT(s_pCategory != 0);

	return s_pCategory;
}

void VCGFXState::SetStateCategory(IVStateCategory* in_pCategory)
{
	s_pCategory = in_pCategory;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

