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
#include <iostream>

//-----------------------------------------------------------------------------
using std::cout;
using std::endl;

using namespace v3d;
using namespace v3d::error;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
VPointer<VErrorService>::AutoPtr g_pErrorService;
//VPointer<VNamedObject>::AutoPtr g_pTest;

//TODO: den debug monitor in einem VPointer speichern, 
//und Devices in VErrorService nicht loeschen, sondern in Shutdown()

ERRORSERVICE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service object and register VDebuglogger and VFileLogger
	VErrorService* MyService = new VErrorService();
	MyService->RegisterLogDevice( new VDebugMonitor() );
//	MyService->RegisterLogDevice( new VFileLogger() );

	//and register it
	g_pErrorService.Reset( MyService );
	
	//(g_pTest.Reset(new VNamedObject("exserv.test", 0));

	cout << "ErrorService.init()" << endl;
}

ERRORSERVICE_API void Shutdown()
{
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