/**
 * Link this file to every service module (dll).
 * Derive a class from VModuleBase and create a global instance of it
 * for every service dll. The initialize and shutdown functions of
 * your instance will be called automagically
 */

#define V3D_MODULE_API __declspec(dllexport)

//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include <v3d/Core/Modules/VModuleParams.h>
#include <v3d/Core/Modules/VModuleBase.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------

VModuleBase::VModuleBase(VStringParam in_pcModuleName)
{
	if( s_pModule == 0 )
	{
		s_pModule = this;
		s_pcModuleName = in_pcModuleName;
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

//-----------------------------------------------------------------------------
//void SetMemoryManager(
//	v3d::IVMemoryManager* in_pMemoryManager,
//	const char* in_pcModuleName
//	);

V3D_MODULE_API void Initialize(VModuleParams* in_pParams)
{
	// set the memory manager
	//SetMemoryManager(
	//	in_pParams->pMemoryManager,
	//	VModuleBase::GetInstance()->GetModuleName()
	//	);

	// store the object registry instance
	VObjectRegistry::SetInstance(in_pParams->pObjectRegistry);

	if( VModuleBase::GetInstance() != 0 )
		VModuleBase::GetInstance()->Initialize();
}

V3D_MODULE_API void Shutdown()
{
	if( VModuleBase::GetInstance() != 0 )
		VModuleBase::GetInstance()->Shutdown();
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