#include "VPBufferTexture.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VPBufferTexture::VPBufferTexture(VPBufferWindowContext* in_pContext) : 
	m_pContext(in_pContext)
{
}

VPBufferTexture::~VPBufferTexture()
{
}

void VPBufferTexture::Bind()
{
	m_pContext->BindTexture();
}

void VPBufferTexture::Unbind()
{
	m_pContext->UnbindTexture();
};

//-----------------------------------------------------------------------------
}}// namespace v3d::graphics
//-----------------------------------------------------------------------------