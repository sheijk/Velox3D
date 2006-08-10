#ifndef V3D_VSTATEPOSITION_27_10_04_H
#define V3D_VSTATEPOSITION_27_10_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Physics/VState.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a position state and
 * encapsulates ODE function calls
 *
 * author: ins
 */

class VStatePosition : public VState
{
public:
	VStatePosition(VState::Parent in_pParent);	
	virtual ~VStatePosition();

	void SetPosition(vfloat32 x, vfloat32 y, vfloat32 z);
	void SetPosition(graphics::VVertex3f in_Position);
	graphics::VVertex3f GetPositon();

	virtual void Apply();

private:

	
	graphics::VVertex3f m_Position;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTATEPOSITION_27_10_04_H
