#include <V3d/Scene/VMeshPartBase.h>
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>
#include <V3dLib/Utils/VStringValue.h>

#include <V3d/Graphics/IVDevice.h>
#include <V3d/Updater/IVUpdateManager.h>
#include <V3dLib/Graphics/Misc/MiscUtils.h>
#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

using namespace v3d::entity;
using namespace v3d::resource;
using namespace v3d::graphics;

namespace {
	std::string ParameterVarName(const IVParameter& in_Param)
	{
		return "mat_" + in_Param.GetName();
	}

	vbool contains(const std::string& str, const char* chars)
	{
		return str.find_first_of(chars) < str.size();
	}

	vbool IsValidPartParamName(const std::string& name)
	{
		vbool isglstate = name.find("mat_gl_") == 0;
		vbool containsInvalidChars = contains(name, "[]");

		return !isglstate && !containsInvalidChars;
	}
}

VMeshPartBase::VMeshPartBase(VResourceDataPtr<const IVMaterial> in_hMaterial) :
	m_pSceneManager(VPartDependency::Ancestor, RegisterTo()),
	m_pRigidBody(VPartDependency::Neighbour, RegisterTo())
{
	SetMaterial(in_hMaterial);
}

VMeshPartBase::VMeshPartBase(const std::string& in_strMaterialResource)
	: m_pSceneManager(VPartDependency::Ancestor, RegisterTo()),
	m_pRigidBody(VPartDependency::Neighbour, RegisterTo())
{
	m_hMaterial = GetMutableResourceData<IVMaterial>(in_strMaterialResource.c_str());
}


/**
* d'tor
*/
VMeshPartBase::~VMeshPartBase()
{
}

const graphics::IVMaterial& VMeshPartBase::GetMaterial() const
{
	return *m_hMaterial;
}

vuint VMeshPartBase::GetPassCount() const
{
	if( m_hMaterial != 0 )
		return m_hMaterial->PassCount();
	else
		return 0;
}

void VMeshPartBase::ApplyPassStates(vuint in_nPassNum, IVDevice& in_Device) const
{
	//bad.. texture parameter values need to be updated before the material is
	// applied, all other after that..
	ApplyParameterValues(in_Device);
	ApplyMaterial(in_Device, &m_hMaterial->GetPass(in_nPassNum));
	ApplyParameterValues(in_Device);
}

void VMeshPartBase::UnapplyPassStates(vuint in_nPassNum, IVDevice& in_Device) const
{
	// do nothing
	//TODO: give materials an "unapply" method
}

void VMeshPartBase::SetMaterial(
	resource::VResourceDataPtr<const graphics::IVMaterial> in_hMaterial)
{
	resource::VResourceDataPtr<graphics::IVMaterial> newMaterial =
		GetMutableResourceData<IVMaterial>(
			in_hMaterial.GetEnclosingResource()->GetQualifiedName().c_str());

	if( m_hMaterial != newMaterial )
	{
		m_hMaterial = newMaterial;

		m_ParameterValues.clear();

		// add parameter values for all parameters
		VRangeIterator<IVParameter> params = m_hMaterial->Parameters();
		while( params.HasNext() )
		{
			VSharedPtr<IVParameterValue> pParamValue = 
				CreateParamValue(params->GetType());

			AddParamValue(params->GetName(), pParamValue);
			++params;
		}
	}
}

const math::VRBTransform& VMeshPartBase::GetModelTransform() const
{
	return m_pRigidBody->GetTransform();
}

void VMeshPartBase::SetModelTransform(const math::VRBTransform& in_Transform)
{
	m_pRigidBody->SetTransform(in_Transform);
}

VRangeIterator<const IVShapePart> VMeshPartBase::GetVisibleMeshes() const
{
	return CreateSingleValueIterator<const IVShapePart>(this);
}

void VMeshPartBase::Activate()
{
	if( m_pSceneManager.IsConnected() )
		m_pSceneManager->Add(this);
}

void VMeshPartBase::Deactivate()
{
	if( m_pSceneManager.IsConnected() )
		m_pSceneManager->Remove(this);
}

//TODO: move to material setup, together with AddVariables and ApplySetting
void VMeshPartBase::ApplyParameterValues(graphics::IVDevice& in_Device) const
{
	for(ParamValueMap::const_iterator paramValue = m_ParameterValues.begin();
		paramValue != m_ParameterValues.end();
		++paramValue)
	{
		IVParameter* parameter = m_hMaterial->GetParameterByName(paramValue->first);

		if( parameter != 0 )
		{
			IVParameterValue* pValue = paramValue->second.Get();
			pValue->Apply(*parameter);

			parameter->ApplyAutoValue(in_Device);
		}
	}
}

void VMeshPartBase::AddParamValue(const std::string& in_strName, VSharedPtr<IVParameterValue> in_pValue)
{
	m_ParameterValues[in_strName] = in_pValue;
}

void VMeshPartBase::RemoveParamValue(const std::string& in_strName)
{
	m_ParameterValues.erase(in_strName);
}

void VMeshPartBase::OnMessage(
	const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;

	string request = in_Message.Get("type").Get<string>();

	if( request == "getSettings" )
	{
		AddVariables(in_pAnswer);
	}
	else if( request == "update" )
	{
		ApplySetting(in_Message);
	}
}

void VMeshPartBase::AddVariables(messaging::VMessage* in_pAnswer)
{
	if( in_pAnswer == 0 )
		return;

	std::string materialResourceName;

	if( m_hMaterial.GetEnclosingResource() != 0 )
		materialResourceName =
			m_hMaterial.GetEnclosingResource()->GetQualifiedName();

	in_pAnswer->AddProperty("material", materialResourceName);

	for(ParamValueMap::const_iterator paramValue = m_ParameterValues.begin();
		paramValue != m_ParameterValues.end();
		++paramValue)
	{
		IVParameter* parameter = m_hMaterial->GetParameterByName(paramValue->first);

		if( parameter != 0 )
		{
			const std::string name = ParameterVarName(*parameter);
			//const std::string value = parameter->AsString();
			const std::string& value = paramValue->second->Get();

			if( IsValidPartParamName(name) )
				in_pAnswer->AddProperty(name, value);
			//else
				//V3D_LOG("ignored material param as part param: " 
					//<< name << "=" << value << "\n");
		}
	}

}

void VMeshPartBase::ApplySetting(const messaging::VMessage& in_Message)
{
	using std::string;

	const string name = in_Message.Get("name").Get<string>();
	const string value = in_Message.Get("value").Get<string>();

	try
	{
		if( name == "material" ) 
		{
			SetMaterial(GetResourceData<IVMaterial>(value.c_str()));
		}
		else 
		{
			for(ParamValueMap::const_iterator paramValue = m_ParameterValues.begin();
				paramValue != m_ParameterValues.end();
				++paramValue)
			{
				IVParameter* parameter = m_hMaterial->GetParameterByName(paramValue->first);

				if( parameter != 0 && ParameterVarName(*parameter) == name )
				{
					paramValue->second->Set(value);
				}
			}
		}
	}
	catch(VException& e)
	{
		vout << "Failed to create model: " << e.GetErrorString() << vendl;
	}
}

void VMeshPartBase::InterpreteMessage(
	messaging::VMessageInterpreter &interpreter,  
	const messaging::VMessage& in_Message,  
	messaging::VMessage* in_pAnswer ) 
{
	messaging::VMessageInterpreter::Result result = 
		interpreter.HandleMessage(this, in_Message, in_pAnswer);

	switch(result) {
	case messaging::VMessageInterpreter::GetSettings:
		{
			AddVariables(in_pAnswer);
		} break;
	case messaging::VMessageInterpreter::ApplySetting:
		{
			ApplySetting(in_Message);
		} break;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
