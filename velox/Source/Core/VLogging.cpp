/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Core/VLogging.h>
//-----------------------------------------------------------------------------
#include <V3d/Error/IVErrorService.h>
#include <V3d/Core/VObjectRegistry.h>
#include <sstream>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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

