#include "VDebugLogger.h"
#include "IVLogDevice.h"

VDebugLogger::~VDebugLogger()
{
	UnregisterAndFreeAll();
}

vbool
VDebugLogger::RegisterLogDevice( IVLogDevice* MyLogDevice )
{
	if ( MyLogDevice == NULL )
		return false;

	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
	{
		if ( (*m_Iter) == MyLogDevice )
			return false;
	}

	m_LogDevices.push_back( MyLogDevice );
	return true;
}

void
VDebugLogger::UnregisterLogDevice( IVLogDevice* MyLogDevice )
{
	m_LogDevices.remove( MyLogDevice );
}

void
VDebugLogger::UnregisterAll()
{
	m_LogDevices.clear();
}

void
VDebugLogger::UnregisterAndFreeAll()
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
	{
		delete (*m_Iter);
		(*m_Iter) = NULL;
	}

	m_LogDevices.clear();
}

void
VDebugLogger::Message( std::string Message, eLogMode LogMode )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnMessage( Message, (IVLogDevice::eLogMode)LogMode );
}

void
VDebugLogger::BeginProgressbar()
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnProgressbarBegin();
}

void
VDebugLogger::UpdateProgressbar( vfloat32 fIndex )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnProgressbarUpdate(fIndex);
}

void
VDebugLogger::EndProgressbar( )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnProgressbarEnd();
}

void
VDebugLogger::AddState( const std::string StateName, const std::string StateText )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnStateAdd(StateName, StateText);
}

void
VDebugLogger::UpdateState( const std::string StateName, const std::string StateText )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnStateUpdate(StateName, StateText);
}

void
VDebugLogger::DeleteState( const std::string StateName )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnStateDelete(StateName);
}

void
VDebugLogger::InfoText( vuint iIndex, const std::string Text )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnInfoText(iIndex, Text);
}