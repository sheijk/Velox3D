#include <v3d/Core/VLogging.h>
//-----------------------------------------------------------------------------
#include <v3d/Error/IVErrorService.h>
#include <v3d/Core/VObjectRegistry.h>
#include <sstream>

//-----------------------------------------------------------------------------
using v3d::error::IVErrorService;

namespace v3d {
//-----------------------------------------------------------------------------

namespace 
{
	IVErrorService* g_pErrorService = 0;
}

IVErrorService* GetLogDevice()
{
	if(0 == g_pErrorService)
	{
		g_pErrorService = QueryObject<IVErrorService>("error.service");
	}

	return g_pErrorService;
}

void SendDebugMessage(VStringParam in_pcMessage)
{
	// if logging device is available
	if( 0 != GetLogDevice() )
	{
		// send message to log device
		*(GetLogDevice()->GetGlobalErrorStream()) << v3d::error::Normal << in_pcMessage << V3D_DBGMSGEND;
	}
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
