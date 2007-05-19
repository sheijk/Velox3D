/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/VModelPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>
#include <V3d/Messaging/VProtocol.h>
#include <V3d/Utils/VRegisterGuard.h>
#include <V3d/Entity/IVEntitySerializationService.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Graphics/Misc/MiscUtils.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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

	m_bIsActive = false;
}

VModelPart::VModelPart() :
	m_pParent(VPartDependency::Ancestor, RegisterTo()),
	m_RigidBodyPart(VPartDependency::Neighbour,	RegisterTo())
{
	m_bIsActive = false;
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

void VModelPart::OnActivate()
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

	m_bIsActive = true;
}

void VModelPart::OnDeactivate()
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

	m_bIsActive = false;
}

//namespace {
//	messaging::VProtocol addProtocol = messaging::VProtocol()
//		.SetDefault("request", "ok")
//		.SetDefault("resource", "");
//}

void VModelPart::OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	if( ! in_Message.HasProperty("type") )
		return;
		
	string request = in_Message.Get("type").Get<string>();
	
	if( request == "getSettings" )
	{
		if( in_pAnswer == 0 )
			return;

		in_pAnswer->AddProperty("material", "");
		in_pAnswer->AddProperty("model", m_strModel);
	}
	else if( request == "update" )
	{
		const string name = in_Message.Get("name").Get<string>();
		const string value = in_Message.Get("value").Get<string>();

		try
		{
			if( name == "model" ) 
			{
				vbool wasActive = m_bIsActive;
				if( wasActive )
					Deactivate();

				m_Meshes.clear();

				m_strModel = value;
				
				vout << "Adding " << m_strModel << vendl;
				Add(*resource::GetResourceData<graphics::VModel>(m_strModel.c_str()));

				if( wasActive )
					Activate();
			}
			else if( name == "material" )
			{
				ChangeMaterialForAllMeshes(value);
			}
		}
		catch(VException& e)
		{
			vout << "Failed to create model: " << e.GetErrorString() << vendl;
		}
	}
}

void VModelPart::ChangeMaterialForAllMeshes(const std::string& in_strResourceName)
{
	using graphics::IVMaterial;

	VResourceDataPtr<const IVMaterial> hMaterial =
		GetResourceData<IVMaterial>(in_strResourceName.c_str());

	for(MeshList::iterator part = m_Meshes.begin(); part != m_Meshes.end(); ++part)
	{
		VSharedPtr<MeshPart> pMeshPart = *part;

		pMeshPart->m_hMaterial = hMaterial;
	}
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

vuint VModelPart::MeshPart::GetPassCount() const
{
	if( m_hMaterial != 0 )
		return m_hMaterial->PassCount();
	else
		return 0;
}

void VModelPart::MeshPart::ApplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const
{
	ApplyMaterial(in_Device, &m_hMaterial->GetPass(in_nPassNum));
}

void VModelPart::MeshPart::UnapplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const
{
	//nothing..
}

void VModelPart::MeshPart::UpdateAndCull(const graphics::IVCamera& in_Camera)
{
}

VRangeIterator<const IVShapePart> VModelPart::MeshPart::GetVisibleMeshes() const
{
	return CreateSingleValueIterator<const IVShapePart>(this);
}

V3D_REGISTER_PART_PARSER(VModelPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

