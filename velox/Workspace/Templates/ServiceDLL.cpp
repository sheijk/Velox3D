/**
 * Example Service DLL
 *
 * Makro um Import und Export in der gleichen Datei zu realisieren
 * wird nicht gebraucht, wg. dynamischen linken
 */
//TODO: add your service's name here
#define /*service.name*/_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>
//TODO: include service header

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>

//-----------------------------------------------------------------------------
using std::cout;
using std::endl;

using namespace v3d;
//-----------------------------------------------------------------------------

//TODO: replace /*your.service.class*/ by the objects you want to register

//-----------------------------------------------------------------------------
// use a smart pointer to guarante object destruction
VPointer</*your.service.class*/>::AutoPtr g_p/*obj.name*/;

/*service.name*/_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service object and register it
	g_p/*obj.name*/.Reset(new /*your.service.class*/(/*reg.name*/));
}

/*service.name*/_API void Shutdown()
{
	// delete and unregister service object
	g_p/*obj.name*/.Release();
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