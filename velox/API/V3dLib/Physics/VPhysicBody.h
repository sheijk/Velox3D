#ifndef V3D_PHYSICBODY_05_11_04_H
#define V3D_PHYSICBODY_05_11_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3dLib/Physics/VPhysicObject.h>
#include <V3d/Entity.h>
#include <V3dLib/Physics/VPhysicPositionState.h>
#include <v3dLib//Graphics/Geometry/VVertex3f.h>
#include <V3dLib/Math/VQuaternion.h>
#include <ode/ode.h>

#include <V3dLib/EntityParts/VRigidBodyPart.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

class VPhysicWorld;
class VPhysicGeometry;

class VPhysicBody : public VPhysicObject, public entity::IVPart
{
public:

	typedef VVector<vfloat32, 3> Position;
		
	VPhysicBody();
	virtual ~VPhysicBody();

	void Create(VPhysicWorld* in_PhysicWorld);
	void SetTransformation();
	void SetPosition(vfloat32 x, vfloat32 y, vfloat32 z);

	// IVPart derived
	void Activate();
    void Deactivate();

	virtual vuint DependencyCount() const;
	virtual Dependency GetDependencyInfo(vuint in_nIndex) const;
	virtual void Connect(IVPart::Location in_Location, 
		const utils::VFourCC& in_Id, entity::IVPart& in_Part);
	virtual void Disconnect(IVPart::Location in_Location, 
		const utils::VFourCC& in_Id, entity::IVPart& in_Part);
	virtual vbool IsReady() const;
	
	static utils::VFourCC GetDefaultId();

	void SetCollisionBody(VPhysicGeometry* in_CollisionBodyState);
	
	/**
	 * Updates the position from ode
	 */
	void UpdatePositionFromBody();

	/**
	 * Returns the current position of the body
	 */
	graphics::VVertex3f GetPosition();
			
	void Update();
	
	dBodyID* GetBodyID();

	void SetQuaternion(const vfloat32 x, const vfloat32 y,
			const vfloat32 z, const vfloat32 w);
	void SetQuaternion(const VQuatf in_Quat);


private:

	VPhysicWorld* m_pWorld;

	

protected: 

	dBodyID m_BodyID;
	entity::VRigidBodyPart* pBodyPart;
	VQuatf m_Quaternion;
	VPhysicPositionState m_PositionState;
};


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_PHYSICBODY_05_11_04_H

