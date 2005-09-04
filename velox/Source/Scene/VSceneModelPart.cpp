#include <V3d/Scene/VSceneModelPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>

#include <V3d/Messaging/VProtocol.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::resource;
using namespace std;
using namespace v3d::entity;

VSceneModelPart::VSceneModelPart(const graphics::VModel& in_Model) :
	m_Model(in_Model),
		m_pParent(VPartDependency::Ancestor, VSimpleScene::GetDefaultId(), RegisterTo()),
		m_RigidBodyPart(
			VPartDependency::Neighbour,	
			entity::VRigidBodyPart::GetDefaultId(), RegisterTo())
{
}

void VSceneModelPart::AddModelMesh(
	VStringParam in_strMeshResource, 
	VStringParam in_strMaterialResource)
{
	m_Model.Add(graphics::VModelMesh(
		GetResourceData<graphics::IVMesh>(in_strMeshResource),
		GetResourceData<graphics::IVMaterial>(in_strMaterialResource)
		));
}

void VSceneModelPart::AddModelMesh(const graphics::VModelMesh in_ModelMesh)
{
	m_Model.Add(in_ModelMesh);
}

void VSceneModelPart::RemoveAllMeshes()
{
	m_Model = graphics::VModel();
}

void VSceneModelPart::Activate()
{
	if( m_pParent.Get() != 0 )
	{
		m_Id = m_pParent->Add(m_Model);
		m_pParent->Add(this);
	}
}

void VSceneModelPart::Deactivate()
{
	if( m_pParent.Get() != 0 )
	{
		m_pParent->Remove(m_Id);
		m_Id = 0;
		m_pParent->Add(this);
	}
}

//namespace {
//	messaging::VProtocol addProtocol = messaging::VProtocol()
//		.SetDefault("request", "ok")
//		.SetDefault("resource", "");
//}

void VSceneModelPart::Send(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	if( ! in_Message.HasProperty("type") )
		return;
		
	string request = in_Message.Get("type").Get<string>();
	
	if( request == "getSettings" )
	{
		if( in_pAnswer == 0 )
			return;
			
		vout << "ret" << vendl;
		
		in_pAnswer->AddProperty("mesh", m_strMeshRes);
		in_pAnswer->AddProperty("material", m_strMatRes);
		in_pAnswer->AddProperty("model", m_strModel);
	}
	else if( request == "update" )
	{
		const string name = in_Message.Get("name").Get<string>();
		const string value = in_Message.Get("value").Get<string>();

		try
		{
			if( name == "model" ) {
				m_strModel = value;
				
				vout << "Adding " << m_strModel << vendl;
				m_Model.AddMeshes(*resource::GetResourceData<graphics::VModel>(m_strModel.c_str()));
			}
			else {
				if( name == "mesh" ) {
					m_strMeshRes = value;
				}
				else if( name == "material" ) {
					m_strMatRes = value;
				}
				
				vout << "Adding " << m_strMeshRes << ", " << m_strMatRes << vendl;
				AddModelMesh(m_strMeshRes.c_str(), m_strMatRes.c_str());
			}
		}
		catch(VException& e)
		{
			vout << "Failed to create model: " << e.GetErrorString() << vendl;
		}
	}
	else 
	{
		vout << "type " << request << vendl;
	}

//	if( request == "add" )
//	{
//		string mesh = in_Message.Get("mesh").Get<string>();
//		string material = in_Message.Get("material").Get<string>();
//
//		AddModelMesh(mesh.c_str(), material.c_str());
//	}
}

graphics::VModel& VSceneModelPart::GetModel()
{
	return m_Model;
}
void VSceneModelPart::Update()
{
	math::VRBTransform trans = m_RigidBodyPart->GetTransform();
	m_Model.ApplyMatrix(trans.GetAsMatrix());
}

std::string VSceneModelPart::GetDefaultId()
{
	return "model";
}
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
