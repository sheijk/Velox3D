#include "VDebugMonitor.h"
#include "VDebugLogger.h"
#include "VDebugMonitorEnum.h"
#include <Core/VBuild.h>

VDebugMonitor::VDebugMonitor()
{
	const char*	WindowName = "Velox3D Debug Monitor";
	m_DebugMonitorHWND = NULL;
	m_DebugMonitorHWND = FindWindow(NULL, WindowName );

	if (m_DebugMonitorHWND!=NULL)
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

void
VDebugMonitor::OnMessage( const std::string& Message, const eLogMode LogMode )
{
	// Prepare struct
	COPYDATASTRUCT MyCopyData;

	switch (LogMode)
	{
		case VDebugLogger::V3D_OK:			MyCopyData.dwData = V3D_DM_MESSAGE_OK; break;
		case VDebugLogger::V3D_WARNING:		MyCopyData.dwData = V3D_DM_MESSAGE_WARNING; break;
		case VDebugLogger::V3D_ERROR:		MyCopyData.dwData = V3D_DM_MESSAGE_ERROR; break;
		default:							MyCopyData.dwData = V3D_DM_MESSAGE_ERROR; break;
	}

	MyCopyData.cbData = Message.length()+1;
	MyCopyData.lpData = (void*) Message.c_str();

	//send the structure
	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;
}

void VDebugMonitor::OnInfoText( const vuint Index, const std::string& Text )
{
	if (Index > 7)
		return;

	COPYDATASTRUCT MyCopyData;
	switch (Index)
	{
		case 0: MyCopyData.dwData = V3D_DM_DISPLAYBOX_0; break;
		case 1: MyCopyData.dwData = V3D_DM_DISPLAYBOX_1; break;
		case 2: MyCopyData.dwData = V3D_DM_DISPLAYBOX_2; break;
		case 3: MyCopyData.dwData = V3D_DM_DISPLAYBOX_3; break;
		case 4: MyCopyData.dwData = V3D_DM_DISPLAYBOX_4; break;
		case 5: MyCopyData.dwData = V3D_DM_DISPLAYBOX_5; break;
		case 6: MyCopyData.dwData = V3D_DM_DISPLAYBOX_6; break;
		case 7: MyCopyData.dwData = V3D_DM_DISPLAYBOX_7; break;
		default: return;
	}

	MyCopyData.cbData = Text.length()+1;
	MyCopyData.lpData = (void*) Text.c_str();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;
}

void
VDebugMonitor::OnStateAdd( const std::string& StateName, const std::string& StateText )
{
	COPYDATASTRUCT MyCopyData;

	MyCopyData.dwData = V3D_DM_STATE_ADD;
	MyCopyData.cbData = StateName.length()+1;
	MyCopyData.lpData = (void*) StateName.c_str();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;

	MyCopyData.dwData = V3D_DM_STATE_DATA;
	MyCopyData.cbData = StateText.length()+1;
	MyCopyData.lpData = (void*) StateText.c_str();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;
}

void
VDebugMonitor::OnStateUpdate( const std::string& StateName, const std::string& StateText )
{
	COPYDATASTRUCT MyCopyData;

	MyCopyData.dwData = V3D_DM_STATE_UPDATE;
	MyCopyData.cbData = StateName.length()+1;
	MyCopyData.lpData = (void*) StateName.c_str();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;

	MyCopyData.dwData = V3D_DM_STATE_DATA;
	MyCopyData.cbData = StateText.length()+1;
	MyCopyData.lpData = (void*) StateText.c_str();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;
}

void
VDebugMonitor::OnStateDelete( const std::string& StateName )
{
	COPYDATASTRUCT MyCopyData;

	MyCopyData.dwData = V3D_DM_STATE_DELETE;
	MyCopyData.cbData = StateName.length()+1;
	MyCopyData.lpData = (void*) StateName.c_str();

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;
}

void
VDebugMonitor::OnProgressbarBegin()
{
	COPYDATASTRUCT MyCopyData;

	MyCopyData.dwData = V3D_DM_PROGRESSBAR_BEGIN;
	MyCopyData.cbData = 0;
	MyCopyData.lpData = NULL;

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;

}

void
VDebugMonitor::OnProgressbarUpdate( const vfloat32 fIndex )
{
	COPYDATASTRUCT MyCopyData;

	MyCopyData.dwData = V3D_DM_PROGRESSBAR_UPDATE;
	MyCopyData.cbData = sizeof(vfloat32);
	MyCopyData.lpData = (void*) &fIndex;

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;
}

void
VDebugMonitor::OnProgressbarEnd()
{
	COPYDATASTRUCT MyCopyData;

	MyCopyData.dwData = V3D_DM_PROGRESSBAR_END;
	MyCopyData.cbData = 0;
	MyCopyData.lpData = NULL;

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;

}

void
VDebugMonitor::SetDebugLevel( const vuint iLevel )
{
	COPYDATASTRUCT MyCopyData;

	MyCopyData.dwData = V3D_DM_DEBUGLEVEL;
	MyCopyData.cbData = sizeof(vuint);
	MyCopyData.lpData = (void*) &iLevel;

	if ( m_DebugMonitorHWND != NULL )
		SendMessage( m_DebugMonitorHWND, WM_COPYDATA, (UINT) NULL, (long) &MyCopyData) ;
}
