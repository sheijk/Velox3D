#ifndef V3D_IVWINDOW_H
#define V3D_IVWINDOW_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Input/IVInputManager.h>
#include <v3d/Graphics/VDisplaySettings.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

/**
 * IVWindow interface for window creating and managing
 */

class IVWindow
{
public:
	
	virtual graphics::IVDevice& QueryGraphicsDevice() = 0;
	virtual input::IVInputManager& QueryInputManager() = 0;
	virtual void ChangeDisplay(graphics::VDisplaySettings* in_pInfo) = 0;
	virtual graphics::VDisplaySettings GetDisplaySettings() = 0;
	
	

	virtual ~IVWindow(){};
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVWINDOW_H
