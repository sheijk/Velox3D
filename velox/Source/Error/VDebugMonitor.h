#ifndef V3D_VDEBUGMONITOR_H
#define V3D_VDEBUGMONITOR_H
//-----------------------------------------------------------------------------
#include <windows.h>
#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/IVErrorService.h>
//-----------------------------------------------------------------------------
namespace v3d {
	namespace error {
//-----------------------------------------------------------------------------

class VDebugMonitor : public IVLogDevice
{
protected:
	void	OnMessage(const VString& in_Msg, LogMode in_LogMode );
	
	void	OnProgressbarBegin();
	void	OnProgressbarUpdate(const vfloat32 in_fIndex);
	void	OnProgressbarEnd();

	void	OnStateCreate( const VString& in_StateName, const VString& in_Text );
	void	OnStateUpdate( const VString& in_StateName, const VString& in_Text );
	void	OnStateDelete( const VString& in_StateName );

	void	SetDebugLevel( const vuint in_iLevel );

	HWND	m_DebugMonitorHWND;
	vbool	m_bIsAvaible;
	COPYDATASTRUCT m_MyCopyData;

public:
			VDebugMonitor();
			~VDebugMonitor();
};

//-----------------------------------------------------------------------------
} // error
} // v3d;
//-----------------------------------------------------------------------------
#endif

