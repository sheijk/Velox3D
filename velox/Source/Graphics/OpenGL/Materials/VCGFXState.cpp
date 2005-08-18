#include "VCGFXState.h"
//-----------------------------------------------------------------------------

#include "VCGFXPass.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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

void VCGFXState::Apply() const
{
	if( s_pLastPass != 0 )
		s_pLastPass->Unbind();

	if( m_pPass != 0 )
		m_pPass->Bind();

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
