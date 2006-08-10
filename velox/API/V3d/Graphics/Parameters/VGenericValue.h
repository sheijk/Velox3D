#ifndef V3D_VGENERICVALUE_2005_11_29_H
#define V3D_VGENERICVALUE_2005_11_29_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/Parameters/IVParameterValue.h>
#include <V3d/Graphics/IVParameter.h>
#include <V3d/Utils/VStringValue.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

template<typename ParamType>
class VGenericValue : public IVParameterValue
{
public:
	VGenericValue()
	{}

	VGenericValue(const ParamType& in_InitialValue)
	{
		m_Value = in_InitialValue;
	}

	virtual void Apply(const IVParameter& in_Param) const
	{
		in_Param.Apply(m_Value);
	}

	ParamType GetValue() const { return m_Value; }
	void SetValue(const ParamType& in_Value) { m_Value = in_Value; }

	virtual void Set(const std::string& in_NewValue)
	{
		utils::VStringValue value(in_NewValue);
		m_Value = value.Get<ParamType>();
	}

	virtual std::string Get() const
	{
		utils::VStringValue value;
		value.Set(m_Value);
		return value.Get<std::string>();
	}

private:
	ParamType m_Value;
};

typedef VGenericValue<vfloat32> VFloatParamValue;
typedef VGenericValue<VVector2f> VFloat2ParamValue;
typedef VGenericValue<VVector4f> VFloat4ParamValue;

typedef VGenericValue<VMatrix44f> VFloat44ParamValue;

typedef VGenericValue<vint> VIntParamValue;

typedef VGenericValue<vbool> VBoolParamValue;

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VGENERICVALUE_2005_11_29_H
