/**
 * Example Service DLL
 *
 * Makro um Import und Export in der gleichen Datei zu realisieren
 * wird nicht gebraucht, wg. dynamischen linken
 */
#define COMMONSERVICES_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include "VConfigProvider.h"
#include "../UpdateManager/VUpdateManager.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::config;
using namespace v3d::updater;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// use a smart pointer to guarante object destruction
VPointer<VConfigProvider>::AutoPtr g_pConfigProvider;
VPointer<VUpdateManager>::AutoPtr g_pUpdater;

COMMONSERVICES_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service object and register it
	g_pConfigProvider.Assign(new VConfigProvider("config.provider"));
	g_pUpdater.Assign(new VUpdateManager("updater.service"));
}

COMMONSERVICES_API void Shutdown()
{
	// delete and unregister service object
	g_pUpdater.Release();
	g_pConfigProvider.Release();
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