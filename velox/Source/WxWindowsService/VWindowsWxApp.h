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
namespace wxwindows {
//-----------------------------------------------------------------------------

/**
* Dummy wx frame for timer
*/

class VDummyFrame : public wxFrame
{
public:

	VDummyFrame();

	virtual void OnTimer();

private:

	wxTimer* m_DisplayTimer;

	enum Id
	{
		TIMER_ID = 0
	};


	DECLARE_EVENT_TABLE()

};

/**
 * Dummy wx app	
 */

class VWindowsWxApp : public wxApp, public updater::IVUpdateable
{
public:
	VWindowsWxApp();
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

private:

	VDummyFrame* m_DummyFrame;

};

//-----------------------------------------------------------------------------
} // namespace wxwindows
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWindowsWxApp_H
