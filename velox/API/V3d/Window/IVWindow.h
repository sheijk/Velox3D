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
 * @author: ins
 */

class IVWindow
{
public:

	/* Returns the current graphics device for this window */
	virtual graphics::IVDevice& QueryGraphicsDevice() = 0;
	
	/* Returns the current inpunt manager for this window */
	virtual input::IVInputManager& QueryInputManager() = 0;

	/* Set new display settings for this window */
	virtual void ChangeDisplay(graphics::VDisplaySettings* in_pInfo) = 0;

	/* Returns the display settings of this window */
	virtual graphics::VDisplaySettings GetDisplaySettings() = 0;

	/* Set the current title for the window */
	virtual void SetTitle(VStringParam in_sTitle) = 0;

	/* Set the focus to this window */
	virtual void SetActive() = 0;
	
	

	virtual ~IVWindow(){};
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVWINDOW_H
