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

class IVWindowFrame
{
public:
	
	virtual void ShowFrame(vbool in_Param) = 0;

	//TODO: warum muss das frame von wx windows abhaengen?
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
