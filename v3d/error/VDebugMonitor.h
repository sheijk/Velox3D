#ifndef V3D_VDEBUGMONITOR_H
#define V3D_VDEBUGMONITOR_H

#include <windows.h>
#include <Core/VTypes.h>
#include <Core/VSingleton.h>
#include "IVLogDevice.h"


class VDebugMonitor : public IVLogDevice
{
protected:
	void	OnMessage(const std::string& Msg, const eLogMode LogMode );
	
	void	OnProgressbarBegin();
	void	OnProgressbarUpdate(const vfloat32 fIndex);
	void	OnProgressbarEnd();

	void	OnStateAdd( const std::string& StateName, const std::string& StateText );
	void	OnStateUpdate( const std::string& Name, const std::string& Text );
	void	OnStateDelete( const std::string& Name );

	void	OnInfoText( const vuint Index, const std::string& Text );
	
	void	SetDebugLevel( const vuint iLevel );

	HWND	m_DebugMonitorHWND;
	vbool	m_bIsAvaible;

public:
			VDebugMonitor();
			~VDebugMonitor();
};
#endif

/*! \class VDebugMonitor
	\brief LogDevice for Velox3D Debugmonitor
*/

/*! \var HWND VDebugMonitor::m_DebugMonitorHWND
	\brief HWND of Debugmonitors main window
*/

/*! \var vbool VDebugMonitor::m_bIsAvaible
	\brief Is the Debugmonitor avaible or not?
*/



