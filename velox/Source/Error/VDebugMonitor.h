#ifndef V3D_VDEBUGMONITOR_H
#define V3D_VDEBUGMONITOR_H

#include <windows.h>
#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/IVErrorServie.h"

namespace v3d {
	namespace error {

class VDebugMonitor : public IVLogDevice
{
protected:
	void	OnMessage(const VString& Msg, LogMode LogMode );
	
	void	OnProgressbarBegin();
	void	OnProgressbarUpdate(const vfloat32 fIndex);
	void	OnProgressbarEnd();

	void	OnStateCreate( const VString& StateName, const VString& StateText );
	void	OnStateUpdate( const VString& Name, const VString& Text );
	void	OnStateDelete( const VSstring& Name );

	void	SetDebugLevel( const vuint iLevel );

	HWND	m_DebugMonitorHWND;
	vbool	m_bIsAvaible;
	COPYDATASTRUCT m_MyCopyData;

public:
			VDebugMonitor();
			~VDebugMonitor();
};
#endif

	} // error
} // v3d;

/*! \class VDebugMonitor
	\brief LogDevice for Velox3D Debugmonitor
*/

/*! \var HWND VDebugMonitor::m_DebugMonitorHWND
	\brief HWND of Debugmonitors main window
*/

/*! \var vbool VDebugMonitor::m_bIsAvaible
	\brief Is the Debugmonitor avaible or not?
*/



