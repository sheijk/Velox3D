#include "VErrorService.h"
#include "IVLogDevice.h"
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
	// delete all register logdevices and clear list
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
	{
		//IVLogDevice temp = *(m_Iter);
		delete *(m_Iter);
		*m_Iter = NULL;
	}

	m_LogDevices.clear();
}

vbool VErrorService::RegisterLogDevice( IVLogDevice* in_LogDevice )
{
	if ( in_LogDevice == NULL )
		return false;

	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++ )
	{
		if ( (*m_Iter) == in_LogDevice )
			return false;
	}

	m_LogDevices.push_back( in_LogDevice );
	return true;
}

void VErrorService::Message( const std::string& in_Message, LogMode in_LogMode )
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

void VErrorService::CreateState( const std::string& in_Name, const std::string& in_Text )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnStateCreate(in_Name, in_Text);
}

void VErrorService::UpdateState( const std::string& in_Name, const std::string& in_Text )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnStateUpdate(in_Name, in_Text);
}

void VErrorService::DeleteState( const std::string& in_Name )
{
	for ( m_Iter = m_LogDevices.begin(); m_Iter != m_LogDevices.end(); m_Iter++)
		(*m_Iter)->OnStateDelete(in_Name);
}

//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------

