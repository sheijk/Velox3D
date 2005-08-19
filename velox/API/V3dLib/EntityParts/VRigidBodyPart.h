#ifndef V3D_VRIGIDBODYPART_2004_10_12_H
#define V3D_VRIGIDBODYPART_2004_10_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Entity.h>
#include <V3dLib/Math.h>
#include <V3dLib/Math/VRBTransform.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VRigidBodyPart : public VPartBase
{
public:
		
	VRigidBodyPart();

	virtual void Activate();
	virtual void Deactivate();

	/**
	 * Sets the position
	 *
	 * @param in_Position The new position
	 */
	virtual void SetPosition(const VVector3f& in_Position);

	/**
	 * Gets the position
	 *
	 * @return The position
	 */
	virtual VVector3f GetPosition() const;

	/**
	 * Gets the current rigid body transformation of this part
	 *
	 * @return The current rigid body transformation
	 */
	math::VRBTransform GetTransform();

	/**
	 * Sets the rigid body transformation of this part
	 * 
	 * @param in_Transformation The new rigid body transformation
	 */
	void SetTransform(const math::VRBTransform& in_Transformation);

	static utils::VFourCC GetDefaultId();

private:
	math::VRBTransform m_Transformation;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VRIGIDBODYPART_2004_10_12_H
