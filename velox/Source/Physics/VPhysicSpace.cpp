#include <v3dLib/Physics/VPhysicSpace.h>
#include <v3dLib/Physics/VPhysicWorld.h>
#include <V3dLib/Physics/VPhysicJointGroup.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VPhysicSpace::VPhysicSpace()
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

	m_pCollisionCallbackFunction = &VPhysicSpace::CollisionCallback;
}
//-----------------------------------------------------------------------------

VPhysicSpace::~VPhysicSpace()
{
	//Destroy();
}
//-----------------------------------------------------------------------------


void VPhysicSpace::AddSubSpace(VPhysicSpace* in_Space)
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

void VPhysicSpace::SetSpaceID(dSpaceID in_SpaceID)
{
	m_SpaceID = in_SpaceID;
}
//-----------------------------------------------------------------------------

dSpaceID* VPhysicSpace::GetSpaceID()
{
	return &m_SpaceID;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::Collide()
{
	dSpaceCollide(m_SpaceID, this, m_pCollisionCallbackFunction);
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetWorld(VPhysicWorld* in_PhysicWorld)
{
	m_PhysicWorld = in_PhysicWorld;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetJointGroup(VPhysicJointGroup* in_JointGroup)
{
	m_JointGroup = in_JointGroup;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetCollisionCallback(dNearCallback* in_pCollisionCallback)
{
	m_pCollisionCallbackFunction = in_pCollisionCallback;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetDefaultCollisionCallback()
{
	m_pCollisionCallbackFunction = &VPhysicSpace::CollisionCallback;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetSurfaceMu(vfloat32 in_fMu)
{
	m_fSurfaceMu = in_fMu;
}
//-----------------------------------------------------------------------------

vfloat32 VPhysicSpace::GetSurfaceMu()
{
	return m_fSurfaceMu;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetSurfaceMu2(vfloat32 in_fMu)
{
	m_fSurfaceMu2 = in_fMu;
}
//-----------------------------------------------------------------------------

vfloat32 VPhysicSpace::GetSurfaceMu2()
{
	return m_fSurfaceMu2;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetSlip1(vfloat32 in_fSlip)
{
	m_fSlip1 = in_fSlip;
}
//-----------------------------------------------------------------------------

vfloat32 VPhysicSpace::GetSlip1()
{
	return m_fSlip1;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetSlip2(vfloat32 in_fSlip)
{
	m_fSlip2 = in_fSlip;
}
//-----------------------------------------------------------------------------

vfloat32 VPhysicSpace::GetSlip2()
{
	return m_fSlip2;
}

//-----------------------------------------------------------------------------
void VPhysicSpace::SetSoftERP(vfloat32 in_fSoftERP)
{
	m_fSoftERP = in_fSoftERP;
}

//-----------------------------------------------------------------------------
vfloat32 VPhysicSpace::GetSoftERP()
{
	return m_fSoftERP;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetSoftCFM(vfloat32 in_fSoftCFM)
{
	m_fSoftCFM = in_fSoftCFM;
}
//-----------------------------------------------------------------------------

vfloat32 VPhysicSpace::GetSoftCFM()
{
	return m_fSoftCFM;
}
//-----------------------------------------------------------------------------
void VPhysicSpace::SetSurfaceBounce(vfloat32 in_fBounce)
{
	m_fSurfaceBounce = in_fBounce;
}

//-----------------------------------------------------------------------------
vfloat32 VPhysicSpace::GetSurfaceBounce()
{
	return m_fSurfaceBounce;
}

//-----------------------------------------------------------------------------

void VPhysicSpace::SetSurfaceBounceVelocity(vfloat32 in_fBounceVelocity)
{
	m_fSurfaceBounceVelocity = in_fBounceVelocity;
}

//-----------------------------------------------------------------------------

vfloat32 VPhysicSpace::GetSurfaceBounceVelocity()
{
	return m_fSurfaceBounceVelocity;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetSurfaceMotion1(vfloat32 in_fMotion)
{
	m_fSurfaceMotion1 = in_fMotion;
}
//-----------------------------------------------------------------------------
vfloat32 VPhysicSpace::GetSurfaceMotion1()
{
	return m_fSurfaceMotion1;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetSurfaceMotion2(vfloat32 in_fMotion)
{
	m_fSurfaceMotion2 = in_fMotion;
}
//-----------------------------------------------------------------------------

vfloat32 VPhysicSpace::GetSurfaceMotion2()
{
	return m_fSurfaceMotion2;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::SetContactMode(ContactMode in_Mode)
{
	m_iContactMode = in_Mode;
}
//-----------------------------------------------------------------------------

vint VPhysicSpace::GetContactMode()
{
	return m_iContactMode;
}
//-----------------------------------------------------------------------------

void VPhysicSpace::Destroy()
{
	dSpaceDestroy(m_SpaceID);
}
//-----------------------------------------------------------------------------

void VPhysicSpace::CollisionCallback(void *data, dGeomID o1, dGeomID o2)
{
	VPhysicSpace* pSpace = static_cast<VPhysicSpace*>(data);

	//if (dGeomIsSpace (o1) || dGeomIsSpace (o2))
	if (dGeomIsSpace(o1) && dGeomIsSpace (o2))
	{
		// colliding a space with something
		SpaceList::iterator it = pSpace->m_SpaceChildList.find((dSpaceID)o1);
		
		if(it != pSpace->m_SpaceChildList.end())
			dSpaceCollide2 (o1,o2,(*it).second, (*it).second->m_pCollisionCallbackFunction);
		
		dSpaceCollide2 (o1,o2,data, pSpace->m_pCollisionCallbackFunction);
	}

	else if(dGeomIsSpace(o1) && !dGeomIsSpace(o2))
	{
		
		// collide all geoms internal to the space(s)
		// look in space child list to call according callision callback
		SpaceList::iterator it = pSpace->m_SpaceChildList.find((dSpaceID)o1);
		
		if(it != pSpace->m_SpaceChildList.end())
			dSpaceCollide((dSpaceID)o1, (*it).second, (*it).second->m_pCollisionCallbackFunction);

		//space not found ode is referering to use default callback
		dSpaceCollide ((dSpaceID)o1,data,pSpace->m_pCollisionCallbackFunction);
	}
    
	else if (!dGeomIsSpace(o2) && dGeomIsSpace(o1))
	{
		SpaceList::iterator it = pSpace->m_SpaceChildList.find((dSpaceID)o2);

		if(it != pSpace->m_SpaceChildList.end())
			dSpaceCollide((dSpaceID)o2, (*it).second, (*it).second->m_pCollisionCallbackFunction);

			//space not found ode is referering to use default callback
		dSpaceCollide ((dSpaceID)o2,data,pSpace->m_pCollisionCallbackFunction);
	}
	
	else
	{
		int	nContactCount;
		dContact contact[MaxNumContacts];
        
		dBodyID b1 = dGeomGetBody(o1);
		dBodyID b2 = dGeomGetBody(o2);

		// Don't do anything if the two bodies are connected
		if (b2 && b2 && dAreConnected (b1,b2))
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

void VPhysicSpace::NoCollisionCallback(void* data, dGeomID o1, dGeomID o2)
{
	//do nothing
}

void VPhysicSpace::SetNoCollisionCallback()
{
	m_pCollisionCallbackFunction = &VPhysicSpace::NoCollisionCallback;
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
