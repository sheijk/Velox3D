#ifndef V3D_IVCAMERA_2004_05_15_H
#define V3D_IVCAMERA_2004_05_15_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Math/VVector.h>
#include <V3d/Math/VMatrix.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Interfaces for cameras
 *
 * @author sheijk
 */
class IVCamera
{
public:
	typedef VVector<vfloat32, 3> Vector;

	virtual VMatrix44f& TransformMatrix() = 0;
	virtual const VMatrix44f& TransformMatrix() const = 0;
	virtual Vector GetPosition() const = 0;
	virtual Vector GetViewDirection() const = 0;
	virtual Vector GetUpVector() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVCAMERA_2004_05_15_H
