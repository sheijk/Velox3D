#ifndef V3D_VDEVICEFACTORY_08_30_04_H
#define V3D_VDEVICEFACTORY_08_30_04_H
//-----------------------------------------------------------------------------
#include <V3d/Graphics/IVDevice.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace window{
//-----------------------------------------------------------------------------

/**
 * Factory for device creation
 * @author: ins
 */

class VDeviceFactory
{
public:

	/* Creates a device */
	virtual graphics::IVDevice* CreateDevice() = 0;
	
};
//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VDEVICEFACTORY_08_30_04_H
