#ifndef V3D_VPHYSICSPACE_2004_11_07_H
#define V3D_VPHYSICSPACE_2004_11_07_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
#include <ode/ode.h>
#include <map>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a collision space for the 
 * physic system
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VPhysicJointGroup;
class VPhysicWorld;

class VPhysicSpace
{
public:

	VPhysicSpace();
	virtual ~VPhysicSpace();

	//TODO: FIX ME
	/**
	 * MUST be explicitly called to destroy
	 * dtor can't do the job yet cos of scalar deleting destructor bug
	 */
	void Destroy();

	dSpaceID* GetSpaceID();

	/**
	 * Insert a subspace to this space for efficent collision quries
	 */
    void AddSubSpace(VPhysicSpace* in_Space);

	/**
	 * Check for collisions. Call this each frame or WorldStep
	 */
	void Collide();

	/**
	 * Set a world association in which this space exists
	 */
    void SetWorld(VPhysicWorld* in_PhysicWorld);
	
	/**
	 * Set a joint group for this space collision can be calculated
	 */
	void SetJointGroup(VPhysicJointGroup* in_JointGroup);

	/**
	 * Set a own collision callback function to be executed 
	 * on collision detect
	 */
	void SetCollisionCallback(dNearCallback* in_pCollisionCallback);

	/**
	 * Restores the default collision callback for this space
	 */
	void SetDefaultCollisionCallback();

	/**
	 * Set the Coulomb friction coefficient. This must be in the
	 * range 0 to dInfinity.
	 * 0 results in a frictionless contact, and dInfinity results in a
	 * contact that never slips. Note that frictionless contacts are 
	 * less time consuming to compute than ones with friction,
	 * and infinite friction contacts can be cheaper than 
	 * contacts with finite friction. This must always be set.
	 */
	void SetSurfaceMu(vfloat32 in_fMu);
	vfloat32 GetSurfaceMu();

	void SetSurfaceMu2(vfloat32 in_fMu);
	vfloat32 GetSurfaceMu2();
	
	/**
	 * Set force-dependent-slip (FDS) in friction direction 1.
	 *
	 * @note: default set to 0.5f
	 */
	void SetSlip1(vfloat32 in_fSlip);
	vfloat32 GetSlip1();

	/**
	 * Set force-dependent-slip (FDS) in friction direction 2.
	 *
	 * @note: default set to 0.5f
	 */
	void SetSlip2(vfloat32 in_fSlip);
	vfloat32 GetSlip2();

	/**
	 * If set, the error reduction parameter of the contact normal can
	 * be set with the soft_erp parameter. This is useful to make surfaces soft
	 *
	 * @note: default set to 0.5f
	 */
	void SetSoftERP(vfloat32 in_fSoftERP);
	vfloat32 GetSoftERP();

	/**
	 * If set, the constraint force mixing parameter of the contact normal can be
	 * set with the soft_cfm parameter. This is useful to make surfaces soft.
	 *
	 * @note: default set to 0.5f
	 */
	void SetSoftCFM(vfloat32 in_fSoftCFM);
	vfloat32 GetSoftCFM();

	/**
	 * Restitution parameter (0..1). 0 means the surfaces are not bouncy at all,
	 * 1 is maximum bouncyness. This is only set if the corresponding flag
	 * is set in mode.
	 *
	 * @note: default set to 0
	 */
	void SetSurfaceBounce(vfloat32 in_fBounce);
	vfloat32 GetSurfaceBounce();

	/**
	 * The minimum incoming velocity necessary for bounce.
	 * Incoming velocities below this will effectively have
	 * a bounce parameter of 0. This is only set if the 
	 * corresponding flag is set in mode.	
	 *
	 * @note: default set to 0
	 */
	void SetSurfaceBounceVelocity(vfloat32 in_fBounceVelocity);
	vfloat32 GetSurfaceBounceVelocity();

	/**
	 * If set, the contact surface is assumed to be moving 
	 * independently of the motion of the bodies. This is kind
	 * of like a conveyor belt running over the surface. When this
	 * flag is set, motion1 defines the surface velocity in
	 * friction direction 1.
	 *
	 * @note: default set to 0
	 */
	void SetSurfaceMotion1(vfloat32 in_fMotion);
    vfloat32 GetSurfaceMotion1();

	/**
	 * If set, the contact surface is assumed to be moving 
	 * independently of the motion of the bodies. This is kind
	 * of like a conveyor belt running over the surface. When this
	 * flag is set, motion2 defines the surface velocity in
	 * friction direction 2.
	 *
	 * @note: default set to 0
	 */
	void SetSurfaceMotion2(vfloat32 in_fMotion);
	vfloat32 GetSurfaceMotion2();

	/**
	 * Set this to avoid collision test in this space
	 */
	void SetNoCollisionCallback();

	/**
	 * Define behavior of the contact mode that should be applied
	 * by a given contact
	 *
	 * @note: default is set to Slip1 | Slip2 | SoftERP | SoftCFM
	 *							| ApproximationALL
	 */
	enum ContactMode
	{
		Mu2					= 0x001,
		ForceDirection		= 0x002,
		Bounce				= 0x004,
		SoftERP				= 0x008,
		SoftCFM				= 0x010,
		Motion1				= 0x020,
		Motion2				= 0x040,
		Slip1				= 0x080,
		Slip2				= 0x100,
		Approximation		= 0x0000,
		Approximation1		= 0x1000,
		Approximation2		= 0x2000,
		ApproximationALL	= 0x3000
	};

	/**
	* Set this mode by INCLUSIVE OR (|) the ContactMode 
	*
	* @note: default is set to Slip1 | Slip2 | SoftERP | SoftCFM
	*							| ApproximationALL
	*/
	void SetContactMode(ContactMode in_Mode);
	vint GetContactMode();



private:


	typedef std::map<dSpaceID, VPhysicSpace*> SpaceList;
	SpaceList m_SpaceChildList;

	enum CollisionConstants
	{
		MaxNumContacts = 10
	};
	

	VPhysicSpace(const VPhysicSpace&);
	VPhysicSpace& operator=(const VPhysicSpace&);

	void SetSpaceID(dSpaceID in_SpaceID);
	
	dSpaceID m_SpaceID;

	vint m_iContactMode;
	vfloat32 m_fSurfaceMu;
	vfloat32 m_fSurfaceMu2;
	vfloat32 m_fSlip1; 
	vfloat32 m_fSlip2; 
	vfloat32 m_fSoftERP;
	vfloat32 m_fSoftCFM;
	vfloat32 m_fSurfaceBounce;
	vfloat32 m_fSurfaceBounceVelocity;
	vfloat32 m_fSurfaceMotion1;
	vfloat32 m_fSurfaceMotion2;
	VPhysicWorld* m_PhysicWorld;
	VPhysicJointGroup* m_JointGroup;
	dNearCallback* m_pCollisionCallbackFunction;
		
	static void CollisionCallback(void *data, dGeomID o1, dGeomID o2);
	static void NoCollisionCallback(void *data, dGeomID o1, dGeomID o2);
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICSPACE_2004_11_07_H
