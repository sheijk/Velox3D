/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VErrorService.h"

#include "VErrorStream.h"
#include <V3d/Core/VAssert.h>
#include <V3d/Core/VObjectRegistry.h>

#include <exception>
#include <iostream>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

VErrorService::VErrorService() :
	IVErrorService("error.service", 0)
{
    m_GlobalErrorStream.Assign( new VErrorStream("global", this) );
}

VErrorService::~VErrorService()
{
	VNamedObject::UnregisterFromObjectRegistry();		
}

vbool VErrorService::RegisterListener(IVErrorListener* in_pListener,
									  IVErrorFilter* in_pFilter )
{
	V3D_ASSERT( (in_pListener != NULL) );
	V3D_ASSERT( (in_pFilter != NULL) );

//TODO: Falls push_back fehlschlägt, false zurückgeben
	try {
		m_Listeners.push_back( FLPair( in_pFilter, in_pListener ) );
	}
	catch ( std::exception exp) {
		return false;
	}

	return true;
}

void VErrorService::UnregisterListener( IVErrorListener* in_pListener )
{
	for ( m_Iter = m_Listeners.begin(); m_Iter != m_Listeners.end(); m_Iter++ )
		if ( (*m_Iter).second == in_pListener )
		{
            m_Listeners.erase( m_Iter );
			return;
		}
}

VErrorService::ErrorStreamPtr VErrorService::GetGlobalErrorStream()
{
	return m_GlobalErrorStream;
}

VErrorService::ErrorStreamPtr VErrorService::CreateErrorStream( VStringParam in_strName )
{
	return ErrorStreamPtr( new VErrorStream(in_strName, this) );
}


void VErrorService::BeginProgressbar( VStringParam in_strStreamName )
{
	for ( m_Iter = m_Listeners.begin(); m_Iter != m_Listeners.end(); m_Iter++ )
		if ( (*m_Iter).first->AcceptProgressbar( in_strStreamName ) )
			(*m_Iter).second->OnProgressbarBegin();
}

void VErrorService::UpdateProgressbar( VStringParam in_strStreamName, vfloat32 in_fIndex )
{
	for ( m_Iter = m_Listeners.begin(); m_Iter != m_Listeners.end(); m_Iter++ )
		if ( (*m_Iter).first->AcceptProgressbar( in_strStreamName ) )
			(*m_Iter).second->OnProgressbarUpdate( in_fIndex );
}

void VErrorService::EndProgressbar( VStringParam in_strStreamName )
{
	for ( m_Iter = m_Listeners.begin(); m_Iter != m_Listeners.end(); m_Iter++ )
		if ( (*m_Iter).first->AcceptProgressbar( in_strStreamName ) )
			(*m_Iter).second->OnProgressbarEnd();
}

void VErrorService::UpdateState( VStringParam in_strStreamName, VStringParam in_strText )
{
	for ( m_Iter = m_Listeners.begin(); m_Iter != m_Listeners.end(); m_Iter++ )
		if ( (*m_Iter).first->AcceptState( in_strStreamName ) )
			(*m_Iter).second->OnStateUpdate( in_strText );
}

void VErrorService::Message( VStringParam in_strStreamName,
							 VStringParam in_strMessage,
							 VMessageType in_MessageType,
							 VStringParam in_strFile,
							vuint in_nLine )
{
	for ( m_Iter = m_Listeners.begin(); m_Iter != m_Listeners.end(); m_Iter++ )
		if ( (*m_Iter).first->AcceptMessage( in_strStreamName, in_MessageType ) )
			(*m_Iter).second->OnMessage( in_strMessage, in_MessageType, in_strFile, in_nLine );
}


//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------


