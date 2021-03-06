/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VErrorConsoleListener.h"
#include <iostream>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

VErrorConsoleListener::VErrorConsoleListener()
{

}

VErrorConsoleListener::~VErrorConsoleListener()
{

}

void VErrorConsoleListener::OnMessage( VStringParam in_strMessage,
								  VMessageType in_MessageType,
								  VStringParam in_strFile,
								  vuint in_nLine )
{
	std::cout << in_MessageType << "[" << in_strFile << "|" << in_nLine << "]:" <<  in_strMessage << std::endl;
}

void VErrorConsoleListener::OnStateUpdate( VStringParam in_Text )
{
	std::cout << "State: " << in_Text << std::endl;
}

inline std::ostream& operator<<( std::ostream& in_oStream, VMessageType in_MessageType )
{
	switch ( in_MessageType )
	{
		case Normal:	in_oStream << ""; break;
		case Warning:	in_oStream << "WARNING: "; break;
		case Error:		in_oStream << "ERROR: "; break;
		default: in_oStream << "Komisch, sollte nicht kommen "; break;
	}

	return in_oStream;
}
//-----------------------------------------------------------------------------
} // namespcae error
} // namespace v3d
//-----------------------------------------------------------------------------

