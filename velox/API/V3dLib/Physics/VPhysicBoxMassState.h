#ifndef V3D_VPHYSICBOXMASSSTATE_27_10_04_H
#define V3D_VPHYSICBOXMASSSTATE_27_10_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Physics/VPhysicMass.h>
#include <v3dLib/Physics/VPhysicState.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a box masss state
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VPhysicBoxMassState : public VPhysicMass, public VPhysicState
{
public:
	
	VPhysicBoxMassState();
	virtual ~VPhysicBoxMassState();

	void SetHeigth(vfloat32 in_fHeigth);
	void SetLength(vfloat32 in_fLength);
	void SetWidth(vfloat32 in_fWidth);
	
	vfloat32 GetLength();
	vfloat32 GetHeight();
	vfloat32 GetWidth();
	
private:

	/**
 	 * applies box mass state
	 */

	virtual void Apply();

	vfloat32 m_fWidth;
	vfloat32 m_fHeight;
	vfloat32 m_fLength;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICBOXMASSSTATE_27_10_04_H
