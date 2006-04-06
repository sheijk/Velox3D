#ifndef V3D_VWORLD_05_11_04_H
#define V3D_VWORLD_05_11_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3dLib//Graphics/Geometry/VVertex3f.h>
#include <V3d/Physics/VSpace.h>
#include <V3d/Physics/VJointGroup.h>
#include <V3d/Physics/VBody.h>
#include <V3d/Core/VException.h>

#include <ode/ode.h>
#include <list>

V3D_DECLARE_EXCEPTION(PhysicException, VException);

//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
class VWorld
{
public:
	VWorld();
	virtual	~VWorld();

	void Destroy();
    void SetGravity(graphics::VVertex3f in_Gravity);
	void SetGravity(vfloat32 x, vfloat32 y, vfloat32 z);
	void Update();
	void SetWorldStep(vfloat32 in_fStep);
	vfloat32 GetWorldStep();
	dWorldID* GetWorld();
	VSpace* GetSpace();
	VJointGroup* GetJointGroup();
	void RemoveCollisionMesh(dGeomID in_GeomId);
	
private:

	dWorldID m_WorldID;
	vfloat32 m_fWorldStep;
	graphics::VVertex3f m_Gravity;
	VSpace m_Space;
	VJointGroup m_JointGroup;
};


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWORLD_05_11_04_H
