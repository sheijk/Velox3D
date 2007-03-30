/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VTextureState.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

IVTexture* VTextureState::m_pLastTexture = 0;
IVStateCategory* VTextureState::m_pCategory = 0;

VTextureState::VTextureState(IVTexture* in_pTexture)
{
	m_pTexture = in_pTexture;
}

VTextureState::VTextureState(resource::VResourceDataPtr<const IVTexture> in_pTexture)
{
	m_pTexture = const_cast<IVTexture*>(&*in_pTexture);
}

void VTextureState::Apply() const
{
	if( m_pLastTexture != 0 )
	{
		m_pLastTexture->Unbind();
	}

	m_pTexture->Bind();

	m_pLastTexture = m_pTexture;
}

void VTextureState::SetCategory(IVStateCategory* in_pStateCategory)
{
	m_pCategory = in_pStateCategory;
}

IVStateCategory* VTextureState::GetCategory() const
{
	V3D_ASSERT(m_pCategory != 0);
	return m_pCategory;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

