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
		//SetDebugLevel( V3D_DEBUG_LEVEL );
	}
	else
		m_bIsAvaible = false;
}

VDebugMonitor::~VDebugMonitor()
{ 
	m_DebugMonitorHWND = NULL;
	m_bIsAvaible = false;
}

void VDebugMonitor::OnMessage( const VString& Message, const LogMode LogMode )
{
	// Prepare struct
	switch (LogMode)
	{
		case Ok:			m_MyCopyData.dwData = (int)MessageOk;		break;
		case Warning:		m_MyCopyData.dwData = MessageWarning;	break;
		case Error:			m_MyCopyData.dwData = MessageError;		break;
		default:			m_MyCopyData.dwData = MessageError;		break;
	}

	m_MyCopyData.cbData = Message.Length()+1;
	m_MyCopyData.lpData = (void*) Message.AsCString();

	//send the structure
	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (LPARAM) &m_MyCopyData) ;
}

void VDebugMonitor::OnStateCreate( const VString& in_Name, const VString& in_Text )
{
	// First send a StateAdd message with the state name
	m_MyCopyData.dwData = StateCreate;
	m_MyCopyData.cbData = in_Name.Length()+1;
	m_MyCopyData.lpData = (void*) in_Name.AsCString();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (LPARAM) &m_MyCopyData) ;

	// Then send a StateData message with the text
	m_MyCopyData.dwData = StateData;
	m_MyCopyData.cbData = in_Text.Length()+1;
	m_MyCopyData.lpData = (void*) in_Text.AsCString();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (LPARAM) &m_MyCopyData) ;
}

void VDebugMonitor::OnStateUpdate( const VString& in_Name, const VString& in_Text )
{
	m_MyCopyData.dwData = StateUpdate;
	m_MyCopyData.cbData = in_Name.Length()+1;
	m_MyCopyData.lpData = (void*) in_Name.AsCString();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (LPARAM) &m_MyCopyData) ;

	m_MyCopyData.dwData = StateData;
	m_MyCopyData.cbData = in_Text.Length()+1;
	m_MyCopyData.lpData = (void*) in_Text.AsCString();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (LPARAM) &m_MyCopyData) ;
}

void VDebugMonitor::OnStateDelete( const VString& in_Name )
{
	m_MyCopyData.dwData = StateDelete;
	m_MyCopyData.cbData = in_Name.Length()+1;
	m_MyCopyData.lpData = (void*) in_Name.AsCString();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (LPARAM) &m_MyCopyData) ;
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