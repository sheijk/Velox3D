#include <v3dLib/Physics/VPhysicWorld.h>
#include <v3dLib/Physics/VPhysicBody.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------

VPhysicWorld::VPhysicWorld()
{
	m_Gravity.x = 0;
	m_Gravity.y = 0;
	m_Gravity.z = 1.5f;
	m_fWorldStep = 0.05f;

	m_WorldID = dWorldCreate();
	
	m_Space.SetWorld(this);
	m_Space.SetJointGroup(&m_JointGroup);
	SetGravity(m_Gravity);
}

VPhysicWorld::~VPhysicWorld()
{
}

void VPhysicWorld::SetGravity(graphics::VVector3f in_Gravity)
{
	m_Gravity = in_Gravity;
	dWorldSetGravity(m_WorldID ,m_Gravity.x,m_Gravity.y,m_Gravity.z);
}

void VPhysicWorld::SetGravity(vfloat32 x, vfloat32 y, vfloat32 z)
{
	m_Gravity.x = x;
	m_Gravity.y = y;
	m_Gravity.z = z;

	dWorldSetGravity(m_WorldID ,m_Gravity.x,m_Gravity.y,m_Gravity.z);
}

dWorldID* VPhysicWorld::GetWorld()
{
	return &m_WorldID;
}

void VPhysicWorld::SetWorldStep(vfloat32 in_fStep)
{
	m_fWorldStep = in_fStep;
}

vfloat32 VPhysicWorld::GetWorldStep()
{
	return m_fWorldStep;
}

VPhysicSpace* VPhysicWorld::GetSpace()
{
	return &m_Space;
}

VPhysicJointGroup* VPhysicWorld::GetJointGroup()
{
	return &m_JointGroup;
}

VPhysicBody* VPhysicWorld::CreateBody()
{
	VPhysicBody* pBody = new VPhysicBody;
    entity::VEntity::PartPtr* pBodyPart = new entity::VEntity::PartPtr;
	pBodyPart->Assign(pBody);
	pBody->Create(this);

	PhysicBodyPair pair;
	pair.pBody = pBody;
	pair.pBodyPart = pBodyPart;

	m_PhysicBodyList.push_back(pair);

	return pair.pBody;
}

entity::VEntity::PartPtr* VPhysicWorld::GetBodyPart(VPhysicBody* in_Body)
{
	IterBodyList iterBegin	= m_PhysicBodyList.begin();
	IterBodyList iterEnd	= m_PhysicBodyList.end();

	for(; iterBegin != iterEnd; ++iterBegin)
	{
		if((*iterBegin).pBody == in_Body)
			return (*iterBegin).pBodyPart;
	}

	//body part not found!
	V3D_THROW(PhysicWorldException, "no entity part found coresponding to this body!");
	return 0;
}

void VPhysicWorld::DeleteBodyPairList()
{
	IterBodyList iterBegin	= m_PhysicBodyList.begin();
	IterBodyList iterEnd	= m_PhysicBodyList.end();

	for(; iterBegin != iterEnd; ++iterBegin)
	{
		delete ((*iterBegin).pBody);
		//delete ((*iterBegin).pBodyPart); //entity will be deleted by it's part
	}
}

void VPhysicWorld::UpdateBodyList()
{
	IterBodyList iterBegin	= m_PhysicBodyList.begin();
	IterBodyList iterEnd	= m_PhysicBodyList.end();

	for(; iterBegin != iterEnd; ++iterBegin)
	{
		(*iterBegin).pBody->Update();
	}
}

void VPhysicWorld::Update()
{
	m_Space.Collide();
	dWorldStep(m_WorldID, m_fWorldStep);
	UpdateBodyList();
	m_JointGroup.Empty();
}

void VPhysicWorld::Destroy()
{
	m_JointGroup.Destroy();
	m_Space.Destroy();

	DeleteBodyPairList();
	dWorldDestroy(m_WorldID);
}

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
