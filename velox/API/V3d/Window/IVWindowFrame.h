#ifndef V3D_IVWINDOWFRAME_H
#define V3D_IVWINDOWFRAME_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Window/IVWxConnector.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

//TODO: move to v3d/window/wx/
class IVWindowFrame
{
public:
	
	/* Shows the window frame if the given param is true */
	virtual void ShowFrame(vbool in_Param) = 0;

	/* Registers the window to the wx connector */
	virtual void Register()
	{

		IVWxConnector* WinConnect;
		WinConnect = QueryObject<IVWxConnector>("wx.connector");
		WinConnect->Register(this);
	};


	virtual ~IVWindowFrame(){};
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVWINDOWFRAME_H
