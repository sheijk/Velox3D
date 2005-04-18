#include "VMaterial.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VRenderStateList::VRenderStateList(std::list<const IVRenderState*>& in_States)
	: m_States(in_States.begin(), in_States.end())
{
}

vuint VRenderStateList::StateCount() const
{
	return (vuint)m_States.size();
}

const IVRenderState& VRenderStateList::GetState(vuint in_nPriority) const
{
	return * m_States[in_nPriority];
}

/**
 * standard c'tor
 */
VMaterial::VMaterial(const std::vector<VRenderStateList>& in_Passes)
	:
	m_Passes(in_Passes.begin(), in_Passes.end())
{
}

/**
 * d'tor
 */
VMaterial::~VMaterial()
{
}

vuint VMaterial::PassCount() const
{
	return vuint(m_Passes.size());
}

const IVPass& VMaterial::GetPass(vuint in_nNum) const
{
	return m_Passes[in_nNum];
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
