/**
* Example Service DLL
*
* Makro um Import und Export in der gleichen Datei zu realisieren
* wird nicht gebraucht, wg. dynamischen linken
*/
#define UNITTESTSUITE_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include "VTestManager.h"
#include "VTestSuite.h"
#include "VUnitTestExample.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::unittests;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// use a smart pointer to guarante object destruction
VPointer<IVTestManager>::AutoPtr g_pTestManager;
VPointer<VTestSuite>::AutoPtr g_pTestSuite;
VPointer<VUnitTestExample>::AutoPtr g_pExampleTest;

UNITTESTSUITE_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create service object and register it

	// create TestManager
	g_pTestManager.Assign(new VTestManager("testmngr"));

	// create Application
	g_pTestSuite.Assign(new VTestSuite("main"));

	// create example test
	g_pExampleTest.Assign(new VUnitTestExample());
}

UNITTESTSUITE_API void Shutdown()
{
	// delete and unregister service object
	g_pExampleTest.Release();
	g_pTestSuite.Release();
	g_pTestManager.Release();
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