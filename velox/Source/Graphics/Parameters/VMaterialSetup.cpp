#include <V3d/Graphics/Parameters/VMaterialSetup.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
#include <V3d/Core/VLogging.h>
#include <V3d/Graphics/Parameters/IVParameterValue.h>
#include <V3d/Graphics/Parameters/VGenericValue.h>
#include <V3d/Graphics/IVMaterial.h>

#include <V3dLib/Utils/VStringValue.h>
#include <V3d/Math/VVectorOps.h>
#include <V3d/Math/VMatrixOps.h>
#include <V3d/Graphics/Parameters/VTextureValue.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VMaterialSetup::VMaterialSetup()
{
}

/**
 * d'tor
 */
VMaterialSetup::~VMaterialSetup()
{
}

void VMaterialSetup::Apply(IVMaterial& io_Material) const
{
	for(NameValueMap::const_iterator value = m_Values.begin();
		value != m_Values.end();
		++value)
	{
		IVParameter* pParam = io_Material.GetParameterByName(value->first);

		if( pParam != 0 )
		{
			value->second->Apply(*pParam);
		}
	}
}

void VMaterialSetup::Add(VStringParam in_strParamName, VSharedPtr<IVParameterValue> in_Value)
{
	m_Values[std::string(in_strParamName)] = in_Value;
}

class VUnknownParamValue : public IVParameterValue
{
public:
	virtual void Apply(const IVParameter& in_Param) const
	{}

	virtual void Set(const std::string& in_NewValue) 
	{}
};

VSharedPtr<IVParameterValue> CreateParamValue(IVParameter::Type in_ParamType)
{
	IVParameterValue* pParamValue = 0;

	switch(in_ParamType)
	{
	case IVParameter::Float: pParamValue = new VFloatParamValue(); break;
	case IVParameter::Float2: pParamValue = new VFloat2ParamValue(); break;
	case IVParameter::Float4: pParamValue = new VFloat4ParamValue(); break;
	case IVParameter::Float44: pParamValue = new VFloat44ParamValue(); break;

	case IVParameter::Int: pParamValue = new VIntParamValue(); break;

	case IVParameter::Bool: pParamValue = new VBoolParamValue(); break;

	case IVParameter::Texture: pParamValue = new VTextureValue(); break;

	default:
		// make sure we did not miss any type
		if( in_ParamType != IVParameter::Unknown )
		{
			V3D_LOGONCE(parameterTypeNotImplemented);
		}

		pParamValue = new VUnknownParamValue();
		break;
	}

	return SharedPtr(pParamValue);
}

void IVParameter::Apply(const std::string& in_strValue)
{
	V3D_THROW(VException, "not implemented, yet");
}

std::string IVParameter::AsString() const
{
	utils::VStringValue value;

	switch(GetType())
	{
	case IVParameter::Float: value.Set(AsFloat()); break;
	case IVParameter::Float2: value.Set(AsFloat2()); break;
	case IVParameter::Float4: value.Set(AsFloat4()); break;

	case IVParameter::Int: value.Set(AsInt()); break;

	case IVParameter::Bool: value.Set(AsBool()); break;

	case IVParameter::Texture: value.Set(TextureResource()); break;

	default:
		if( GetType() != IVParameter::Unknown )
		{
			V3D_LOGONCE(paramTypeNotImplemented);
		}

		value.Set("?");
		break;
	}

	return value.Get<std::string>();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
