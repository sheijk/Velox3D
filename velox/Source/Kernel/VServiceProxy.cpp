#include "VServiceProxy.h"
//-----------------------------------------------------------------------------
#include <iostream>
#include <v3d/Core/MemManager.h>

using namespace std;

//-----------------------------------------------------------------------------
using std::string;

namespace v3d {
	IVMemLogger* GetMemLogger();

namespace kernel {
//-----------------------------------------------------------------------------

VServiceProxy::VServiceProxy(const string &in_strDLL)
{
	m_strDLL = in_strDLL;

	m_pInitFunction = 0;
	m_pDeInitFunction = 0;

	m_hDllInstance = NULL;
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
		"?Initialize@@YAXPAUVModuleParams@v3d@@@Z");

	m_pDeInitFunction = (ShutdownFunction) GetProcAddress(
		m_hDllInstance, 
		"?Shutdown@@YAXXZ");

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

//-----------------------------------------------------------------------------
} // namespace kernel
} // namespace v3d
