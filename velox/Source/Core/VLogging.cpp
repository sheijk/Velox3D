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
	//IVErrorService* g_pErrorService = 0;

	IVErrorService* GetLogDevice()
	{
		try 
		{
			return QueryObject<IVErrorService>("error.service");
		}
		//TODO: eleminate warning - ins
		catch(VObjectRegistryException& )
		{
			return 0;
		}

		//if(0 == g_pErrorService)
		//{
			//try 
			//{
			//	g_pErrorService = QueryObject<IVErrorService>("error.service");
			//}
			//catch(VObjectRegistryException& e)
			//{
			//}
		//}

	//	return g_pErrorService;
	}
}

void SendDebugMessage(VStringParam in_pcMessage)
{
	// if logging device is available
	if( 0 != GetLogDevice() )
	{
		// send message to log device
		v3d::error::IVErrorStream& errorStream
			= * (GetLogDevice()->GetGlobalErrorStream());

		//*(GetLogDevice()->GetGlobalErrorStream())
		errorStream
			<< v3d::error::Normal << in_pcMessage;
	}
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
