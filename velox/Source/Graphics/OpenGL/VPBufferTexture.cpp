/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VPBufferTexture.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VPBufferTexture::VPBufferTexture(VOffscreenContextBase* in_pContext) : 
	m_pContext(in_pContext)
{
	V3D_ASSERT(m_pContext != 0);
}

VPBufferTexture::~VPBufferTexture()
{
}

void VPBufferTexture::Bind(vuint in_nTextureUnit)
{
	V3D_ASSERT(m_pContext != 0);
	m_pContext->BindAsTexture(in_nTextureUnit);
}

void VPBufferTexture::Unbind()
{
	V3D_ASSERT(m_pContext != 0);
	m_pContext->UnbindTexture();
};

//-----------------------------------------------------------------------------
}}// namespace v3d::graphics
//-----------------------------------------------------------------------------
