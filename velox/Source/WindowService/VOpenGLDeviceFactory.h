#ifndef V3D_VOPENGLDEVICEFACTORY_08_30_04_H_H
#define V3D_VOPENGLDEVICEFACTORY_08_30_04_H_H
//-----------------------------------------------------------------------------
#include "VDeviceFactory.h"
#include <v3d/Graphics/VDisplaySettings.h>

#include <windows.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------
 /**
  * concrete device factory for an opengl device
  * @author: ins
  */

class VOpenGLDeviceFactory : public VDeviceFactory
{
public:

	VOpenGLDeviceFactory(
		const graphics::VDisplaySettings* in_pDisplaySettings,
		const HWND hWnd);
	
	virtual ~VOpenGLDeviceFactory();

	virtual graphics::IVDevice* CreateDevice();

private:

	HWND m_hWnd;
	const graphics::VDisplaySettings* m_pDisplaySettings;
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VOPENGLDEVICEFACTORY_08_30_04_H_H
