#ifndef V3D_VPHYSICGEOMETRYBOX_2004_11_07_H
#define V3D_VPHYSICGEOMETRYBOX_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3dLib/Physics/VPhysicGeometry.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a physic state
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VPhysicSpace;

class VPhysicGeometryBox : public VPhysicGeometry
{
public:

	VPhysicGeometryBox();
	virtual ~VPhysicGeometryBox();

	void CreateBox(VPhysicSpace* in_SpaceState);
	
	void SetWidth(vfloat32 in_fWidth);
	void SetHeight(vfloat32 in_fHeight);
	void SetLength(vfloat32 in_fLength);

	vfloat32 GetWidth();
	vfloat32 GetHeight();
	vfloat32 GetLength();

private:

	VPhysicGeometryBox(const VPhysicGeometryBox&);
	VPhysicGeometryBox& operator=(const VPhysicGeometryBox&);

	vfloat32 m_fWidth;
	vfloat32 m_fHeight;
	vfloat32 m_fLength;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICGEOMETRYBOX_2004_11_07_H
