#include "ExampleServiceDLL.h"
//-----------------------------------------------------------------------------
#include <Utils/SmartPtr/VGuards.h>
#include <ExampleService/VExampleService.h>
#include "VExampleApp.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>

using std::cout;
using std::endl;

//-----------------------------------------------------------------------------
VPointer<VExampleService>::AutoPtr g_pExService;
VPointer<VNamedObject>::AutoPtr g_pTest;
VPointer<VExampleApp>::AutoPtr g_pApp;

EXAMPLESERVICE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service object and register it
	g_pExService.Reset(new VExampleService());
	
//	g_pApp.Reset(new VExampleApp());
	
	g_pTest.Reset(new VNamedObject("exserv.test", 0));

	cout << "exService.init()" << endl;
}

EXAMPLESERVICE_API void Shutdown()
{
	// delete and unregister service object
	g_pExService.Release();
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