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

void VFileLogger::OnMessage( const VString& in_Msg, LogMode in_LogMode )
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

void VFileLogger::OnStateCreate( const VString& in_StateName, const VString& in_Text )
{
}

void VFileLogger::OnStateUpdate( const VString& in_StateName, const VString& in_Text )
{
}

void VFileLogger::OnStateDelete( const VString& in_StateName )
{
}


//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------