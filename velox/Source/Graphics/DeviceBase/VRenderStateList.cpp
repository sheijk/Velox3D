/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VRenderStateList.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVStateCategory.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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

void VRenderStateList::AddParameter(IVParameter* in_pParam)
{
	m_Parameters.push_back(in_pParam);
}

VRangeIterator<IVParameter> VRenderStateList::Parameters()
{
	return CreateDerefBeginIterator<IVParameter>(m_Parameters);
}

IVParameter* VRenderStateList::GetParameterByName(
	const std::string& in_strName)
{
	for(ParameterContainer::iterator param = m_Parameters.begin();
		param != m_Parameters.end();
		++param)
	{
		if( (*param)->GetName() == in_strName )
			return *param;
	}

	return 0;
}

void VRenderStateList::AddParameters(VRangeIterator<IVParameter> in_Params)
{
	VRangeIterator<IVParameter> params = in_Params;

	while(params.HasNext())
	{
		AddParameter(&*params);
		++params;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

