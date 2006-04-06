#ifndef V3D_VGEOMETRYBOX_2004_11_07_H
#define V3D_VGEOMETRYBOX_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3d/Physics/VGeometry.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Represents a collision box
 * encapsulates ODE function calls
 *
 * @author: ins
 */

class VSpace;

class VGeometryBox : public VGeometry
{
public:

	VGeometryBox();
	virtual ~VGeometryBox();

	void CreateBox(VSpace* in_SpaceState);
	
	void SetWidth(vfloat32 in_fWidth);
	void SetHeight(vfloat32 in_fHeight);
	void SetLength(vfloat32 in_fLength);

	vfloat32 GetWidth();
	vfloat32 GetHeight();
	vfloat32 GetLength();

private:

	VGeometryBox(const VGeometryBox&);
	VGeometryBox& operator=(const VGeometryBox&);

	vfloat32 m_fWidth;
	vfloat32 m_fHeight;
	vfloat32 m_fLength;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGEOMETRYBOX_2004_11_07_H
