#ifndef V3D_VRIGIDBODYPART_2004_10_12_H
#define V3D_VRIGIDBODYPART_2004_10_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity.h>
#include <V3dLib/Math.h>
#include <V3dLib/EntityParts/VRBTransform.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VRigidBodyPart : public IVPart
{
public:
	typedef VRBTransform::Vector Vector;
	
	VRigidBodyPart();

	virtual void Activate();
	virtual void Deactivate();

	/**
	 * Sets the position
	 *
	 * @param in_Position The new position
	 */
	virtual void SetPosition(const Vector& in_Position);

	/**
	 * Gets the position
	 *
	 * @return The position
	 */
	virtual Vector GetPosition() const;

	/**
	 * Gets the current rigid body transformation of this part
	 *
	 * @return The current rigid body transformation
	 */
	VRBTransform GetTransform() const;

	/**
	 * Sets the rigid body transformation of this part
	 * 
	 * @param in_Transformation The new rigid body transformation
	 */
	void SetTransform(const VRBTransform& in_Transformation);

private:
	VRBTransform m_Transformation;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VRIGIDBODYPART_2004_10_12_H