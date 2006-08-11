#ifndef V3D_VORIENTATIONSTATE_2006_02_12_H
#define V3D_VORIENTATIONSTATE_2006_02_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Math.h>
#include <V3d/Physics/VState.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------

/**
 * Encapsulates a ODE orientation
 */
class VStateOrientation : public VState
{
public:
	VStateOrientation(VState::Parent in_pParent);
	virtual ~VStateOrientation();

	virtual void Apply();
	math::VQuatf& GetQuat();
	math::VVector4f GetAsVector();

private:

	math::VQuatf m_Quaternion;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------
#endif // V3D_VORIENTATIONSTATE_2006_02_12_H
