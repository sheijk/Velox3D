#ifndef V3D_VPHYSICWORLD_05_11_04_H
#define V3D_VPHYSICWORLD_05_11_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3dLib//Graphics/Geometry/VVertex3f.h>
#include <V3dLib/Physics/VPhysicSpace.h>
#include <V3dLib/Physics/VPhysicJointGroup.h>
#include <V3dLib/Physics/VPhysicBody.h>
#include <V3d/Entity.h>
#include <ode/ode.h>

#include <list>

V3D_DECLARE_EXCEPTION(PhysicWorldException, VException);

//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
class VPhysicWorld
{
public:
	VPhysicWorld();
	virtual	~VPhysicWorld();

	//TODO: FIX ME
	/**
	 * MUST be explicitly called to destroy
	 * dtor can't do the job yet cos of scalar deleting destructor bug
	 */
	void Destroy();

    void SetGravity(graphics::VVertex3f in_Gravity);
	void SetGravity(vfloat32 x, vfloat32 y, vfloat32 z);

	void Update();
	void SetWorldStep(vfloat32 in_fStep);
	vfloat32 GetWorldStep();
	
	/**
	 * Creates a body in this world with an associated entity part
	 * @note: Bodies and pairs will be delete when world gets destroyed
	 */
	VPhysicBody* CreateBody();
	entity::VEntity::PartPtr* GetBodyPart(VPhysicBody* in_Body);
	
    
	dWorldID* GetWorld();
	VPhysicSpace* GetSpace();
	VPhysicJointGroup* GetJointGroup();

	
private:

	void DeleteBodyPairList();
	void UpdateBodyList();

    struct PhysicBodyPair
	{
		VPhysicBody* pBody;
		entity::VEntity::PartPtr* pBodyPart;
	};

	typedef std::list<PhysicBodyPair>::iterator IterBodyList;

	dWorldID m_WorldID;
	vfloat32 m_fWorldStep;
	graphics::VVertex3f m_Gravity;
	VPhysicSpace m_Space; // a world without space does not make sense
	VPhysicJointGroup m_JointGroup;

	std::list<PhysicBodyPair> m_PhysicBodyList;

};


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICWORLD_05_11_04_H
