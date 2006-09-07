/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Physics/VSpace.h>
#include <v3d/Physics/VWorld.h>
#include <V3d/Physics/VJointGroup.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VSpace::VSpace()
{

	m_SpaceID = dSimpleSpaceCreate(0); 

	m_JointGroup				= 0;
	m_PhysicWorld				= 0;
	m_fSurfaceMu				= 0.5f;
	m_fSurfaceMu2				= 0.5f;
	m_fSlip1					= 0.1f;
	m_fSlip2					= 0.1f;
	m_fSoftCFM					= 0.3f;
	m_fSoftERP					= 0.5f;
	m_fSurfaceBounce			= 0.0f;
	m_fSurfaceBounceVelocity	= 0.0f;
	m_fSurfaceMotion1			= 0.0f;
	m_fSurfaceMotion2			= 0.0f;
	m_iContactMode				= /*Slip1 | Slip2 | SoftERP | SoftCFM
									| ApproximationALL;*/

	dContactSlip1 | dContactSlip2 |
		dContactSoftERP | dContactSoftCFM | dContactApprox1;

	m_pCollisionCallbackFunction = &VSpace::CollisionCallback;
}

VSpace::VSpace(VSpace* in_pPhysicSpace)
{

	m_SpaceID = dSimpleSpaceCreate(*in_pPhysicSpace->GetSpaceID()); 

	m_JointGroup				= 0;
	m_PhysicWorld				= 0;
	m_fSurfaceMu				= 0.5f;
	m_fSurfaceMu2				= 0.5f;
	m_fSlip1					= 0.1f;
	m_fSlip2					= 0.1f;
	m_fSoftCFM					= 0.3f;
	m_fSoftERP					= 0.5f;
	m_fSurfaceBounce			= 0.0f;
	m_fSurfaceBounceVelocity	= 0.0f;
	m_fSurfaceMotion1			= 0.0f;
	m_fSurfaceMotion2			= 0.0f;
	m_iContactMode				= /*Slip1 | Slip2 | SoftERP | SoftCFM
								  | ApproximationALL;*/

								  dContactSlip1 | dContactSlip2 |
								  dContactSoftERP | dContactSoftCFM | dContactApprox1;

	m_pCollisionCallbackFunction = &VSpace::CollisionCallback;
}


//-----------------------------------------------------------------------------

VSpace::~VSpace()
{
	//Destroy();
}
//-----------------------------------------------------------------------------


void VSpace::AddSubSpace(VSpace* in_Space)
{
	in_Space->SetSpaceID(dSimpleSpaceCreate(m_SpaceID));

	V3D_ASSERT(m_PhysicWorld != 0);
	V3D_ASSERT(m_JointGroup != 0);

	in_Space->SetWorld(m_PhysicWorld);
	in_Space->SetJointGroup(m_JointGroup);

	//insert space pointer to a child list
	m_SpaceChildList[*in_Space->GetSpaceID()] = in_Space;
}
//-----------------------------------------------------------------------------

void VSpace::SetSpaceID(dSpaceID in_SpaceID)
{
	m_SpaceID = in_SpaceID;
}
//-----------------------------------------------------------------------------

dSpaceID* VSpace::GetSpaceID()
{
	return &m_SpaceID;
}
//-----------------------------------------------------------------------------

void VSpace::Collide()
{
	dSpaceCollide(m_SpaceID, this, m_pCollisionCallbackFunction);
}
//-----------------------------------------------------------------------------

void VSpace::SetWorld(VWorld* in_PhysicWorld)
{
	m_PhysicWorld = in_PhysicWorld;
}
//-----------------------------------------------------------------------------

void VSpace::SetJointGroup(VJointGroup* in_JointGroup)
{
	m_JointGroup = in_JointGroup;
}
//-----------------------------------------------------------------------------

void VSpace::SetCollisionCallback(dNearCallback* in_pCollisionCallback)
{
	m_pCollisionCallbackFunction = in_pCollisionCallback;
}
//-----------------------------------------------------------------------------

void VSpace::SetDefaultCollisionCallback()
{
	m_pCollisionCallbackFunction = &VSpace::CollisionCallback;
}
//-----------------------------------------------------------------------------

void VSpace::SetSurfaceMu(vfloat32 in_fMu)
{
	m_fSurfaceMu = in_fMu;
}
//-----------------------------------------------------------------------------

vfloat32 VSpace::GetSurfaceMu()
{
	return m_fSurfaceMu;
}
//-----------------------------------------------------------------------------

void VSpace::SetSurfaceMu2(vfloat32 in_fMu)
{
	m_fSurfaceMu2 = in_fMu;
}
//-----------------------------------------------------------------------------

vfloat32 VSpace::GetSurfaceMu2()
{
	return m_fSurfaceMu2;
}
//-----------------------------------------------------------------------------

void VSpace::SetSlip1(vfloat32 in_fSlip)
{
	m_fSlip1 = in_fSlip;
}
//-----------------------------------------------------------------------------

vfloat32 VSpace::GetSlip1()
{
	return m_fSlip1;
}
//-----------------------------------------------------------------------------

void VSpace::SetSlip2(vfloat32 in_fSlip)
{
	m_fSlip2 = in_fSlip;
}
//-----------------------------------------------------------------------------

vfloat32 VSpace::GetSlip2()
{
	return m_fSlip2;
}

//-----------------------------------------------------------------------------
void VSpace::SetSoftERP(vfloat32 in_fSoftERP)
{
	m_fSoftERP = in_fSoftERP;
}

//-----------------------------------------------------------------------------
vfloat32 VSpace::GetSoftERP()
{
	return m_fSoftERP;
}
//-----------------------------------------------------------------------------

void VSpace::SetSoftCFM(vfloat32 in_fSoftCFM)
{
	m_fSoftCFM = in_fSoftCFM;
}
//-----------------------------------------------------------------------------

vfloat32 VSpace::GetSoftCFM()
{
	return m_fSoftCFM;
}
//-----------------------------------------------------------------------------
void VSpace::SetSurfaceBounce(vfloat32 in_fBounce)
{
	m_fSurfaceBounce = in_fBounce;
}

//-----------------------------------------------------------------------------
vfloat32 VSpace::GetSurfaceBounce()
{
	return m_fSurfaceBounce;
}

//-----------------------------------------------------------------------------

void VSpace::SetSurfaceBounceVelocity(vfloat32 in_fBounceVelocity)
{
	m_fSurfaceBounceVelocity = in_fBounceVelocity;
}

//-----------------------------------------------------------------------------

vfloat32 VSpace::GetSurfaceBounceVelocity()
{
	return m_fSurfaceBounceVelocity;
}
//-----------------------------------------------------------------------------

void VSpace::SetSurfaceMotion1(vfloat32 in_fMotion)
{
	m_fSurfaceMotion1 = in_fMotion;
}
//-----------------------------------------------------------------------------
vfloat32 VSpace::GetSurfaceMotion1()
{
	return m_fSurfaceMotion1;
}
//-----------------------------------------------------------------------------

void VSpace::SetSurfaceMotion2(vfloat32 in_fMotion)
{
	m_fSurfaceMotion2 = in_fMotion;
}
//-----------------------------------------------------------------------------

vfloat32 VSpace::GetSurfaceMotion2()
{
	return m_fSurfaceMotion2;
}
//-----------------------------------------------------------------------------

void VSpace::SetContactMode(ContactMode in_Mode)
{
	m_iContactMode = in_Mode;
}
//-----------------------------------------------------------------------------

vint VSpace::GetContactMode()
{
	return m_iContactMode;
}
//-----------------------------------------------------------------------------

void VSpace::Destroy()
{
	dSpaceDestroy(m_SpaceID);
}
//-----------------------------------------------------------------------------

void VSpace::CollisionCallback(void *data, dGeomID o1, dGeomID o2)
{
	VSpace* pSpace = static_cast<VSpace*>(data);

	if (dGeomIsSpace (o1) || dGeomIsSpace (o2))
	//if (dGeomIsSpace(o1) && dGeomIsSpace (o2)) //both geoms are spaces
	{
		// colliding a space with something
		SpaceList::iterator it = pSpace->m_SpaceChildList.find((dSpaceID)o1);
		
		if(it != pSpace->m_SpaceChildList.end())
			dSpaceCollide2 (o1,o2,(*it).second, (*it).second->m_pCollisionCallbackFunction);
		
		dSpaceCollide2 (o1,o2,data, pSpace->m_pCollisionCallbackFunction);
	}

	//else if(dGeomIsSpace(o1) && !dGeomIsSpace(o2))
	//{
	//	
	//	// collide all geoms internal to the space(s)
	//	// look in space child list to call according callision callback
	//	SpaceList::iterator it = pSpace->m_SpaceChildList.find((dSpaceID)o1);
	//	
	//	if(it != pSpace->m_SpaceChildList.end())
	//		dSpaceCollide((dSpaceID)o1, (*it).second, (*it).second->m_pCollisionCallbackFunction);

	//	//space not found ode is referering to use default callback
	//	dSpaceCollide ((dSpaceID)o1,data,pSpace->m_pCollisionCallbackFunction);
	//}
 //   
	//else if (!dGeomIsSpace(o2) && dGeomIsSpace(o1))
	//{
	//	SpaceList::iterator it = pSpace->m_SpaceChildList.find((dSpaceID)o2);

	//	if(it != pSpace->m_SpaceChildList.end())
	//		dSpaceCollide((dSpaceID)o2, (*it).second, (*it).second->m_pCollisionCallbackFunction);

	//		//space not found ode is referering to use default callback
	//	dSpaceCollide ((dSpaceID)o2,data,pSpace->m_pCollisionCallbackFunction);
	//}
	//
	else
	{
		int	nContactCount;
		dContact contact[MaxNumContacts];
        
		dBodyID b1 = dGeomGetBody(o1);
		dBodyID b2 = dGeomGetBody(o2);

		// Don't do anything if the two bodies are connected
		if (b1 && b2 && dAreConnected (b1,b2))
			return;

		nContactCount = dCollide (o1, o2, MaxNumContacts, &contact[0].geom,
						sizeof(dContact));

		if (nContactCount > 0)
		{
			for (vint i=0; i<nContactCount; i++)
			{
				// Note that if params are not properly set they won't be
				// applied by ode
				contact[i].surface.mode			= pSpace->m_iContactMode;
				contact[i].surface.bounce		= pSpace->m_fSurfaceBounce;
				contact[i].surface.bounce_vel	= pSpace->m_fSurfaceBounceVelocity;
				contact[i].surface.mu			= pSpace->m_fSurfaceMu;
				contact[i].surface.mu2			= pSpace->m_fSurfaceMu2;
				contact[i].surface.slip1		= pSpace->m_fSlip1;
				contact[i].surface.slip2		= pSpace->m_fSlip2;
				contact[i].surface.soft_erp		= pSpace->m_fSoftERP;
				contact[i].surface.soft_cfm		= pSpace->m_fSoftCFM;
				contact[i].surface.motion1		= pSpace->m_fSurfaceMotion1;
				contact[i].surface.motion2		= pSpace->m_fSurfaceMotion2;
				
				V3D_ASSERT(pSpace->m_PhysicWorld != 0);
				V3D_ASSERT(pSpace->m_JointGroup != 0);

				dJointID c = dJointCreateContact (*pSpace->m_PhysicWorld->GetWorld(),
					*pSpace->m_JointGroup->GetJointGroupID(),&contact[i]);
				
				dJointAttach (c, dGeomGetBody(contact[i].geom.g1),
					dGeomGetBody(contact[i].geom.g2));
			}
		}
	}
}

void VSpace::NoCollisionCallback(void* data, dGeomID o1, dGeomID o2)
{
	//do nothing
}

void VSpace::SetNoCollisionCallback()
{
	m_pCollisionCallbackFunction = &VSpace::NoCollisionCallback;
}

vuint VSpace::GetMaxNumContacts()
{
	return VSpace::MaxNumContacts;
}
//-----------------------------------------------------------------------------
//vint VPhysicSpace::m_iContactMode = 0;
//vfloat32 VPhysicSpace::m_fSurfaceMu = 0;
//vfloat32 VPhysicSpace::m_fSurfaceMu2 = 0;
//vfloat32 VPhysicSpace::m_fSlip1 = 0;
//vfloat32 VPhysicSpace::m_fSlip2 = 0;
//vfloat32 VPhysicSpace::m_fSoftERP = 0;
//vfloat32 VPhysicSpace::m_fSoftCFM = 0;
//vfloat32 VPhysicSpace::m_fSurfaceBounce = 0;
//vfloat32 VPhysicSpace::m_fSurfaceBounceVelocity = 0;
//vfloat32 VPhysicSpace::m_fSurfaceMotion1 = 0;
//vfloat32 VPhysicSpace::m_fSurfaceMotion2 = 0;
//VPhysicWorld* VPhysicSpace::m_PhysicWorld = 0;
//VPhysicJointGroup* VPhysicSpace::m_JointGroup = 0;
//dNearCallback* VPhysicSpace::m_pCollisionCallbackFunction = 0;
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

