/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
#include "CoreLibTests/VIteratorTests.h"
#include "CoreLibTests/VContainerTests.h"

#include "VFSTests/VFileStreamTest.h"
#include "VFSTests/VMemoryStreamTest.h"
#include "VFSTests/VFileSysTest.h"

#include "XMLTests/VXMLTests.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//-----------------------------------------------------------------------------
using namespace v3d;
using namespace unittests;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// add all tests here
VPointer<VStringTests>::AutoPtr g_pStringTests;
VPointer<VSmartPointerTest>::AutoPtr g_pSmartPtrTest;
VPointer<VIteratorTests>::AutoPtr g_pIterTests;
VPointer<VContainerTests>::AutoPtr g_pContainerTests;

VPointer<VFileStreamTest>::AutoPtr g_pFileStreamTest;
VPointer<VMemoryStreamTest>::AutoPtr g_pMemStreamTest;
VPointer<VFileSysTest>::AutoPtr g_pFileSysTest;

VPointer<VXMLTest>::AutoPtr g_pXmlTest;

//TODO: verfahren um die tests automatisch hinzuzufuegen

TESTSDLL_API void Initialize(VObjectRegistry* in_pObjReg)
{
	// store the object registry instance
	VObjectRegistry::SetInstance(in_pObjReg);

	// create tests and register them
	g_pStringTests.Assign(new VStringTests());
	g_pSmartPtrTest.Assign(new VSmartPointerTest());
	g_pContainerTests.Assign(new VContainerTests());
	g_pIterTests.Assign(new VIteratorTests());

	g_pFileStreamTest.Assign(new VFileStreamTest());
	g_pMemStreamTest.Assign(new VMemoryStreamTest());
	g_pFileSysTest.Assign(new VFileSysTest());

	g_pXmlTest.Assign(new VXMLTest());
}

TESTSDLL_API void Shutdown()
{
	// delete all tests (is this really neccessary? - sheijk)
	g_pXmlTest.Release();

	g_pFileSysTest.Release();
	g_pMemStreamTest.Release();
	g_pFileStreamTest.Release();

	g_pContainerTests.Release();
	g_pIterTests.Release();
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

