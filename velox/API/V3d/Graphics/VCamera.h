#ifndef V3D_VCAMERA_H
#define V3D_VCAMERA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A simple rustical camera for testing purpose
 *
 * @author ins
 */
class VCamera
{
public:
	VCamera();
	VCamera(vfloat32 x, vfloat32 y, vfloat32 z);
	virtual ~VCamera(){};

	vfloat32 GetX();
	vfloat32 GetY();
	vfloat32 GetZ();

	
	void SetX(vfloat32 x);
	void SetY(vfloat32 y);
	void SetZ(vfloat32 z);

	void AddX(vfloat32 x);
	void AddY(vfloat32 y);
	void AddZ(vfloat32 z);

private:

	vfloat32 m_pPosition[3];

};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCAMERA_H
