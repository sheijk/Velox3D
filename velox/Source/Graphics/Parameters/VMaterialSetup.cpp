/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/Parameters/VMaterialSetup.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
#include <V3d/Core/VLogging.h>

#include <V3d/Graphics/Parameters/IVParameterValue.h>
#include <V3d/Graphics/Parameters/VGenericValue.h>
#include <V3d/Graphics/IVMaterial.h>
#include <V3d/Graphics/Parameters/VTextureValue.h>
#include <V3d/Graphics/IVDevice.h>

#include <V3d/Utils/VStringValue.h>
#include <V3d/Updater/IVUpdateManager.h>

#include <V3d/Math/VVectorOps.h>
#include <V3d/Math/VMatrixOps.h>
#include <V3d/Math/VRBTransform.h>

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

	virtual std::string Get() const
	{
		return "";
	}
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

//-----------------------------------------------------------------------------
//TODO: move to IVParameter.cpp (and create it..)

namespace {
	const std::string LIGHT_COUNT_PARAM_NAME = "v3d_MaxLight";
	const std::string TIME_PARAM_NAME = "v3d_TimeFraction";
	const std::string TIME_MIN_PARAM_NAME = "v3d_TimeFraction60";
	const std::string CAM_POS_PARAM_NAME = "v3d_CameraPos";
	const std::string MODEL_MATRIX_PARAM_NAME = "v3d_ModelMatrix";
	const std::string VIEW_MATRIX_PARAM_NAME = "v3d_ViewMatrix";
}

std::string IVParameter::AsString() const
{
	utils::VStringValue value;

	switch(GetType())
	{
	case IVParameter::Float: value.Set(AsFloat()); break;
	case IVParameter::Float2: value.Set(AsFloat2()); break;
	case IVParameter::Float4: value.Set(AsFloat4()); break;
	case IVParameter::Float44: value.Set(AsFloat44()); break;

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

void IVParameter::ApplyAutoValue(IVDevice& in_Device)
{
	const std::string name = GetName();

	if( name == LIGHT_COUNT_PARAM_NAME )
	{
		Apply(vint(in_Device.MaxActiveLight()));
	}
	else if( name == TIME_PARAM_NAME )
	{
		vuint32 ms = updater::VUpdateManagerPtr()->GetMilliSecondsSinceStart() % 1000;
		vfloat32 secondFraction = vfloat32(ms) / 1000.0f;
		Apply(secondFraction);
	}
	else if( name == TIME_MIN_PARAM_NAME )
	{
		vuint32 ms = updater::VUpdateManagerPtr()->GetMilliSecondsSinceStart() % (1000 * 60);
		vfloat32 secondFraction = vfloat32(ms) / 1000.0f / 60.0f;
		Apply(secondFraction);
	}
	else if( name == CAM_POS_PARAM_NAME )
	{
		math::VVector4f camPos = math::ToVector4f( 
			in_Device.GetViewTransform().GetPosition(), 1.0f );

		Apply( camPos );
	}
	else if( name == MODEL_MATRIX_PARAM_NAME )
	{
		Apply( in_Device.GetMatrix(IVDevice::ModelMatrix) );
	}
	else if( name == VIEW_MATRIX_PARAM_NAME )
	{
		Apply( in_Device.GetViewMatrix() );
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

