#include <V3d/Physics/VPhysicManager.h> 
#include <V3d/Physics/VStateSphereMass.h>
#include <V3d/Physics/VGeometrySphere.h>
#include <V3d/Physics/VGeometryBox.h>
#include <V3d/Physics/VGeometryPlane.h>
#include <V3d/Physics/VGeometryMesh.h>
#include <v3d/math/VBoundingBox.h>
#include <v3d/math/VBoundingSphere.h>
#include <v3d/Physics/Bounding/VBoundingMesh.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace  physics{
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::math;

VPhysicManager::VPhysicManager()
{
	
}
VPhysicManager::~VPhysicManager()
{
}

void VPhysicManager::RegisterToUpdater()
{
	//Register();
}

void VPhysicManager::UnregisterToUpdater()
{
	//Unregister();
}

void VPhysicManager::Update(vfloat32 in_fSeconds)
{
	m_World.Update();

	typedef BodyList::iterator Iter;
	Iter begin = m_BodyList.begin();
	Iter end = m_BodyList.end();

	for(; begin != end; ++begin)
	{
 		(*begin)->Update();
	}
}

void VPhysicManager::Activate()
{
	;
}

void VPhysicManager::Deactivate()
{
	;
}

VPhysicManager::Geometry VPhysicManager::CreateGeom(IVBoundingVolumePart* in_pBoundingPart)
{
	VBoundingBox* pBox = in_pBoundingPart->GetBoundingBox();
	VBoundingSphere* pSphere = in_pBoundingPart->GetBoundingSphere();
	math::VPlane* pPlane = in_pBoundingPart->GetBoundingPlane();
	VBoundingMesh* pMesh = 0;

	if( in_pBoundingPart->HasBoundingMesh() )
	{
		pMesh = in_pBoundingPart->GetBoundingMesh();
	}	

	if(pBox)
		return CreateBoxGeom(pBox);
	if(pSphere)
		return CreateSphereGeom(pSphere);
	if(pMesh)
		return CreateMeshGeom(pMesh);
	if(pPlane)
		return CreatePlane(pPlane->GetNormal(), pPlane->GetDistance());
	
	V3D_THROW(VException, "no valid bounding part found");
	Geometry retValue;
	retValue.Assign(0);
	return retValue;
}

VPhysicManager::Geometry VPhysicManager::CreateBoxGeom(VBoundingBox* in_pBoundingBox)
{
	VSharedPtr<VGeometryBox> pGeometryBox(new VGeometryBox());
	pGeometryBox->SetWidth(in_pBoundingBox->GetLength().GetX());
	pGeometryBox->SetHeight(in_pBoundingBox->GetLength().GetY());
	pGeometryBox->SetLength(in_pBoundingBox->GetLength().GetZ());

	pGeometryBox->CreateBox(m_World.GetSpace());
	return pGeometryBox;
}
VPhysicManager::Geometry VPhysicManager::CreateMeshGeom(VBoundingMesh* in_pBoundingMesh)
{
	VSharedPtr<VGeometryMesh> pGeometry(new VGeometryMesh(*in_pBoundingMesh));
	
	pGeometry->Create(m_World.GetSpace());
	return pGeometry;
}

VPhysicManager::Geometry VPhysicManager::CreateSphereGeom(VBoundingSphere* in_pBoundingSphere)
{
	VSharedPtr<VGeometrySphere> pGeometrySphere(new VGeometrySphere());
	pGeometrySphere->SetSphereRadius(in_pBoundingSphere->GetRadius());

	pGeometrySphere->CreateSphere(m_World.GetSpace());
	return pGeometrySphere;
}

VPhysicManager::BodyPtr VPhysicManager::CreateBody()
{
	//body will take ownership of odeBody
	VOdeBody* pOdeBody = new VOdeBody();
	pOdeBody->Create(&m_World);
	BodyPtr pBody(new VBody(pOdeBody));
	//VSharedPtr<VBodyPart> bodyPart(new VBodyPart(body));
    //return bodyPart;
	return pBody;
}

VPhysicManager::BodyPtr VPhysicManager::Create(IVBoundingVolumePart* in_pBoundingPart,
											   vfloat32 in_fMass)
{
	VBoundingBox* pBox = in_pBoundingPart->GetBoundingBox();
	VBoundingSphere* pSphere = in_pBoundingPart->GetBoundingSphere();
	VBoundingMesh* pMesh = 0;

	if( in_pBoundingPart->HasBoundingMesh() )
	{
		pMesh = in_pBoundingPart->GetBoundingMesh();
	}	

	if(pBox)
		return CreateBox(in_fMass, pBox->GetLength());
	if(pSphere)
		return CreateSphere(in_fMass, pSphere->GetRadius());
	if(pMesh)
		return CreateMesh(in_fMass, pMesh);

	return BodyPtr(0);

}

VPhysicManager::BodyPtr VPhysicManager::CreateSphere(
	vfloat32 in_fMass,
	vfloat32 in_fRadius
	)
{
	BodyPtr pBody = CreateBody();

	//physic stuff
	VStateSphereMass* pMassState(new VStateSphereMass(pBody->GetOdeBody())); //FIXME: no deletion!!!!!!!!!
	VGeometrySphere* pSphereGeometry(new VGeometrySphere());//FIXME: no deletion!!!!!!!!!
	//assign values
	pMassState->SetMass(in_fMass);
	pMassState->SetRadius(in_fRadius);
	pBody->Add(pMassState);
	
	pSphereGeometry->SetSphereRadius(in_fRadius);
	pSphereGeometry->CreateSphere(m_World.GetSpace());

	pBody->SetCollisionMesh(pSphereGeometry);
	
	m_BodyList.push_back(pBody);
	
	return pBody;
}

VPhysicManager::BodyPtr VPhysicManager::CreateBox(
	vfloat32 in_fMass,
	VVector3f in_Expansion)
{
	BodyPtr pBody = CreateBody();

	VStateBoxMass* pMassState(new VStateBoxMass(pBody->GetOdeBody())); //!!!!!
	VGeometryBox* pGeometryBox(new VGeometryBox());//!!!

	pMassState->SetMass(in_fMass);
	pMassState->SetLength(in_Expansion[0]); //fix this settings!!
	pMassState->SetWidth(in_Expansion[1]);
	pMassState->SetHeight(in_Expansion[2]);

	pGeometryBox->SetLength(in_Expansion[0]);
	pGeometryBox->SetWidth(in_Expansion[1]);
	pGeometryBox->SetHeight(in_Expansion[2]);

	pGeometryBox->CreateBox(m_World.GetSpace());
	pBody->Add(pMassState);
	
	pBody->SetCollisionMesh(pGeometryBox);

	m_BodyList.push_back(pBody);
	return pBody;
}

VPhysicManager::BodyPtr VPhysicManager::CreateMesh(
	vfloat32 in_fMass,
	VBoundingMesh* in_BoundingMesh)
{
	BodyPtr pBody = CreateBody();

	VStateBoxMass* pMassState(new VStateBoxMass(pBody->GetOdeBody()));
	VGeometryMesh* pGeometryMesh(new VGeometryMesh(*in_BoundingMesh));

	pMassState->SetMass(in_fMass);
	
	//pGeometryBox->SetLength(in_Expansion[0]);
	//pGeometryBox->SetWidth(in_Expansion[1]);
	//pGeometryBox->SetHeight(in_Expansion[2]);

	pGeometryMesh->Create(m_World.GetSpace());
	pBody->Add(pMassState);
	pBody->SetCollisionMesh(pGeometryMesh);

	m_BodyList.push_back(pBody);

	return pBody;
}

VPhysicManager::Geometry VPhysicManager::CreatePlane(
	VVector3f in_Normal,
	vfloat32 in_fDistance
	)
{
	VSharedPtr<VGeometryPlane> pGeometryPlane(new VGeometryPlane());
	
	pGeometryPlane->SetPlane(graphics::VVertex3f(in_Normal[0], in_Normal[1], in_Normal[2]),in_fDistance);
	pGeometryPlane->CreatePlane(m_World.GetSpace());
	
	return pGeometryPlane;
}

void VPhysicManager::LinkBody(
      VPhysicManager::BodyPtr in_pBody1,
	  VPhysicManager::BodyPtr in_pBody2,
	  VPhysicManager::JointPtr in_LinkMode)
{
	in_LinkMode->Create(&m_World);
	in_LinkMode->AddBody(in_pBody1.Get(), in_pBody2.Get());
	in_LinkMode->Apply();
}

void VPhysicManager::DeleteCollisionMesh(VGeometry* in_Geometry)
{
	V3D_ASSERT(in_Geometry != 0);
	m_World.RemoveCollisionMesh(*in_Geometry->GetGeomID());
	delete in_Geometry;

}

VWorld* VPhysicManager::GetWorld()
{
	return &m_World;
}

vuint VPhysicManager::GetPhysicObjectCount()
{
	return static_cast<vuint>(m_BodyList.size());
}

//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------
