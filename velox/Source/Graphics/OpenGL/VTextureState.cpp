#include "VTextureState.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

IVTexture* VTextureState::m_pLastTexture = 0;

VTextureState::VTextureState(IVTexture* in_pTexture)
{
	m_pTexture = in_pTexture;
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

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------