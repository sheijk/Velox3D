#include "VRenderStateList.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVStateCategory.h>

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

void VRenderStateList::SetState(IVRenderState* in_pRenderState)
{
	const vuint priority = in_pRenderState->GetCategory()->GetPriority();

	V3D_ASSERT(priority >= 0 && priority < static_cast<vuint>(m_States.size()));

	ClearState(priority);
	m_States[priority] = in_pRenderState;
}

void VRenderStateList::ClearState(vuint in_nPriority)
{
	V3D_ASSERT(in_nPriority < m_States.size());

	//TODO: states auch wieder loeschen
	//delete m_States[in_nPriority];
	m_States[in_nPriority] = 0;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
