#include <v3d/Core/VLogging.h>
//-----------------------------------------------------------------------------
#include <v3d/Error/IVErrorService.h>
#include <v3d/Core/VObjectRegistry.h>

//-----------------------------------------------------------------------------
using v3d::error::IVErrorService;

namespace v3d {
//-----------------------------------------------------------------------------
#define LOGGING_NAMESPACE LOGGING##__TIMESTAMP__

namespace LOGGING_NAMESPACE {
	IVErrorService* g_pErrorService = 0;
}

IVErrorService* GetLogDevice()
{
	if(0 == LOGGING_NAMESPACE::g_pErrorService)
	{
		LOGGING_NAMESPACE::g_pErrorService = QueryObject<IVErrorService>("error");
	}

	return LOGGING_NAMESPACE::g_pErrorService;
}

//TODO: implement this function
void SendDebugMessage(VStringParam in_pcMessage)
{
	// if logging device is available
	if( 0 != GetLogDevice() )
	{
		// send message to log device
		GetLogDevice()->Message(in_pcMessage, v3d::error::Ok);
	}
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
