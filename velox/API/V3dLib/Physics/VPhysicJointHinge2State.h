#ifndef V3D_VPHYSICJOINTHINGE2STATE_2004_11_07_H
#define V3D_VPHYSICJOINTHINGE2STATE_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3dLib/Physics/VPhysicJoint.h>
#include <V3dLib/Physics/VPhysicState.h>
#include <V3dLib/Graphics/Geometry/VVector3f.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a ode hinge2 joint
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VPhysicBody;

class VPhysicJointHinge2State : public VPhysicJoint, public VPhysicState
{
public:

	VPhysicJointHinge2State();
	virtual ~VPhysicJointHinge2State();

	void Create(VPhysicWorld* in_PhysicWorld);
	void AddBody(VPhysicBody* in_pBody1, VPhysicBody* in_pBody2);

	void SetAxis1(graphics::VVector3f in_Axis);
	void SetAxis1(vfloat32 x, vfloat32 y, vfloat32 z);
	void SetAxis2(graphics::VVector3f in_Axis);
	void SetAxis2(vfloat32 x, vfloat32 y, vfloat32 z);
	void SetAnchor(graphics::VVector3f in_Anchor);
	void SetAnchor(vfloat32 x, vfloat32 y, vfloat32 z);
	void SetMaxForce2(vfloat32 in_fMaxForce2);

	vfloat32 GetMaxForce2();
	

	vfloat32 GetAnchorAngle1();

	graphics::VVector3f  GetAxis1();
	graphics::VVector3f  GetAxis2();
	graphics::VVector3f  GetAnchor();
	virtual void Apply();

private:
	void SetParameters();

	VPhysicJointHinge2State(const &VPhysicJointHinge2State);
	VPhysicJointHinge2State& operator=(const VPhysicJointHinge2State&);

	VPhysicBody* m_pBody1;
	VPhysicBody* m_pBody2;

	vfloat32 m_fMaxForce2;

	graphics::VVector3f m_Axis1;
	graphics::VVector3f m_Axis2;
	graphics::VVector3f m_Anchor;

};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICJOINTHINGE2STATE_2004_11_07_H
