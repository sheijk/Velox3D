#include "VServiceProxy.h"
//-----------------------------------------------------------------------------
using std::string;

//-----------------------------------------------------------------------------

VServiceProxy::VServiceProxy(const string &in_strDLL)
{
	m_strDLL = in_strDLL;

	m_pInitFunction = 0;
	m_pDeInitFunction = 0;

	m_hDllInstance = NULL;
}

VServiceProxy::~VServiceProxy()
{
}

void VServiceProxy::Initialize(VObjectRegistry* in_pObjectRegistry)
{
	// abort if already initialized


	// load the dll file
	m_hDllInstance = LoadLibraryEx(m_strDLL.c_str(), 0, 0);

	if( NULL == m_hDllInstance )
	{
		V3D_THROW(VKernelException, 
			string("could not load DLL file <")
			+ m_strDLL
			+ string(">") );
	}

	// store the function pointers
	m_pInitFunction = (InitFunction) GetProcAddress(m_hDllInstance, "?Initialize@@YAXPAVVObjectRegistry@@@Z");
	m_pDeInitFunction = (ShutdownFunction) GetProcAddress(m_hDllInstance, "?Shutdown@@YAXXZ");

	if( 0 == m_pInitFunction || 0 == m_pDeInitFunction )
	{
		V3D_THROW(VKernelException,
			"could not get address of Initialize/DeInitialize function of DLL \""
			+ m_strDLL + "\"");
	}
	
	// call the init function
	m_pInitFunction(in_pObjectRegistry);
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
