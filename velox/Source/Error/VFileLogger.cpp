#include "VFileLogger.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------
//VFileLogger::VFileLogger(void)
//{
//	// We do nothing YEEAH!
//}
//TODO: we even don't compile unless we add the c'tor to the header :) (sheijk)
//TODO: hm.. ne Implementation waer bei Gelegenheit mal ganz nett :) (sheijk)

void VFileLogger::OnMessage(  VStringParam in_Message, VMessageType in_MessageType )
{
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


void VFileLogger::OnStateUpdate( VStringParam in_Text )
{
}



//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------