/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VFileLogger.h"
#include <V3d/Core/VException.h>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------
VFileLogger::VFileLogger( VStringParam in_strFileName )
{
	m_File.open( in_strFileName, std::ios_base::out|std::ios_base::trunc );
    if ( !m_File.is_open() )
		V3D_THROW( VException, "Could not open file for error logging" );
}

VFileLogger::~VFileLogger()
{
	m_File.close();
}


void VFileLogger::OnMessage( VStringParam in_strStreamName, VStringParam in_strMessage, VMessageType in_MessageType, VStringParam in_strFile, vuint in_nLine )
{
    m_File << in_MessageType << "[" << in_strStreamName << "|" << in_strFile << "|" << in_nLine << "]:" <<  in_strMessage << std::endl;
	m_File.flush();
}

void VFileLogger::OnProgressbarBegin() 
{
}

void VFileLogger::OnProgressbarUpdate(const vfloat32 in_fIndex)
{
}

void VFileLogger::OnProgressbarEnd()
{
}


void VFileLogger::OnStateUpdate( VStringParam in_strStreamName, VStringParam in_strText )
{
	//TODO: fehlt da nicht die schliessende klammer(])?
	m_File << "[" << in_strStreamName << "|State" << in_strText << std::endl;
	m_File.flush();
}

inline std::ofstream& operator<<( std::ofstream& in_fStream, VMessageType in_MessageType )
{
	switch ( in_MessageType )
	{
	case Normal:	in_fStream << ""; break;
	case Warning:	in_fStream << "WARNING: "; break;
	case Error:		in_fStream << "ERROR: "; break;
	default: in_fStream << "Komisch, sollte nicht kommen "; break;
	}

	return in_fStream;
}


//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------
