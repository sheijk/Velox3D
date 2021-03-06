/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VServiceProxy.h"
//-----------------------------------------------------------------------------
#include <iostream>
#include <V3d/Core/MemManager.h>

using namespace std;

//-----------------------------------------------------------------------------
using std::string;

namespace v3d {
	IVMemLogger* GetMemLogger();

namespace kernel {
//-----------------------------------------------------------------------------
#ifdef V3D_WIN32
VServiceProxy::VServiceProxy(const string &in_strDLL)
{
	m_strDLL = in_strDLL;

	m_pInitFunction = 0;
	m_pDeInitFunction = 0;

	m_hDllInstance = 0;
	m_bIsLoaded = false;
}

VServiceProxy::~VServiceProxy()
{
}

void VServiceProxy::Initialize(VObjectRegistry* in_pObjectRegistry)
{
	// abort if already initialized
	if(m_bIsLoaded)
		return;

	// load the dll file
	m_hDllInstance = LoadLibraryEx(m_strDLL.c_str(), 0, 0);

	if( NULL == m_hDllInstance )
	{
		V3D_THROW(VKernelException, 
			VString("could not load DLL file <")
			+ m_strDLL.c_str()
			+ ">" );
	}

	// store the function pointers
	m_pInitFunction = (InitFunction) GetProcAddress(
		m_hDllInstance, 
		//"?Initialize@@YAXPAVVObjectRegistry@v3d@@@Z");
		"Initialize");

	m_pDeInitFunction = (ShutdownFunction) GetProcAddress(
		m_hDllInstance, 
		"Shutdown");

	if( 0 == m_pInitFunction || 0 == m_pDeInitFunction )
	{
		V3D_THROW(VKernelException,
			"could not get address of Initialize/DeInitialize function of DLL \""
			+ VString(m_strDLL.c_str()) + "\"");
	}
	
	// call the init function
	VModuleParams modParams;
	modParams.pObjectRegistry = in_pObjectRegistry;
	modParams.pMemLogger = GetMemLogger();
	//modParams.pMemoryManager = GetMemoryManager();
	m_pInitFunction(&modParams);
	m_bIsLoaded = true;
}

void VServiceProxy::Shutdown()
{
	// call deinitialize function
	if( 0 != m_pDeInitFunction )
	{
		m_pDeInitFunction();
	}

	// unload DLL
	FreeLibrary(m_hDllInstance);
}
#endif
//-----------------------------------------------------------------------------
} // namespace kernel
} // namespace v3d

