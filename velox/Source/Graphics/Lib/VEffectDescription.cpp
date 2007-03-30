/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/VEffectDescription.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

VStateParameter::VStateParameter(InvalidMark)
{
}

VStateParameter::VStateParameter(VStringParam in_strName)
{
	m_strName = in_strName;
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

VRenderPass::VRenderPass()
{
}

VRenderPass::VRenderPass(const VRenderPass& in_Source)
{
	*this = in_Source;
}

void VRenderPass::operator=(const VRenderPass& in_Source)
{
	m_States.clear();
	m_States.reserve(in_Source.GetStateCount());

	for(vuint i = 0; i < in_Source.GetStateCount(); ++i)
	{
		m_States.push_back(StatePtr(new VState(in_Source.State(i))));
	}
}

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

VShaderPath::VShaderPath()
{
}

VShaderPath::VShaderPath(const VShaderPath& in_Source)
{
	*this = in_Source;
}

void VShaderPath::operator=(const VShaderPath& in_Source)
{
	m_RenderPasses.clear();
	m_RenderPasses.reserve(in_Source.GetRenderPassCount());

	for(vuint i = 0; i < in_Source.GetRenderPassCount(); ++i)
	{
		m_RenderPasses.push_back(RenderPassPtr(new VRenderPass(in_Source.RenderPass(i))));
	}
}

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
	{
		std::stringstream msg;
		msg << "Accessing non existing render pass nr. "
			<< in_nIndex << " only " << GetRenderPassCount()
			<< " paths existing";

		V3D_THROW(VException, msg.str().c_str());
	}
}

const VRenderPass& VShaderPath::RenderPass(vuint in_nIndex) const
{
	if( in_nIndex < GetRenderPassCount() )
	{
		return *m_RenderPasses[in_nIndex].Get();
	}
	else
	{
		std::stringstream msg;
		msg << "Accessing non existing render pass nr. "
			<< in_nIndex << " only " << GetRenderPassCount()
			<< " paths existing";

		V3D_THROW(VException, msg.str().c_str());
	}
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

std::string VEffectParameter::GetName() const
{
	return m_xName;
}

void VEffectParameter::SetName(const std::string& in_Name)
{
	m_xName = in_Name;
}

std::string VEffectParameter::GetDefault() const
{
	return m_xDefault;
}

void VEffectParameter::SetDefault(const std::string& in_Default)
{
	m_xDefault = in_Default;
}

std::string VEffectParameter::GetType() const
{
	return m_xType;
}

void VEffectParameter::SetType(const std::string& in_Type)
{
	m_xType = in_Type;
}

std::string VEffectParameter::GetGeneration() const
{
	return m_xGeneration;
}

void VEffectParameter::SetGeneration(const std::string& in_Generation)
{
	m_xGeneration = in_Generation;
}

//-----------------------------------------------------------------------------

VEffectDescription::VEffectDescription()
{
}

VEffectDescription::VEffectDescription(const VEffectDescription& in_Source)
{
	*this = in_Source;
}

void VEffectDescription::operator=(const VEffectDescription& in_Source)
{
	m_ShaderPaths.clear();
	m_ShaderPaths.reserve(in_Source.GetShaderPathCount());

	for(vuint i = 0; i < in_Source.GetShaderPathCount(); ++i)
	{
		m_ShaderPaths.push_back(ShaderPathPtr(new VShaderPath(in_Source.ShaderPath(i))));
	}
}

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
	{
		std::stringstream msg;
		msg << "Accessing non existing shader path nr. "
			<< in_nIndex << " only " << GetShaderPathCount()
			<< " paths existing";

		V3D_THROW(VException, msg.str().c_str());
	}
}

const VShaderPath& VEffectDescription::ShaderPath(vuint in_nIndex) const
{
	if( in_nIndex < GetShaderPathCount() )
	{
		return *m_ShaderPaths[in_nIndex].Get();
	}
	else
	{
		std::stringstream msg;
		msg << "Accessing non existing shader path nr. "
			<< in_nIndex << " only " << GetShaderPathCount()
			<< " paths existing";

		V3D_THROW(VException, msg.str().c_str());
	}
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

vuint VEffectDescription::GetEffectCount() const
{
	return static_cast<vuint>(m_Parameters.size());
}

const VEffectParameter& VEffectDescription::GetParameter(vuint in_nIndex) const
{
	V3D_ASSERT(in_nIndex < m_Parameters.size());

	return m_Parameters[in_nIndex];
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

