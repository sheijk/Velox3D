#include "VShaderState.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

IVShader* VShaderState::s_pActiveShader = 0;

/**
 * standard c'tor
 */
VShaderState::VShaderState(IVShader* in_pShader, IVStateCategory* in_pCategory)
{
	m_pShader = in_pShader;
	m_pCategory = in_pCategory;
}

/**
 * d'tor
 */
VShaderState::~VShaderState()
{
}

void VShaderState::Apply() const
{
	if( s_pActiveShader != 0 )
	{
		s_pActiveShader->Unbind();
	}

	m_DepthState.Apply();

	if( m_pShader != 0 )
	{
		m_pShader->Bind();
	}

	s_pActiveShader = m_pShader;
}

const IVStateCategory* VShaderState::GetCategory() const
{
	return m_pCategory;
}

IVShader* VShaderState::GetShader()
{
	return m_pShader;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
