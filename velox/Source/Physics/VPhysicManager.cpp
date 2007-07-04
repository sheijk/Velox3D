/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VPhysicManager.h> 
#include <V3d/Physics/VStateSphereMass.h>
#include <V3d/Physics/VStateCCylinderMass.h>
#include <V3d/Physics/VGeometrySphere.h>
#include <V3d/Physics/VGeometryBox.h>
#include <V3d/Physics/VGeometryPlane.h>
#include <V3d/Physics/VGeometryMesh.h>
#include <V3d/math/VBoundingBox.h>
#include <V3d/math/VBoundingSphere.h>
#include <V3d/Physics/Bounding/VBoundingMesh.h>
#include <V3d/Physics/VGeometryCappedCylinder.h>
#include <V3d/Core.h>
#include <algorithm>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace  physics{
//-----------------------------------------------------------------------------
V3D_DECLARE_EXCEPTION(VPhysicManagerException, v3d::VException);
using namespace v3d;
using namespace v3d::math;
using namespace std;

VPhysicManager::VPhysicManager() : m_fTimeStep(0.001f)
{
	m_iAutoGeneratedCounter = 0;
	m_fTimeDelta = 0;
}
VPhysicManager::~VPhysicManager()
{
	;
}

void VPhysicManager::Update(vfloat32 in_fSeconds)
{
	//limit time of physic simulation
	//vfloat32 t= 0.0f;
	
	//see if our time is far to high (alt tabbing or initial start up)
	if(in_fSeconds > 2.0f)
		return;

	m_fTimeDelta += in_fSeconds;
	//step small fixed steps forward in time
	//vuint steps = 0;
	while( m_fTimeDelta >= m_fTimeStep )
	{
		m_World.SetWorldStep(m_fTimeStep);
		m_World.Update();
		UpdateBodies();
		UpdateJoints();
		m_fTimeDelta -= m_fTimeStep;
		//steps++;
	}
	//vout << "PhysManager steps: " << steps << vendl;
}

void VPhysicManager::UpdateBodies()
{
	typedef BodyList::const_iterator Iter;
	Iter begin = m_BodyList.begin();
	Iter end = m_BodyList.end();

	for(; begin != end; ++begin)
		(*begin)->Update();

	//for_each(begin, end, std::mem_fun(&VBody::Update));
}

void VPhysicManager::UpdateJoints()
{
  typedef JointList::const_iterator JLIter;
  JLIter it = m_UnconnectedJoints.begin();
  JLIter itEnd = m_UnconnectedJoints.end();

  for ( ; it != itEnd; ++it)
  {
	//get the 2 bodies we want to attach
	std::string reqName1 = (*it)->GetBody1Name();
	std::string reqName2 = (*it)->GetBody2Name();

   	VBody* pBody1 = QueryBodyByName(reqName1);
	VBody* pBody2 = QueryBodyByName(reqName2);
	
	if( pBody1 && pBody2 )
	{
	  (*it)->Destroy();
	  (*it)->Create(GetWorld());
	  (*it)->AddBody(pBody1, pBody2);
	  (*it)->Apply();
	  m_ConnectedJoints.push_back(*it);
	}
  }

  //remove connected joints from list
  it = m_ConnectedJoints.begin();
  itEnd = m_ConnectedJoints.end();

  for( ; it != itEnd; ++it )
  {
	JLIter findIt =	std::find(m_UnconnectedJoints.begin(), m_UnconnectedJoints.end(), (*it));
	if( findIt != m_UnconnectedJoints.end() )
	  m_UnconnectedJoints.remove(*it);
  }
}

void VPhysicManager::Delete(VBodyPart* in_Body)
{
    V3D_ASSERT( in_Body != 0 );
	m_BodyList.remove(in_Body);

	//check if we need to deactivate a joint
	JointList::const_iterator it = m_ConnectedJoints.begin();
	JointList::const_iterator itEnd = m_ConnectedJoints.end();
	for ( ; it != itEnd; ++it )
	{
		VBody* pBody1 = (*it)->GetBody1();
		VBody* pBody2 = (*it)->GetBody2();
		
		if(pBody1 == in_Body->GetBody().Get() || pBody2 == in_Body->GetBody().Get() )
			(*it)->Destroy();
	}
}

std::string VPhysicManager::QueryAvailableIdentifier(std::string in_sIdentifier)
{
	//traverse over all registered bodies and check if name is conflicting
	if( IsRegisteredName(in_sIdentifier) || in_sIdentifier == "" )
	{
		std::string autoIdentifier = "autoGenerated@";
		std::stringstream str;
		str << autoIdentifier << m_iAutoGeneratedCounter;
		m_iAutoGeneratedCounter++;
		if( ! IsRegisteredName(str.str()) )
			return str.str();
		else
			return QueryAvailableIdentifier(in_sIdentifier);
	}
	else
		return in_sIdentifier;
}

vbool VPhysicManager::IsRegisteredName(std::string in_sName)
{
	BodyList::const_iterator it = m_BodyList.begin();
	BodyList::const_iterator itEnd = m_BodyList.end();

	for ( ; it != itEnd; ++it)
	{
		std::string name = (*it)->GetBody()->GetName();
		if ( name == in_sName)
		{
			return true;
		}
	}
	return false;
}

void VPhysicManager::RequestNameChange(std::string in_sName, VBody* in_pBody)
{
	if( ! IsRegisteredName(in_sName) )
	{
		// change the name
		in_pBody->SetName(in_sName);
	}
	else
	{
		; //sorry we can't do this
	}
}

VBody* VPhysicManager::QueryBodyByName(std::string in_sName)
{
	BodyList::const_iterator it = m_BodyList.begin();
	BodyList::const_iterator itEnd = m_BodyList.end();

	for( ; it != itEnd; ++it)
	{
		std::string name = (*it)->GetBody()->GetName();
		if(name == in_sName)
			return (*it)->GetBody().Get();
	}
	return 0;
}

VPhysicManager::Geometry VPhysicManager::CreateGeom(IVBoundingVolumePart* in_pBoundingPart)
{
	VBoundingBox* pBox = in_pBoundingPart->GetBoundingBox();
	VBoundingSphere* pSphere = in_pBoundingPart->GetBoundingSphere();
	math::VPlane* pPlane = in_pBoundingPart->GetBoundingPlane();
	math::VCCylinder* pCylinder = in_pBoundingPart->GetBoundingCylinder();
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
	if(pCylinder)
	  return CreateCCylinderGeom(pCylinder);
	
	V3D_THROW(VException, "no valid bounding part found");
	Geometry retValue;
	retValue.Assign(0);
	return retValue;
}

VPhysicManager::Geometry VPhysicManager::CreateBoxGeom(VBoundingBox* in_pBoundingBox)
{
	VSharedPtr<VGeometryBox> pGeometryBox(new VGeometryBox());
	pGeometryBox->SetLength(in_pBoundingBox->GetLength().GetX());
	pGeometryBox->SetWidth(in_pBoundingBox->GetLength().GetY());
	pGeometryBox->SetHeight(in_pBoundingBox->GetLength().GetZ());

	pGeometryBox->CreateBox(m_World.GetSpace());
	return pGeometryBox;
}

VPhysicManager::Geometry VPhysicManager::CreateCCylinderGeom(VCCylinder* in_pBoundingMesh)
{
  VSharedPtr<VGeometryCappedCylinder> pCylinder(new VGeometryCappedCylinder());
  pCylinder->SetParams(in_pBoundingMesh->GetLength(), in_pBoundingMesh->GetRadius());
  pCylinder->CreateCylinder(m_World.GetSpace());
  return pCylinder;
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

VPhysicManager::BodyPtr VPhysicManager::CreateBody(std::string in_sName)
{
	//body will take ownership of odeBody
	VSharedPtr<VOdeBody> pOdeBody;
	pOdeBody.Assign(new VOdeBody());
	pOdeBody->Create(&m_World);
	BodyPtr pBody(new VBody(pOdeBody, in_sName));
	//VSharedPtr<VBodyPart> bodyPart(new VBodyPart(body));
    //return bodyPart;
	return pBody;
}

VPhysicManager::BodyPtr VPhysicManager::Create(IVBoundingVolumePart* in_pBoundingPart,
											   vfloat32 in_fMass,
											   std::string in_sIdentifierName,
											   VBodyPart* in_pPart)
{
	//check if name is not already taken

	VBoundingBox* pBox = in_pBoundingPart->GetBoundingBox();
	VBoundingSphere* pSphere = in_pBoundingPart->GetBoundingSphere();
	VBoundingMesh* pMesh = 0;
	VCCylinder* pCylinder = in_pBoundingPart->GetBoundingCylinder();

	if( in_pBoundingPart->HasBoundingMesh() )
	{
		pMesh = in_pBoundingPart->GetBoundingMesh();
	}
	BodyPtr body(0);

	if(pBox)
	{
		body = CreateBox(in_fMass, pBox->GetLength(), in_sIdentifierName);
	}
	if(pSphere)
	{
		body = CreateSphere(in_fMass, pSphere->GetRadius(), in_sIdentifierName);
	}
	if(pCylinder)
	{
		body = CreateCCylinder(in_fMass, pCylinder->GetLength(), pCylinder->GetRadius(), in_sIdentifierName);
	}
	if(pMesh)
	{
		body = CreateMesh(in_fMass, pMesh, in_sIdentifierName);
	}

	if( body.Get() )
	  m_BodyList.push_back(in_pPart);
	
	return body;
}

VPhysicManager::BodyPtr VPhysicManager::CreateSphere(
	vfloat32 in_fMass,
	vfloat32 in_fRadius,
	std::string	in_sName
	)
{
	BodyPtr pBody = CreateBody(in_sName);

	//physic stuff
	VStateSphereMass* pMassState(new VStateSphereMass(pBody->GetOdeBody())); //deleted by VBody StateList
	VSharedPtr<VGeometrySphere> pSphereGeometry(new VGeometrySphere());
	//assign values
	pMassState->SetMass(in_fMass);
	pMassState->SetRadius(in_fRadius);
	pBody->Add(pMassState);
	
	pSphereGeometry->SetSphereRadius(in_fRadius);
	pSphereGeometry->CreateSphere(m_World.GetSpace());

	pBody->SetCollisionMesh(pSphereGeometry);
	
	//m_BodyList.push_back(pBody);
	
	return pBody;
}

VPhysicManager::BodyPtr VPhysicManager::CreateBox(
	vfloat32 in_fMass,
	VVector3f in_Expansion,
	std::string in_sName)
{
	BodyPtr pBody = CreateBody(in_sName);

	VStateBoxMass* pMassState(new VStateBoxMass(pBody->GetOdeBody())); //!!!!!
	VSharedPtr<VGeometryBox> pGeometryBox(new VGeometryBox());

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

	//m_BodyList.push_back(pBody);
	return pBody;
}

VPhysicManager::BodyPtr VPhysicManager::CreateMesh(
	vfloat32 in_fMass,
	VBoundingMesh* in_BoundingMesh,
	std::string in_sName)
{
	BodyPtr pBody = CreateBody(in_sName);

	VStateBoxMass* pMassState(new VStateBoxMass(pBody->GetOdeBody()));
	VSharedPtr<VGeometryMesh> pGeometryMesh(new VGeometryMesh(*in_BoundingMesh));

	pMassState->SetMass(in_fMass);
	pGeometryMesh->Create(m_World.GetSpace());
	pBody->Add(pMassState);
	pBody->SetCollisionMesh(pGeometryMesh);

	//m_BodyList.push_back(pBody);

	return pBody;
}
VPhysicManager::BodyPtr VPhysicManager::CreateCCylinder(
  vfloat32 in_fMass,
  vfloat32 in_fLength,
  vfloat32 in_fRadius,
  std::string in_sName)
{
	BodyPtr pBody = CreateBody(in_sName);

	VStateCCylinderMass* pMassState(new VStateCCylinderMass(pBody->GetOdeBody()));
	VSharedPtr<VGeometryCappedCylinder> pGeometry(new VGeometryCappedCylinder());
	//assign values
	pMassState->SetMass(in_fMass);
	pMassState->SetRadius(in_fRadius);
	pMassState->SetLength(in_fLength);
	pBody->Add(pMassState);
	pGeometry->CreateCylinder(m_World.GetSpace());
	pGeometry->SetParams(in_fLength, in_fRadius);
	pBody->SetCollisionMesh(pGeometry);
	//m_BodyList.push_back(pBody);
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

void VPhysicManager::RegisterJoint(VJointHinge2* in_pJoint)
{
	if(in_pJoint)
	{
		JointList::const_iterator it = m_ConnectedJoints.begin();
		JointList::const_iterator itEnd = m_ConnectedJoints.end();
		for ( ; it != itEnd; ++it)
		{
			if(in_pJoint == (*it) )
				return;
		}

		m_ConnectedJoints.push_back(in_pJoint);
	}
}
void VPhysicManager::UnregisterJoint(VJointHinge2* in_pJoint)
{
	if(in_pJoint)
	{
		m_UnconnectedJoints.remove(in_pJoint);
		m_ConnectedJoints.remove(in_pJoint);
	}
}

void VPhysicManager::RefreshJoint(VBody* in_pBody)
{
	//check if body has any connections to joints
	JointList::const_iterator it = m_ConnectedJoints.begin();
	JointList::const_iterator itEnd = m_ConnectedJoints.end();

	for( ; it != itEnd; ++it)
	{
		VBody* pBody1 = (*it)->GetBody1();
		VBody* pBody2 = (*it)->GetBody2();

		//joint exists, thats connected and needs to be reseted
		if(pBody1 == in_pBody || pBody2 == in_pBody)
		{
			vout << "Physics: BodyPart position change announced" << vendl;
			(*it)->Destroy();
			(*it)->Create(this->GetWorld());
			(*it)->AddBody(pBody1, pBody2);
			(*it)->Apply();
			RegisterJoint((*it));
		}
	}
}

void VPhysicManager::RegisterJointForCreation(VJointHinge2* in_pJointPart)
{
  m_UnconnectedJoints.push_back(in_pJointPart);
}

physics::VJointHinge2* VPhysicManager::GetJointByName(std::string in_sName)
{
  JointList::const_iterator it = m_ConnectedJoints.begin();
  JointList::const_iterator itEnd = m_ConnectedJoints.end();

  for( ; it != itEnd; ++it)
  {
	if((*it)->GetName() == in_sName)
	  return (*it);
  }
  //V3D_THROW(VPhysicManagerException, "joint not found");
  //nothing found; handle gracefully
  return 0;

}

//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------

