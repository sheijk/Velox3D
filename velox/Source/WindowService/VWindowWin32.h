#ifndef V3D_VWINDOWWIN32_H
#define V3D_VWINDOWWIN32_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
#include "VWindowBase.h"
#include "VDeviceFactory.h"
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
 * @author: ins
 */

V3D_DECLARE_EXCEPTION(VWin32Exception, VException)

class VWindowWin32 : public VWindowBase
					  
{
public:
	/**
	 * -----------------------------------------------------------------------------
	 */
	VWindowWin32();
	/**
	 * -----------------------------------------------------------------------------
	 */
	virtual ~VWindowWin32();
	
	/**
	 * -----------------------------------------------------------------------------
	 * @param in_pName
	 * 
	 */
	virtual void Create(VStringParam in_pName);
	/**
	 * -----------------------------------------------------------------------------
	 */
	virtual void Destroy();
	/**
	 * -----------------------------------------------------------------------------
	 * @param in_pInfo
	 * 
	 */
	virtual void ChangeDisplay(graphics::VDisplaySettings* in_pInfo);
	/**
	 * -----------------------------------------------------------------------------
	 */
	virtual graphics::IVDevice& QueryGraphicsDevice();
	virtual input::IVInputManager& QueryInputManager();
	/**
	 * -----------------------------------------------------------------------------
	 * @param in_sName
	 * 
	 */
	virtual void SetTitle(VStringParam in_sName);
	/**
	 * -----------------------------------------------------------------------------
	 */
	virtual void SetActive();

	static vbool bFocus;

private:

	/**
	 * -----------------------------------------------------------------------------
	 */
    void Register();
	/**
	 * -----------------------------------------------------------------------------
	 */
	void Unregister();
	/**
	 * -----------------------------------------------------------------------------
	 */
	void CreateWindow();
	/**
	 * -----------------------------------------------------------------------------
	 * @param in_fSeconds
	 * 
	 */
	virtual void Update(vfloat32 in_fSeconds);
	

	HINSTANCE hInstance;
	HWND hWnd;

	VDeviceFactory* m_pDeviceFactory;
	
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWINDOWWIN32_H
