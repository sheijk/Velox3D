#ifndef V3D_VERRORCONSOLELISTENER_H
#define V3D_VERRORCONSOLELISTENER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Error/IVErrorListener.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace error {

//-----------------------------------------------------------------------------
class VErrorConsoleListener : public IVErrorListener
{
public:
	VErrorConsoleListener();
	virtual ~VErrorConsoleListener();

	virtual void OnMessage( VStringParam in_strMessage,
							VMessageType in_MessageType,
                            VStringParam in_strFile,
                            vuint in_nLine );
	

	virtual void	OnProgressbarBegin() {};
	virtual void	OnProgressbarUpdate( const vfloat32 in_fIndex) {};
	virtual void	OnProgressbarEnd() {};
	virtual void	OnStateUpdate( VStringParam in_Text );
};

//-----------------------------------------------------------------------------
} // namsepace 
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_/*classname*/_H