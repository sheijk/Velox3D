#ifndef V3D_VWINDOWMANAGERWIN32_H
#define V3D_VWINDOWMANAGERWIN32_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
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

	VWindowManagerWin32();
	virtual ~VWindowManagerWin32();

	/**
	 * @param: Set a window name 
	 * 
	 * @note: will be shown as caption under win32
	 */
	
	virtual IVWindowPtr QueryWindow(VStringParam in_pName);



};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWINDOWMANAGERWIN32_H
