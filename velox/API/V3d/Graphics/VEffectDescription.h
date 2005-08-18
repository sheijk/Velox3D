#ifndef V3D_VEFFECTDESCRIPTION_2004_08_28_H
#define V3D_VEFFECTDESCRIPTION_2004_08_28_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Core/VException.h>
#include <V3dLib/Utils/VStringValue.h>

#include <vector>
#include <string>
#include <sstream>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VStateParameter
{
public:
	enum InvalidMark { Invalid };

	VStateParameter(InvalidMark);

	VStateParameter(VStringParam in_strName);

	template<typename T>
	VStateParameter(VStringParam in_strName, const T& in_Val);
	
	VStringRetVal GetName() const;

    template<typename T>
	T GetValue() const { return m_Value.Get<T>(); }

	template<typename T> 
	void SetValue(const T& in_Val) { m_Value.Set<T>(in_Val); }

private:
	VString m_strName;
	utils::VStringValue m_Value;
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

class VRenderPass
{
public:
	VRenderPass();
	VRenderPass(const VRenderPass& in_Source);
	void operator=(const VRenderPass& in_Source);

	vuint GetStateCount() const;

	VState& State(vuint in_nIndex);
	const VState& State(vuint in_nIndex) const;

	VState const* GetStateByName(VStringParam in_strName) const;

	vuint AddState(const VState& in_State);
	VState& AddState(VStringParam in_strName);

	/** Removes all states */
	void Clear();

private:
	typedef VPointer<VState>::SharedPtr StatePtr;

	std::vector<StatePtr> m_States;
};

class VShaderPath
{
public:
	VShaderPath();
	VShaderPath(const VShaderPath& in_Source);
	void operator=(const VShaderPath& in_Source);

	vuint GetRenderPassCount() const;
	
	VRenderPass& RenderPass(vuint in_nIndex);
	const VRenderPass& RenderPass(vuint in_nIndex) const;

	VRenderPass& AddRenderPass();

	/** Removes all render passes */
	void Clear();
private:
	typedef VPointer<VRenderPass>::SharedPtr RenderPassPtr;

	std::vector<RenderPassPtr> m_RenderPasses;
};

class VEffectParameter
{
public:
	VEffectParameter(VStringParam in_strName, VStringParam in_strType,
		VStringParam in_strDefault, VStringParam in_strGeneration);

	std::string GetName() const;
	void SetName(const std::string& in_Name);

	std::string GetDefault() const;
	void SetDefault(const std::string& in_Default);

	std::string GetType() const;
	void SetType(const std::string& in_Type);

	std::string GetGeneration() const;
	void SetGeneration(const std::string& in_Generation);
private:
	std::string m_xName;
	std::string m_xDefault;
	std::string m_xType;
	std::string m_xGeneration;
};

class VEffectDescription
{
public:
	VEffectDescription();
	VEffectDescription(const VEffectDescription& in_Source);
	void operator=(const VEffectDescription& in_Source);

	vuint GetShaderPathCount() const;

	VShaderPath& ShaderPath(vuint in_nIndex);
	const VShaderPath& ShaderPath(vuint in_nIndex) const;

	VShaderPath& AddShaderPath();

	/** Removes all paths */
	void Clear();

	vuint GetEffectCount() const;
	const VEffectParameter& GetParameter(vuint in_nIndex) const;

private:
	typedef VPointer<VShaderPath>::SharedPtr ShaderPathPtr;

	std::vector<ShaderPathPtr> m_ShaderPaths;
	std::vector<VEffectParameter> m_Parameters;
};

//-----------------------------------------------------------------------------
#include "VEffectDescription.inl"
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO(v3d::graphics::VEffectDescription);
//-----------------------------------------------------------------------------
#endif // V3D_VEFFECTDESCRIPTION_2004_08_28_H
