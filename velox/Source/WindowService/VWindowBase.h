/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VWINDOWBASE_H
#define V3D_VWINDOWBASE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Window/IVWindow.h>
#include <V3d/Updater/IVUpdateable.h>
#include <V3d/Graphics/VDisplaySettings.h>
#include <V3d/Input/IVInputManager.h>
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

