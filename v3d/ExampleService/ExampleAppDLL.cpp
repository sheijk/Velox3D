// kann evtl weggelassen werden, da diese Deklarationen nie importiert werden
#ifdef EXAMPLEAPP_EXPORTS
#define EXAMPLEAPP_API __declspec(dllexport)
#else
#define EXAMPLEAPP_API __declspec(dllimport)
#endif
//-----------------------------------------------------------------------------
#include <Kernel/ObjReg/VObjectRegistry.h>
#include "VExampleApp.h"
#include <Utils/SmartPtr/VGuards.h>
#include "VExampleService.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//-----------------------------------------------------------------------------

/** instance of the application service */
VPointer<VExampleApp>::AutoPtr g_pService;
VPointer<VNamedObject>::AutoPtr g_pTest;
VPointer<VExampleService>::AutoPtr g_pExServ;

EXAMPLEAPP_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create the application service instance
	// (registers itself at the Object Registry)
//	g_pExServ.Reset(new VExampleService());

	g_pService.Reset(new VExampleApp());

	g_pTest.Reset(new VNamedObject("app.test", 0));

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
