#ifndef V3D_VWINDOWSWXAPP_H
#define V3D_VWINDOWSWXAPP_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Updater/IVUpdateable.h>
//-----------------------------------------------------------------------------
#include <wx/wx.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

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

//	virtual void Register(VWindowFrame* in_pFrame);

private:

	//std::list<VWindowFrame*> m_FrameList;

//	VEditorMainFrame* m_MainFrame;
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWindowsWxApp_H
