/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VJOINT_2004_11_07_H
#define V3D_VJOINT_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3d/Physics/VWorld.h>
#include <V3d/Physics/VJointGroup.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents an abstract ode joint
 * encapsulates ODE function calls
 *
 * @author: ins
 */
class VWorld;
class VJointGroup;
class VBody;

class VJoint
{
public:

	VJoint();
	virtual ~VJoint();

	//TODO: FIX ME
	/**
	 * MUST be explicitly called to destroy
	 * dtor can't do the job yet cos of scalar deleting destructor bug
	 */
	void Destroy();

	/**
	 * explcit assign a joint group
	 * @note: this is automatical done by AddWorld
	 */
	void AddJointGroup(VJointGroup* in_pJointGroup);

	/**
	 * Low stop angle or position. Setting this to -dInfinity 
	 * (the default value) turns off the low stop. For rotational
	 * joints, this stop must be greater than - pi to be effective.
	 */
	void SetLowStop(vfloat32 in_fLowStop);
	vfloat32 GetLowStop();

	/**
	 * High stop angle or position. Setting this to dInfinity 
	 * (the default value) turns off the high stop. For rotational
	 * joints, this stop must be less than pi to be effective.
	 * If the high stop is less than the low stop then both stops
	 * will be ineffective.
	 */
	void SetHighStop(vfloat32 in_fHighStop);
	vfloat32 GetHighStop();

	/**
	 * Desired motor velocity (this will be an angular or linear velocity).
	 */
	void SetVelocity(vfloat32 in_fVelocity);
	vfloat32 GetVelocity();

	/**
	 * The maximum force or torque that the motor will use to achieve the
	 * desired velocity. This must always be greater than or equal to zero.
	 * Setting this to zero (the default value) turns off the motor.
	 */
	void SetMaxForce(vfloat32 in_fMaxForce);
	vfloat32 GetMaxForce();

	/**
	 * The current joint stop/motor implementation has a small problem:
	 * when the joint is at one stop and the motor is set to move it away
	 * from the stop, too much force may be applied for one time step, 
	 * causing a ``jumping'' motion. This fudge factor is used to scale this
	 * excess force. It should have a value between zero and one
	 * (the default value). If the jumping motion is too visible in a joint,
	 * the value can be reduced. Making this value too small can prevent the 
	 * motor from being able to move the joint away from a stop.
	 */
	void SetFudgeFactor(vfloat32 in_fFudgeFactor);
	vfloat32 GetFudgeFactor();

	/**
	 * The bouncyness of the stops. This is a restitution parameter
	 * in the range 0..1. 0 means the stops are not bouncy at all,
	 * 1 means maximum bouncyness.
	 */
	void SetBounce(vfloat32 in_fBounce);
	vfloat32 GetBounce();

	/**
	 * The constraint force mixing (CFM) value used when not at a stop.
	 */
	void SetCFM(vfloat32 in_fCFM);
	vfloat32 GetCFM();

	/**
	 * The error reduction parameter (ERP) used by the stops.
	 */
    void SetStopERP(vfloat32 in_fStopERP);
	vfloat32 GetStopERP();

	/**
	 * The constraint force mixing (CFM) value used by the stops.
	 * Together with the ERP value this can be used to get spongy 
	 * or soft stops. Note that this is intended for unpowered joints,
	 * it does not really work as expected when a powered joint 
	 * reaches its limit.
	 */
	void SetStopCFM(vfloat32 in_fStopCFM);
	vfloat32 GetStopCFM();

	/**
	 * Suspension error reduction parameter (ERP).
	 * Currently this is only implemented on the hinge-2 joint.
	 */
	void SetSuspensionERP(vfloat32 in_fSuspensionERP);
	vfloat32 GetSuspensionERP();

	/**
	 * Suspension constraint force mixing (CFM) value.
	 * Currently this is only implemented on the hinge-2 joint.
	 */
	void SetSuspensionCFM(vfloat32 in_fSuspensionCFM);
	vfloat32 GetSuspensionCFM();

	void SetVelocity2(vfloat32 in_fVelocity2);
	vfloat32 GetVelocity2();

	virtual void Create(VWorld* in_PhysicWorld) = 0;
	virtual void AddBody(VBody* in_pBody1, VBody* in_pBody2) = 0;
	virtual void Apply() = 0;


private:

	VJoint(const VJoint&);
	VJoint& operator=(const VJoint&);

protected:

	/**
	 * Assign the joint a given world.
	 * @note: automaticaly assignes the joint group to 0
	 */
	void AddWorld(VWorld* in_pPhysicWorld);

	dJointID m_JointID;
	VWorld* m_pPhysicWorld;
	VJointGroup* m_pJointGroup;

	vfloat32 m_fLowStop;
	vfloat32 m_fHighStop;
	vfloat32 m_fVelocity;
	vfloat32 m_fVelocity2;
	vfloat32 m_fMaxForce;
	vfloat32 m_fFudgeFactor;
	vfloat32 m_fBounce;
	vfloat32 m_fCFM;
	vfloat32 m_fStopERP;
	vfloat32 m_fStopCFM;
	vfloat32 m_fSuspensionCFM;
	vfloat32 m_fSuspensionERP;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VJOINT_2004_11_07_H

