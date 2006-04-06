#ifndef V3D_VSTATEBOXMASS_27_10_04_H
#define V3D_VSTATEBOXMASS_27_10_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Physics/VMass.h>
#include <v3d/Physics/VState.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a box mass state
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VStateBoxMass : public VMass, public VState
{
public:
	
	VStateBoxMass(VState::Parent in_pParent);
	virtual ~VStateBoxMass();

	void SetHeight(vfloat32 in_fHeigth);
	void SetLength(vfloat32 in_fLength);
	void SetWidth(vfloat32 in_fWidth);
	
	vfloat32 GetLength();
	vfloat32 GetHeight();
	vfloat32 GetWidth();
	/**
	 * total mass given without density information
	 */
	void SetTotalMass();
	
	virtual void Apply();

private:

	/**
 	 * applies box mass state
	 */

	

	vfloat32 m_fWidth;
	vfloat32 m_fHeight;
	vfloat32 m_fLength;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VStateBoxMass_27_10_04_H
