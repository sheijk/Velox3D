/**
 * Example Service DLL
 *
 * Makro um Import und Export in der gleichen Datei zu realisieren
 * wird nicht gebraucht, wg. dynamischen linken
 */
//TODO: add your service's name here
#define VFSSERVICE_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include <v3d/VFS/VMountOptions.h>

#include "VStreamFactory.h"
#include "VSimpleVfs.h"
#include "VDataProviderPool.h"
#include "VFileDataProvider.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>

//-----------------------------------------------------------------------------
using std::cout;
using std::endl;

using namespace v3d;
using namespace v3d::vfs;
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// use a smart pointer to guarante object destruction
VPointer<VStreamFactory>::AutoPtr g_pStreamFac;
VPointer<VSimpleVfs>::AutoPtr g_pFileSys;
VPointer<VDataProviderPool>::AutoPtr g_pDataProvPool;
VPointer<VFileDataProvider>::AutoPtr g_pFileDataProv;


VFSSERVICE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service objects and register it
	g_pStreamFac.Assign(new VStreamFactory("vfs.strfact"));
	g_pDataProvPool.Assign(new VDataProviderPool("vfs.dpp"));
	g_pFileDataProv.Assign(new VFileDataProvider());
	g_pDataProvPool->RegisterDataProvider(g_pFileDataProv.Get());
	g_pFileSys.Assign(new VSimpleVfs("vfs.fs", "vfs.xml"));
}

VFSSERVICE_API void Shutdown()
{
	g_pDataProvPool->UnregisterDataProvider(g_pFileDataProv.Get());

	// delete and unregister service object
	g_pFileSys.Release();
	g_pStreamFac.Release();
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