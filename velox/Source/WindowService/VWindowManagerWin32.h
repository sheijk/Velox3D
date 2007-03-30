/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VWINDOWMANAGERWIN32_H
#define V3D_VWINDOWMANAGERWIN32_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
#include "VWindowManagerBase.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

/**
 * Specializes WindowManagerBase to Win32 specific stuff /warum? WInMBase gilt für alle Plattformen -[ins]
 * TODO: windows cannot share resources. fix!
 */

class VWindowManagerWin32 : public VWindowManagerBase
{
public:

	/**
	 * -----------------------------------------------------------------------------
	 */
	VWindowManagerWin32();
	/**
	 * -----------------------------------------------------------------------------
	 */
	virtual ~VWindowManagerWin32();

	/**
	 * @param: Set a window name 
	 * 
	 * @note: will be shown as caption under win32
	 */
	
	virtual IVWindowPtr QueryWindow(VStringParam in_pName);
	
	/**
	* @param: in_pName - the window caption
	*         in_pDisplaySettings - the display properties
	* 
	*/

	virtual IVWindowPtr QueryWindow(
		VStringParam in_pName,
		const graphics::VDisplaySettings* in_pDisplaySettings
		);

	virtual GraphicsDevicePtr CreateGraphicsDevice(
		const graphics::VDisplaySettings& in_Settings,
		PlatformWindowHandle in_Handle);

};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWINDOWMANAGERWIN32_H

