#include <V3d/Scene/VModelPart.h>
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

VModelPart::VModelPart(const graphics::VModel& in_Model) :
	m_pParent(VPartDependency::Ancestor, RegisterTo()),
	m_RigidBodyPart(VPartDependency::Neighbour,	RegisterTo())
{
	Add(in_Model);
}

VModelPart::VModelPart() :
	m_pParent(VPartDependency::Ancestor, RegisterTo()),
	m_RigidBodyPart(VPartDependency::Neighbour,	RegisterTo())
{
}

void VModelPart::Add(const graphics::VModel& in_Model)
{
	for(vuint partNum = 0; partNum < in_Model.GetPartCount(); ++partNum)
	{
		Add(in_Model.GetPart(partNum));
	}
}

void VModelPart::AddMesh(
	VStringParam in_strMeshResource, 
	VStringParam in_strMaterialResource)
{
	Add(graphics::VModelMesh(
		GetResourceData<graphics::IVMesh>(in_strMeshResource),
		GetResourceData<graphics::IVMaterial>(in_strMaterialResource)
		));
}

void VModelPart::Add(const graphics::VModelMesh in_ModelMesh)
{
	// create mesh part for model mesh
	VSharedPtr<MeshPart> part(new MeshPart());
	part->m_pModelPart = this;
	part->m_hMesh = in_ModelMesh.GetMesh();
	part->m_hMaterial = in_ModelMesh.GetMaterial();

	m_Meshes.push_back(part);
}

void VModelPart::RemoveAllMeshes()
{
	m_Meshes.clear();
}

void VModelPart::UpdateAndCull(const graphics::IVCamera& in_Camera)
{
}

VRangeIterator<const IVShapePart> VModelPart::GetVisibleMeshes() const
{
	return CreateDerefBeginIterator<const IVShapePart>(m_Meshes);
	//VRangeIterator<MeshPart> partIter = CreateBeginIterator(m_Meshes);
//	return CreateIterator<MeshList::const_iterator>(m_Meshes.begin(), m_Meshes.end());
}

void VModelPart::Activate()
{
	if( m_pParent.Get() != 0 )
	{
		VRangeIterator<MeshPart> part = CreateDerefBeginIterator<MeshPart>(m_Meshes);
		while( part.HasNext() )
		{
			m_pParent->Add(&*part);
			++part;
		}
	}
}

void VModelPart::Deactivate()
{
	if( m_pParent.Get() != 0 )
	{
		VRangeIterator<MeshPart> part = CreateDerefBeginIterator<MeshPart>(m_Meshes);
		while( part.HasNext() )
		{
			m_pParent->Remove(&*part);
			++part;
		}
	}
}

//namespace {
//	messaging::VProtocol addProtocol = messaging::VProtocol()
//		.SetDefault("request", "ok")
//		.SetDefault("resource", "");
//}

void VModelPart::Send(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	if( ! in_Message.HasProperty("type") )
		return;
		
	string request = in_Message.Get("type").Get<string>();
	
	if( request == "getSettings" )
	{
		if( in_pAnswer == 0 )
			return;

		//vuint meshNum = 0;
		//for(MeshList::iterator meshIter = m_Meshes.begin(); 
		//	meshIter != m_Meshes.end(); 
		//	++meshIter)
		//{
		//	std::stringstream name;
		//	name << "mesh nr. " << meshNum;
		//	in_pAnswer->AddProperty(

		//	++meshNum;
		//}

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
			m_Meshes.clear();

			if( name == "model" ) {
				m_strModel = value;
				
				vout << "Adding " << m_strModel << vendl;
				Add(*resource::GetResourceData<graphics::VModel>(m_strModel.c_str()));
			}
			else {
				if( name == "mesh" ) {
					m_strMeshRes = value;
				}
				else if( name == "material" ) {
					m_strMatRes = value;
				}
				
				vout << "Adding " << m_strMeshRes << ", " << m_strMatRes << vendl;
				AddMesh(m_strMeshRes.c_str(), m_strMatRes.c_str());
			}
		}
		catch(VException& e)
		{
			vout << "Failed to create model: " << e.GetErrorString() << vendl;
		}
	}

//	if( request == "add" )
//	{
//		string mesh = in_Message.Get("mesh").Get<string>();
//		string material = in_Message.Get("material").Get<string>();
//
//		AddModelMesh(mesh.c_str(), material.c_str());
//	}
}

const math::VRBTransform& VModelPart::GetModelTransform() const
{
	return m_RigidBodyPart->GetTransform();
}

void VModelPart::SetModelTransform(const math::VRBTransform& in_Transform)
{
	m_RigidBodyPart->SetTransform(in_Transform);
}

std::string VModelPart::GetDefaultId()
{
	return "model";
}

//-----------------------------------------------------------------------------

void VModelPart::MeshPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	in_Device.RenderMesh(&*m_hMesh);
}

const math::VRBTransform& VModelPart::MeshPart::GetModelTransform() const
{
	math::VRBTransform transform = m_pModelPart->GetModelTransform();
	return m_pModelPart->GetModelTransform();
}

const graphics::IVMaterial& VModelPart::MeshPart::GetMaterial() const
{
	return *m_hMaterial;
}

void VModelPart::MeshPart::UpdateAndCull(const graphics::IVCamera& in_Camera)
{
}

VRangeIterator<const IVShapePart> VModelPart::MeshPart::GetVisibleMeshes() const
{
	return CreateSingleValueIterator<const IVShapePart>(this);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
