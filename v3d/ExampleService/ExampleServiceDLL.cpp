#include "ExampleServiceDLL.h"
//-----------------------------------------------------------------------------
#include <Utils/SmartPtr/VGuards.h>
#include <ExampleService/VExampleService.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//-----------------------------------------------------------------------------

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
VPointer<VExampleService>::AutoPtr g_pExService;

EXAMPLESERVICE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// create service object and register it
	g_pExService.Reset(new VExampleService());
}

EXAMPLESERVICE_API void Shutdown()
{
	// delete and unregister service object
	g_pExService.Release();
}

//-----------------------------------------------------------------------------