#ifndef V3D_VWINDOWSWXAPP_H
#define V3D_VWINDOWSWXAPP_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Updater/IVUpdateable.h>
//-----------------------------------------------------------------------------
#include <wx/wx.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

/**
 * Dummy wx app	
 */

class VWindowsWxApp : public wxApp, public IVUpdateable
{
public:
	/**
	 * standard c'tor
	 */
	VWindowsWxApp();
	/**
	 * d'tor
	 */
	virtual ~VWindowsWxApp();

	/**
	 * IVUpdateable members	
	 */
	virtual void Update(vfloat32 in_fSeconds);
	virtual void Activate();
	virtual void Deactivate();

	/**
	 * virtual wxApp members	
	 */
	
	virtual bool OnInit();
	virtual int MainLoop();
	virtual int OnExit();

};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWindowsWxApp_H
