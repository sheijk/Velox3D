/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVWINDOWMANAGER_H
#define V3D_IVWINDOWMANAGER_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Window/IVWindow.h>
#include <V3d/Core/SmartPtr/VGuards.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics/VDisplaySettings.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

/**
 * Implementation of the Interface IVWindowManager.
 * Use this interface to work with the managers
 *
 * Contains factory methods for devices which need platform dependent handles
 * (should maybe moved to an IVPlatformDependent interface?) -- sheijk
 */
class IVWindowManager
{
public:
	typedef VPointer<graphics::IVDevice>::SharedPtr GraphicsDevicePtr;
	typedef void* PlatformWindowHandle;
	//TODO: replace IVWindowPtr by WindowPtr --sheijk
	typedef VPointer<IVWindow>::SharedPtr IVWindowPtr; 
	typedef IVWindowPtr WindowPtr;

	/* Returns a pointer to the window created by this manager */
	virtual IVWindowPtr QueryWindow(VStringParam in_pName) = 0;

	/* Returns a pointer to the window created by this manager */
	virtual IVWindowPtr QueryWindow(
		VStringParam in_pName,
		const graphics::VDisplaySettings* in_pDisplaySettings
		) = 0;
	
	/**
	 * returns a graphics device. The handle will be casted to the platforms
	 * window handle (HWND for windows, etc)
	 */
	virtual GraphicsDevicePtr CreateGraphicsDevice(
		const graphics::VDisplaySettings& in_Settings,
		PlatformWindowHandle in_Handle) = 0;

	virtual ~IVWindowManager() {};
};

typedef VServicePtr<IVWindowManager> VWindowManagerPtr;
//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
template<>
inline v3d::window::IVWindowManager* v3d::QueryService<v3d::window::IVWindowManager>()
{
	return QueryObject<v3d::window::IVWindowManager>("window.manager");
}
//-----------------------------------------------------------------------------
#endif // V3D_IVWINDOWMANAGER_H

