#define IMAGE_SERVICE_API __declspec(dllexport)
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include "VImageFactory.h"
#include "VTgaImageLoader.h"
#include "VJpegImageLoader.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::image;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// use a smart pointer to guarantee object destruction
VPointer<VImageFactory>::AutoPtr g_pImageFactory;
VPointer<IVImageLoader>::AutoPtr g_pTgaImageLoader;
VPointer<IVImageLoader>::AutoPtr g_pJpgImageLoader;

IMAGE_SERVICE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service object and register it
	g_pImageFactory.Assign(new VImageFactory());
	//g_pTgaImageLoader.Assign(new VTgaImageLoader());
	g_pJpgImageLoader.Assign(new VJpegImageLoader());
}

IMAGE_SERVICE_API void Shutdown()
{
	// delete and unregister service object
	g_pImageFactory.Release();
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