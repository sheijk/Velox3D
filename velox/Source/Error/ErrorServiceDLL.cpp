/**
 * Makro um Import und Export in der gleichen Datei zu realisieren
 */
#ifdef ERRORSERVICE_EXPORTS
#define ERRORSERVICE_API __declspec(dllexport)
#else
#define ERRORSERVICE_API __declspec(dllimport)
#endif
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include "VErrorService.h"
#include "VDebugMonitor.h"
#include "VFileLogger.h"

//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::error;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
VPointer<VErrorService>::AutoPtr g_pErrorService;
VPointer<VDebugMonitor>::AutoPtr g_pDebugMonitor;
VPointer<VFileLogger>::AutoPtr g_pFileLogger;

ERRORSERVICE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create log devices
	g_pDebugMonitor.Assign( new VDebugMonitor );
	g_pFileLogger.Assign( new VFileLogger );

	// create service object and register VDebuglogger and VFileLogger
	g_pErrorService.Assign( new VErrorService() );
	g_pErrorService->RegisterLogDevice( g_pDebugMonitor.Get() );
	g_pErrorService->RegisterLogDevice( g_pFileLogger.Get() );
}

ERRORSERVICE_API void Shutdown()
{
	//unregister debug loggers
	g_pErrorService->UnregisterLogDevice( g_pDebugMonitor.Get() );
	g_pErrorService->UnregisterLogDevice( g_pFileLogger.Get() );

	// delete debug loggers
	g_pDebugMonitor.Release();
	g_pFileLogger.Release();

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