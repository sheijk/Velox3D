#include "VDebugMonitor.h"
#include "VDebugMonitorEnum.h"

namespace v3d {
namespace error {

VDebugMonitor::VDebugMonitor()
{
	const char*	WindowName = "Velox3D Debug Monitor";
	m_DebugMonitorHWND = NULL;
	m_DebugMonitorHWND = FindWindow(NULL, WindowName );

	if (m_DebugMonitorHWND != NULL)
	{
		m_bIsAvaible = true;
		SetDebugLevel( V3D_DEBUG_LEVEL );
	}
	else
		m_bIsAvaible = false;
}

VDebugMonitor::~VDebugMonitor()
{ 
	m_DebugMonitorHWND = NULL;
	m_bIsAvaible = false;
}

void VDebugMonitor::OnMessage( VStringParam in_strMessage, VMessageType in_MessageType )
{

}


void VDebugMonitor::OnStateUpdate( VStringParam in_strText )
{
	
}

void VDebugMonitor::OnProgressbarBegin()
{
	m_MyCopyData.dwData = ProgressbarBegin;
	m_MyCopyData.cbData = 0;
	m_MyCopyData.lpData = NULL;

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (LPARAM) &m_MyCopyData) ;

}

void VDebugMonitor::OnProgressbarUpdate( const vfloat32 fIndex )
{
	m_MyCopyData.dwData = ProgressbarUpdate;
	m_MyCopyData.cbData = sizeof(vfloat32);
	m_MyCopyData.lpData = (void*) &fIndex;

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (LPARAM) &m_MyCopyData) ;
}

void VDebugMonitor::OnProgressbarEnd()
{
	m_MyCopyData.dwData = ProgressbarEnd;
	m_MyCopyData.cbData = 0;
	m_MyCopyData.lpData = NULL;

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (LPARAM) &m_MyCopyData) ;

}

void VDebugMonitor::SetDebugLevel( const vuint iLevel )
{
	m_MyCopyData.dwData = DebugLevel;
	m_MyCopyData.cbData = sizeof(vuint);
	m_MyCopyData.lpData = (void*) &iLevel;

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (LPARAM) &m_MyCopyData) ;
}

 } //error
} //v3d