/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

/**
 * Link this file to every service module (dll).
 * Derive a class from VModuleBase and create a global instance of it
 * for every service dll. The initialize and shutdown functions of
 * your instance will be called automatically
 */
#ifdef V3D_WIN32
#define V3D_MODULE_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VGuards.h>
#include <V3d/Core/Modules/VModuleParams.h>
#include <V3d/Core/Modules/VModuleBase.h>
#include <V3d/Utils/VRegisterGuard.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------
namespace v3d {
	void SetMemLogger(IVMemLogger* in_pMemLogger);
} // namespace v3d
//-----------------------------------------------------------------------------

VModuleBase::VModuleBase(/*VStringParam in_pcModuleName*/)
{
	if( s_pModule == 0 )
	{
		s_pModule = this;
		s_pcModuleName = v3d::GetModuleName();
		//s_pcModuleName = in_pcModuleName;
	}
	else
		V3D_THROW(VModuleLoadFailure, "more than on module instances");
}

VModuleBase::~VModuleBase()
{
}

VModuleBase* VModuleBase::GetInstance()
{
	if( s_pModule == 0 )
	{
		V3D_THROW(VModuleLoadFailure,
			"no global instance of VModuleBase derived class found"
			" - cannont load module"
			);
	}

	return s_pModule;
}

const vchar* VModuleBase::GetModuleName()
{
	return s_pcModuleName;
}

VModuleBase* VModuleBase::s_pModule(0);
const vchar* VModuleBase::s_pcModuleName(0);

namespace {
	vuint g_ModuleId = 0;
};

//-----------------------------------------------------------------------------
//void SetMemoryManager(
//	v3d::IVMemoryManager* in_pMemoryManager,
//	const char* in_pcModuleName
//	);

extern "C" {
	void Initialize(VModuleParams* in_pParams)
	{
		// set the memory manager
		//SetMemoryManager(
		//	in_pParams->pMemoryManager,
		//	VModuleBase::GetInstance()->GetModuleName()
		//	);

		// store the object registry instance
		VObjectRegistry::SetInstance(in_pParams->pObjectRegistry);

		//g_ModuleId = in_pParams->moduleId;
		SetMemLogger(in_pParams->pMemLogger);

		if( VModuleBase::GetInstance() != 0 )
			VModuleBase::GetInstance()->Initialize();

		//utils::VRegisterGuardBase::RegisterAll();
	}

	void Shutdown()
	{
		//utils::VRegisterGuardBase::UnregisterAll();

		if( VModuleBase::GetInstance() != 0 )
			VModuleBase::GetInstance()->Shutdown();
	}
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
#endif
