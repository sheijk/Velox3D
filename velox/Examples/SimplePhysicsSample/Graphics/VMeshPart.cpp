#include "VMeshPart.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace racer {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VGraphicsManager::VGraphicsManager()
{
}

void VGraphicsManager::SetDrawList(graphics::IVDrawList& in_DrawList)
{
	// don't set drawlist twice
	V3D_ASSERT(m_pDrawList == 0);

	m_pDrawList = &in_DrawList;
}

graphics::IVDrawList& VGraphicsManager::GetDrawList()
{
	V3D_ASSERT(m_pDrawList != 0);

	return *m_pDrawList;
}

//-----------------------------------------------------------------------------

VMeshPart::VMeshPart(VGraphicsManager* in_pManager) :
	m_pManager(in_pManager)
{
	m_bActive = false;
	m_pRigidBodyPart = false;
}

void VMeshPart::AddMesh(graphics::IVDevice::MeshHandle in_hMesh)
{
	AddMesh(graphics::VModel(in_hMesh));
}

void VMeshPart::AddMesh(graphics::VModel in_Model)
{
	m_Meshes.push_back(in_Model);

	// if meshes are in drawlist, add new mesh
	if( m_bActive && m_pManager != 0 )
	{
		GetDrawList().Add(in_Model);
	}
}

void VMeshPart::RemoveMesh(graphics::IVDevice::MeshHandle in_hMesh)
{
	// if meshes are in drawlist, remove it
	if( m_bActive && m_pManager != 0 )
	{
		GetDrawList().Remove(graphics::VModel(in_hMesh));
	}

	MeshList::iterator iter = std::find(m_Meshes.begin(), m_Meshes.end(), graphics::VModel(in_hMesh));
	m_Meshes.erase(iter);
}

void VMeshPart::Update()
{
	if( m_pRigidBodyPart != 0 )
	{
		VRigidBodyPart::PositionVector pos = m_pRigidBodyPart->GetPosition();

		// for all meshes, set position
		for(MeshList::iterator model = m_Meshes.begin(); model != m_Meshes.end(); ++model)
		{
			model->pTransformation->Set(0, 3, pos.Get(0));
			model->pTransformation->Set(1, 3, pos.Get(1));
			model->pTransformation->Set(2, 3, pos.Get(2));
		}
	}
}

void VMeshPart::Activate()
{
	if( m_pManager != 0 )
	{
		for(MeshList::iterator mesh = m_Meshes.begin(); mesh != m_Meshes.end(); ++mesh)
		{
			GetDrawList().Add(*mesh);
		}

		m_pManager->Add(this);

		m_bActive = true;
	}
}

void VMeshPart::Deactivate()
{
	if( m_pManager != 0 )
	{
		m_pManager->Remove(this);

		for(MeshList::iterator mesh = m_Meshes.begin(); mesh != m_Meshes.end(); ++mesh)
		{
			GetDrawList().Remove(*mesh);
		}

		m_bActive = false;
	}
}

void VMeshPart::TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part)
{
	// get rigid body part
	if( in_Id.AsStdString() == "body" && in_Part.IsOfType<VRigidBodyPart>() )
	{
		m_pRigidBodyPart = in_Part.Convert<VRigidBodyPart>();
	}
}

graphics::IVDrawList& VMeshPart::GetDrawList()
{
	V3D_ASSERT(m_pManager != 0);

	return m_pManager->GetDrawList();
}
//-----------------------------------------------------------------------------
}} // namespace v3d::racer
//-----------------------------------------------------------------------------
