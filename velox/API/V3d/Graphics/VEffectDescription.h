#ifndef V3D_VEFFECTDESCRIPTION_2004_08_28_H
#define V3D_VEFFECTDESCRIPTION_2004_08_28_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Core/VException.h>

#include <vector>
#include <string>
#include <sstream>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VStringValue
{
public:
	template<typename T>
	void Set(const T val)
	{
		std::stringstream str;
		str << val;
		m_strValue = str.str();
	}

	template<> void Set(const vbool val)
	{
		m_strValue = val ? "true" : "false";
	}

	template<typename T>
	T Get() const
	{
		std::stringstream str;
		str << m_strValue;
		T t;
		str >> t;
		return t;
	}

	template<> vbool Get() const
	{
		return m_strValue == std::string("true");
	}

private:
	std::string m_strValue;
};

class VStateParameter
{
public:
	enum InvalidMark { Invalid };

	VStateParameter(InvalidMark);

	VStateParameter(VStringParam in_strName)
	{
		m_strName = in_strName;
	}

	template<typename T>
	VStateParameter(VStringParam in_strName, const T& in_Val)
	{
		m_strName = in_strName;
		SetValue<T>(in_Val);
	}
	
	VStringRetVal GetName() const;

    template<typename T>
	T GetValue() const { return m_Value.Get<T>(); }

	template<typename T> 
	void SetValue(const T& in_Val) { m_Value.Set<T>(in_Val); }

private:
	VString m_strName;
	VStringValue m_Value;
};

class VState
{
public:
	VState(VStringParam in_strName);

	VStringRetVal GetName() const;

	vuint GetParameterCount() const;

	VStateParameter GetParameter(vuint in_nIndex) const;

	/**
	 * Read a parameter's value by name
	 * If the named parameter exists, out_Value will be overridden with it's
	 * value. If it doesn't exist, it will remain it's original value
	 */
	template<typename T>
	vbool GetParameter(VStringParam in_strName, T& out_Value) const;

	void SetParameter(VStateParameter in_Param);

	template<typename T>
	void SetParameter(VStringParam in_strName, T in_Value);

	VStateParameter GetParameterByName(VStringParam in_strName) const;
	vbool ContainsParameter(VStringParam in_strName) const;

private:
	vuint GetIndexOfNamedParam(const VString& in_strName) const;

	std::string m_strName;

	std::vector<VStateParameter> m_Parameters;
};

template<typename T>
vbool VState::GetParameter(VStringParam in_strName, T& out_Value) const
{
	if( ContainsParameter(in_strName) )
	{
		out_Value = GetParameterByName(in_strName).GetValue<T>();
		return true;
	}
	else
		return false;
}

template<typename T>
void VState::SetParameter(VStringParam in_strName, T in_Value)
{
	VStateParameter param(in_strName);
	param.SetValue<T>(in_Value);
	SetParameter(param);
}

class VRenderPass
{
public:
	vuint GetStateCount() const;

	VState& State(vuint in_nIndex);
	const VState& State(vuint in_nIndex) const;

	VState const* GetStateByName(VStringParam in_strName) const;

	vuint AddState(const VState& in_State);
	VState& AddState(VStringParam in_strName);

private:
	typedef VPointer<VState>::SharedPtr StatePtr;

	std::vector<StatePtr> m_States;
};

class VShaderPath
{
public:
	vuint GetRenderPassCount() const;
	
	VRenderPass& RenderPass(vuint in_nIndex);
	const VRenderPass& RenderPass(vuint in_nIndex) const;

	vuint AddRenderPass();

private:
	typedef VPointer<VRenderPass>::SharedPtr RenderPassPtr;

	std::vector<RenderPassPtr> m_RenderPasses;
};

class VEffectDescription
{
public:
	vuint GetShaderPathCount() const;

	VShaderPath& ShaderPath(vuint in_nIndex);
	const VShaderPath& ShaderPath(vuint in_nIndex) const;

	vuint AddShaderPath();

private:
	typedef VPointer<VShaderPath>::SharedPtr ShaderPathPtr;

	std::vector<ShaderPathPtr> m_ShaderPaths;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VEFFECTDESCRIPTION_2004_08_28_H
