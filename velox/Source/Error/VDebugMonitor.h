#ifndef V3D_VDEBUGMONITOR_H
#define V3D_VDEBUGMONITOR_H

#include <windows.h>
#include <v3d/Core/VTypes.h>
#include "VLogModeEnum.h"
#include "IVLogDevice.h"

namespace v3d {
	namespace error {

class VDebugMonitor : public IVLogDevice
{
protected:
	void	OnMessage(const std::string& Msg, LogMode LogMode );
	
	void	OnProgressbarBegin();
	void	OnProgressbarUpdate(const vfloat32 fIndex);
	void	OnProgressbarEnd();

	void	OnStateCreate( const std::string& StateName, const std::string& StateText );
	void	OnStateUpdate( const std::string& Name, const std::string& Text );
	void	OnStateDelete( const std::string& Name );

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



