#define ERRORSERVICE_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/Error/IVErrorFilter.h>
#include <v3d/Utils/VAllFilter.h>
#include "VErrorService.h"
#include "VErrorConsoleListener.h"
#include "windows.h"
//#include "VDebugMonitor.h"
//#include "VFileLogger.h"

//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::error;
using namespace v3d::utils;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
VPointer<VErrorService>::AutoPtr g_pErrorService;
VPointer<VErrorConsoleListener>::AutoPtr g_pConsoleListener;
//-----------------------------------------------------------------------------


ERRORSERVICE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create log devices
	g_pConsoleListener.Assign( new VErrorConsoleListener() );

	// create service object
	g_pErrorService.Assign( new VErrorService() );

	// register standard listener
//TODO: hack entfernen
	g_pErrorService->RegisterListener( g_pConsoleListener.Get(), new VAllFilter()  );

}

ERRORSERVICE_API void Shutdown()
{
	//unregister debug loggers
	g_pErrorService->UnregisterListener( g_pConsoleListener.Get() );
	
	// delete debug loggers
	g_pConsoleListener.Release();

	// delete and unregister service object
	g_pErrorService.Release();
}

/**
 * DLL Einsprungspunkt, wird beim laden der DLL aufgerufen, sollte
 * aber meist nichts tun
 */
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

//-----------------------------------------------------------------------------