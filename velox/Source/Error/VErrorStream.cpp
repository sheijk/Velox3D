#include "VErrorStream.h"
#include <iostream>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

VErrorStream::VErrorStream(VStringParam in_strName, VErrorService* in_pErrorService )
	: m_pParent( in_pErrorService), m_strName( in_strName )
{

}

VErrorStream::~VErrorStream()
{

}

void VErrorStream::BeginProgressbar()
{
    m_pParent->BeginProgressbar( m_strName.c_str() );
}

void VErrorStream::UpdateProgressbar(vfloat32 in_fIndex)
{
	m_pParent->UpdateProgressbar( m_strName.c_str(), in_fIndex );
}

void VErrorStream::EndProgressbar()
{
	m_pParent->EndProgressbar( m_strName.c_str() );
}

void VErrorStream::UpdateState( VStringParam in_strText )
{
	m_pParent->UpdateState( m_strName.c_str(), in_strText );
}

VStringRetVal VErrorStream::GetName()
{
	return m_strName.c_str();
}

void VErrorStream::SetLine( vuint in_nLine )
{
	m_nLine = in_nLine;
}

void VErrorStream::SetFile( VStringParam in_strLine )
{
	m_strFile = in_strLine;
}

void VErrorStream::SetMessageType( VMessageType in_MessageType )
{
	m_MessageType = in_MessageType;
}

void VErrorStream::Write( VStringParam in_strString )
{
	m_oStream << in_strString << std::ends;
}

void VErrorStream::Flush()
{
	m_pParent->Message( m_strName.c_str(), m_oStream.str().c_str(), m_MessageType, m_strFile.c_str(), m_nLine );
	m_oStream.str("");
	
}
//-----------------------------------------------------------------------------
} // namespace error
} // namespace v3d
//-----------------------------------------------------------------------------
