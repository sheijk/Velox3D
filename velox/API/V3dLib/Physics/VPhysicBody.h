#ifndef V3D_PHYSICBODY_05_11_04_H
#define V3D_PHYSICBODY_05_11_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3dLib/Physics/VPhysicObject.h>
#include <V3d/Entity.h>
#include <V3dLib/Physics/VPhysicPositionState.h>
#include <v3dLib/Graphics/Geometry/VVector3f.h>
#include <V3dLib/Math/VQuaternion.h>
#include <ode/ode.h>

#include "../../../Examples/Racer/Shared/VRigidBodyPart.h"
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
	
	racer::VRigidBodyPart* pBodyPart;

	void Create(VPhysicWorld* in_PhysicWorld);
	void SetPosition(vfloat32 x, vfloat32 y, vfloat32 z);
	void Activate();
    void Deactivate();
	void TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part);
	void SetCollisionBody(VPhysicGeometry* in_CollisionBodyState);
	
	/**
	 * Updates the position from ode
	 */
	void UpdatePositionFromBody();

	/**
	 * Returns the current position of the body
	 */

	graphics::VVector3f GetPosition();
			
	void Update();
	
	dBodyID* GetBodyID();

	void SetQuaternion(const vfloat32 x, const vfloat32 y,
			const vfloat32 z, const vfloat32 w);
	void SetQuaternion(const VQuatf in_Quat);


private:

	VPhysicWorld* m_pWorld;

	

protected: 

	dBodyID m_BodyID;
	
	VQuatf m_Quaternion;
	VPhysicPositionState m_PositionState;
};


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_PHYSICBODY_05_11_04_H

