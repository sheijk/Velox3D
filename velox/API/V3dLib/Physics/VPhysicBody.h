#ifndef V3D_PHYSICBODY_05_11_04_H
#define V3D_PHYSICBODY_05_11_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3dLib/Physics/VPhysicObject.h>
#include <V3d/Entity.h>
#include <V3dLib/Physics/VPhysicPositionState.h>
#include <v3dLib//Graphics/Geometry/VVertex3f.h>
#include <V3d/Math/VQuaternion.h>
#include <ode/ode.h>

#include <V3dLib/EntityParts/VRigidBodyPart.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

class VPhysicWorld;
class VPhysicGeometry;

class VPhysicBody : public VPhysicObject, public entity::VPartBase
{
public:

//	entity::VPartConnection<entity::VRigidBodyPart> partConnection;

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

	static std::string GetDefaultId();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:

	VPhysicWorld* m_pWorld;

	

protected: 

	dBodyID m_BodyID;
	entity::VPartConnection<entity::VRigidBodyPart> pBodyPart;
//	entity::VRigidBodyPart* pBodyPart;
	VQuatf m_Quaternion;
	VPhysicPositionState m_PositionState;
};


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d

V3D_TYPEINFO_WITHPARENT(v3d::physics::VPhysicBody, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_PHYSICBODY_05_11_04_H

