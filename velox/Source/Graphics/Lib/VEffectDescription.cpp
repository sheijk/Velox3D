#include <v3d/Graphics/VEffectDescription.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

VStateParameter::VStateParameter(InvalidMark)
{
}

VStringRetVal VStateParameter::GetName() const
{
	return m_strName;
}

//-----------------------------------------------------------------------------

VState::VState(VStringParam in_strName)
	: m_strName(in_strName)
{
}

VStringRetVal VState::GetName() const
{
	return m_strName.c_str();
}

vuint VState::GetParameterCount() const
{
	return vuint(m_Parameters.size());
}

VStateParameter VState::GetParameter(vuint in_nIndex) const
{
	V3D_ASSERT(in_nIndex < GetParameterCount());
	return m_Parameters[in_nIndex];
}

void VState::SetParameter(VStateParameter in_Param)
{
	vuint index = GetIndexOfNamedParam(in_Param.GetName());

	if( index >= m_Parameters.size() )
	{
		m_Parameters.push_back(in_Param);
	}
	else
	{
		m_Parameters[index].SetValue(in_Param.GetValue<std::string>());
	}
}

VStateParameter VState::GetParameterByName(VStringParam in_strName) const
{
	vuint index = GetIndexOfNamedParam(in_strName);

	if( index < m_Parameters.size() )
	{
		return m_Parameters[index];
	}
	else
		return VStateParameter(VStateParameter::Invalid);
}

vbool VState::ContainsParameter(VStringParam in_strName) const
{
	return GetIndexOfNamedParam(in_strName) < m_Parameters.size();
}

vuint VState::GetIndexOfNamedParam(const VString& in_strName) const
{
	for(vuint pid = 0; pid < m_Parameters.size(); ++pid)
	{
		std::string name = m_Parameters[pid].GetName().AsCString();
		
		if( name == in_strName.AsCString() )
			return pid;
	}

	return vuint(m_Parameters.size());
}

//-----------------------------------------------------------------------------

vuint VRenderPass::GetStateCount() const
{
	return vuint(m_States.size());
}

VState& VRenderPass::State(vuint in_nIndex)
{
	if( in_nIndex < GetStateCount() )
	{
		return *(m_States[in_nIndex].Get());
	}
	else
		V3D_THROW(VException, "blahblubber");
}

const VState& VRenderPass::State(vuint in_nIndex) const
{
	if( in_nIndex < GetStateCount() )
	{
		return *(m_States[in_nIndex].Get());
	}
	else
		V3D_THROW(VException, "blahblubber");
}

VState const* VRenderPass::GetStateByName(VStringParam in_strName) const
{
	VString strName(in_strName);

	for(vuint stateid = 0; stateid < GetStateCount(); ++stateid)
	{
		if( m_States[stateid]->GetName() == strName )
		{
			return m_States[stateid].Get();
		}
	}

	return 0;
}

vuint VRenderPass::AddState(const VState& in_State)
{
	m_States.push_back(StatePtr(new VState(in_State)));
	return vuint(m_States.size())-1;
}

VState& VRenderPass::AddState(VStringParam in_strName)
{
	const vuint stateIndex = AddState(VState(in_strName));
	return *m_States[stateIndex].Get();
}			  

void VRenderPass::Clear()
{
	m_States.clear();
}

//-----------------------------------------------------------------------------

vuint VShaderPath::GetRenderPassCount() const
{
	return vuint(m_RenderPasses.size());
}

VRenderPass& VShaderPath::RenderPass(vuint in_nIndex)
{
	if( in_nIndex < GetRenderPassCount() )
	{
		return *m_RenderPasses[in_nIndex].Get();
	}
	else
		V3D_THROW(VException, "blahblub");
}

const VRenderPass& VShaderPath::RenderPass(vuint in_nIndex) const
{
	if( in_nIndex < GetRenderPassCount() )
	{
		return *m_RenderPasses[in_nIndex].Get();
	}
	else
		V3D_THROW(VException, "blahblub");
}

VRenderPass& VShaderPath::AddRenderPass()
{
    m_RenderPasses.push_back(RenderPassPtr(new VRenderPass()));
	return *m_RenderPasses.back();
}


void VShaderPath::Clear()
{
	m_RenderPasses.clear();
}

//-----------------------------------------------------------------------------

vuint VEffectDescription::GetShaderPathCount() const
{
	return vuint(m_ShaderPaths.size());
}

VShaderPath& VEffectDescription::ShaderPath(vuint in_nIndex)
{
	if( in_nIndex < GetShaderPathCount() )
	{
		return *m_ShaderPaths[in_nIndex].Get();
	}
	else
		V3D_THROW(VException, "bhasd");
}

const VShaderPath& VEffectDescription::ShaderPath(vuint in_nIndex) const
{
	if( in_nIndex < GetShaderPathCount() )
	{
		return *m_ShaderPaths[in_nIndex].Get();
	}
	else
		V3D_THROW(VException, "bhasd");
}

VShaderPath& VEffectDescription::AddShaderPath()
{
	m_ShaderPaths.push_back(ShaderPathPtr(new VShaderPath()));
	return *m_ShaderPaths.back();
}

void VEffectDescription::Clear()
{
	m_ShaderPaths.clear();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
