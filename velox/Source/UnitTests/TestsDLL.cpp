/**
* Example Service DLL
*
* Makro um Import und Export in der gleichen Datei zu realisieren
* wird nicht gebraucht, wg. dynamischen linken
*/
#define TESTSDLL_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include "CoreLibTests/VStringTests.h"
#include "CoreLibTests/VSmartPointerTests.h"
#include "VFSTests/VFileStreamTest.h"
#include "VFSTests/VMemoryStreamTest.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>

//-----------------------------------------------------------------------------
using std::cout;
using std::endl;

using namespace v3d;
using namespace unittests;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// add all tests here
VPointer<VStringTests>::AutoPtr g_pStringTests;
VPointer<VSmartPointerTest>::AutoPtr g_pSmartPtrTest;
VPointer<VFileStreamTest>::AutoPtr g_pFileStreamTest;
VPointer<VMemoryStreamTest>::AutoPtr g_pMemStreamTest;

TESTSDLL_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create tests and register them
	g_pStringTests.Assign(new VStringTests());
	g_pSmartPtrTest.Assign(new VSmartPointerTest());
	g_pFileStreamTest.Assign(new VFileStreamTest());
	g_pMemStreamTest.Assign(new VMemoryStreamTest());
}

TESTSDLL_API void Shutdown()
{
	// delete all tests
	g_pMemStreamTest.Release();
	g_pFileStreamTest.Release();
	g_pSmartPtrTest.Release();
	g_pStringTests.Release();
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