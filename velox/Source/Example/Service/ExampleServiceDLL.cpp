/**
 * Example Service DLL
 *
 * Makro um Import und Export in der gleichen Datei zu realisieren
 */
//#ifdef EXAMPLESERVICE_EXPORTS
#define EXAMPLESERVICE_API __declspec(dllexport)
//#else
//#define EXAMPLESERVICE_API __declspec(dllimport)
//#endif
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include "VExampleService.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>

//-----------------------------------------------------------------------------
using std::cout;
using std::endl;

using namespace v3d;
using namespace v3d::example;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
VPointer<VExampleService>::AutoPtr g_pExService;
VPointer<VNamedObject>::AutoPtr g_pTest;

EXAMPLESERVICE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service object and register it
	g_pExService.Reset(new VExampleService());
	
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