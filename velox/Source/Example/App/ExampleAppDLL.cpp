// kann evtl weggelassen werden, da diese Deklarationen nie importiert werden
#ifdef EXAMPLEAPP_EXPORTS
#define EXAMPLEAPP_API __declspec(dllexport)
#else
#define EXAMPLEAPP_API __declspec(dllimport)
#endif
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include "VExampleApp.h"
#include <v3d/Core/SmartPtr/VGuards.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::example;
//-----------------------------------------------------------------------------

/** instance of the application service */
VPointer<VExampleApp>::AutoPtr g_pService;

EXAMPLEAPP_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create the application service instance
	// (registers itself at the Object Registry)
	g_pService.Reset(new VExampleApp());
}

EXAMPLEAPP_API void Shutdown()
{
	// destroy the application instance
	g_pService.Release();
}

/**
 * DLL Entry Punkt, fuer DLL spezifische Funktionen beim Laden
 * der DLL. (wird fuer Services nicht gebraucht)
 */
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	return TRUE;
}
