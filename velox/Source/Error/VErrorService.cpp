#include "VErrorService.h"

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

VErrorService::VErrorService() :
	IVErrorService("error", 0)
{
}

VErrorService::~VErrorService()
{
	m_LogDevices.clear();
}

vbool VErrorService::RegisterLogDevice( IVLogDevice* in_pLogDevice )
{
	if ( in_pLogDevice == NULL )
		return false;

	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++ )
	{
		if ( (*m_Iter) == in_pLogDevice )
			return false;
	}

	m_LogDevices.push_back( in_pLogDevice );
	return true;
}

void VErrorService::UnregisterLogDevice( IVLogDevice* in_pLogDevice )
{
	m_LogDevices.remove( in_pLogDevice );
}

void VErrorService::Message( const VString& in_Message, LogMode in_LogMode )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnMessage( in_Message, static_cast<v3d::error::LogMode>(in_LogMode) );
}

void VErrorService::BeginProgressbar()
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnProgressbarBegin();
}

void VErrorService::UpdateProgressbar( const vfloat32 in_fIndex )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnProgressbarUpdate(in_fIndex);
}

void VErrorService::EndProgressbar()
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnProgressbarEnd();
}

void VErrorService::CreateState( const VString& in_StateName, const VString& in_Text )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnStateCreate(in_StateName, in_Text);
}

void VErrorService::UpdateState( const VString& in_StateName, const VString& in_Text )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnStateUpdate(in_StateName, in_Text);
}

void VErrorService::DeleteState( const VString& in_StateName )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnStateDelete(in_StateName);
}

//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------

