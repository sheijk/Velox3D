#ifndef V3D_VWINDOWWIN32_H
#define V3D_VWINDOWWIN32_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
#include "VWindowBase.h"
//-----------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef CreateWindow
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

/**
 * Implements the IVWindow interface for win32
 */
class VWindowWin32 : public VWindowBase
					  
{
public:
	VWindowWin32();
	virtual ~VWindowWin32();

	virtual void Create(VStringParam in_pName);
	virtual void Destroy();
	virtual void ChangeDisplay(graphics::VDisplaySettings* in_pInfo);
	virtual graphics::IVDevice& QueryGraphicsDevice();
	virtual input::IVInputManager& QueryInputManager();

private:

    void Register();
	void Unregister();
	void CreateWindow();
	virtual void Update(vfloat32 in_fSeconds);
	

	HINSTANCE hInstance;
	HWND hWnd;
	
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWINDOWWIN32_H
