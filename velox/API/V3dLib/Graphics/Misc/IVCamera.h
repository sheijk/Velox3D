#ifndef V3D_IVCAMERA_2004_05_15_H
#define V3D_IVCAMERA_2004_05_15_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Math/VVector.h>
#include <V3d/Math/VMatrix.h>
#include <V3dLib/Math/VRBTransform.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

class IVDevice;

/**
 * Interface for cameras
 *
 * @author sheijk
 */
class IVCamera
{
public:
	virtual const VMatrix44f& ViewMatrix() const = 0;
	virtual const math::VRBTransform& Transform() const = 0;

	virtual void ApplyTo(IVDevice& in_Device) const = 0;

	virtual VVector3f GetPosition() const = 0;
	virtual VVector3f GetViewDirection() const = 0;
	virtual VVector3f GetUpVector() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVCAMERA_2004_05_15_H
