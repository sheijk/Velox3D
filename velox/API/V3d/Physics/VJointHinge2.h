#ifndef V3D_VJOINTHINGE2_2004_11_07_H
#define V3D_VJOINTHINGE2_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3d/Physics/VJoint.h>
#include <V3dLib/Graphics/Geometry/VVertex3f.h>
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

class VBody;

class VJointHinge2: public VJoint
{
public:

	VJointHinge2();
	virtual ~VJointHinge2();

	void Create(VWorld* in_PhysicWorld);
	void AddBody(VBody* in_pBody1, VBody* in_pBody2);

	void SetAxis1(graphics::VVertex3f in_Axis);
	void SetAxis1(vfloat32 x, vfloat32 y, vfloat32 z);
	void SetAxis2(graphics::VVertex3f in_Axis);
	void SetAxis2(vfloat32 x, vfloat32 y, vfloat32 z);
	void SetAnchor(graphics::VVertex3f in_Anchor);
	void SetAnchor(vfloat32 x, vfloat32 y, vfloat32 z);
	void SetMaxForce2(vfloat32 in_fMaxForce2);

	vfloat32 GetMaxForce2();
	vfloat32 GetAnchorAngle1();

	graphics::VVertex3f  GetAxis1();
	graphics::VVertex3f  GetAxis2();
	graphics::VVertex3f  GetAnchor();
	virtual void Apply();

private:
	void SetParameters();

	VJointHinge2(const &VJointHinge2);
	VJointHinge2& operator=(const VJointHinge2&);

	VBody* m_pBody1;
	VBody* m_pBody2;

	vfloat32 m_fMaxForce2;

	graphics::VVertex3f m_Axis1;
	graphics::VVertex3f m_Axis2;
	graphics::VVertex3f m_Anchor;

};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VJOINTHINGE2_2004_11_07_H
