#ifndef V3D_VPHYSICPOSITIONSTATE_27_10_04_H
#define V3D_VPHYSICPOSITIONSTATE_27_10_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3dLib/Graphics/Geometry/VVector3f.h>
#include <V3dLib/Physics/VPhysicState.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a position
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VPhysicPositionState : public VPhysicState
{
public:
	VPhysicPositionState();	
	virtual ~VPhysicPositionState();

	void SetPosition(vfloat32 x, vfloat32 y, vfloat32 z);
	void SetPosition(graphics::VVector3f in_Position);
	graphics::VVector3f GetPositon();

private:

	virtual void Apply();
	graphics::VVector3f m_Position;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICPOSITIONSTATE_27_10_04_H
