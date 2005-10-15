#include "VTextureState.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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
