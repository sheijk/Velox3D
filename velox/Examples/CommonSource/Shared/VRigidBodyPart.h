#ifndef V3D_VRIGIDBODYPART_2004_10_12_H
#define V3D_VRIGIDBODYPART_2004_10_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity.h>
#include <V3d/Math.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace racer {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VRigidBodyPart : public entity::IVPart
{
public:
	typedef math::VVector<vfloat32, 3>  PositionVector;

	VRigidBodyPart();

	virtual void Activate();
	virtual void Deactivate();

	PositionVector GetPosition() const;
	void SetPosition(const PositionVector& in_NewPos);

private:
	PositionVector m_Position;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::racer
//-----------------------------------------------------------------------------
#endif // V3D_VRIGIDBODYPART_2004_10_12_H
