#ifndef V3D_VWINDOWBASE_H
#define V3D_VWINDOWBASE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Window/IVWindow.h>
#include <v3d/Updater/IVUpdateable.h>
#include <v3d/Graphics/VDisplaySettings.h>
#include <v3d/Input/IVInputManager.h>
//-----------------------------------------------------------------------------
#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------
/**
 * Base class of all windows	
 */
class VWindowBase : public IVWindow, public updater::IVUpdateable
{

public:
		VWindowBase();		
		virtual ~VWindowBase();
		
		virtual void Activate();
		virtual void Deactivate();
		virtual void SetName(VStringParam in_pName);
		VStringParam GetWindowName();
		graphics::VDisplaySettings GetDisplaySettings();

protected:

		input::IVInputManager* m_pInputManager;
		graphics::IVDevice* m_Device;
		std::string m_Name;
		graphics::VDisplaySettings m_DisplaySettings;

};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWINDOWBASE?H
