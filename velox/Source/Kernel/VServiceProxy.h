#ifndef V3D_VSERVICEPROXY_H
#define V3D_VSERVICEPROXY_H
//------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "VKernelException.h"

#include <string>
#include <windows.h>

//-----------------------------------------------------------------------------
namespace v3d {

class VObjectRegistry;

namespace kernel {
//-----------------------------------------------------------------------------

/**
 * A proxy to use the DLL info of a service
 * @author sheijk
 * @version 1.0
 * @updated 06-Apr-2003 22:59:55
 */
class VServiceProxy
{
private:
	VServiceProxy();
	
	std::string m_strDLL;

	typedef void (*InitFunction)(VObjectRegistry*);
	typedef void (*ShutdownFunction)();

	InitFunction m_pInitFunction;
	ShutdownFunction m_pDeInitFunction;

	HINSTANCE m_hDllInstance;
	vbool m_bIsLoaded;
public:
	VServiceProxy(const std::string& in_strDLL);

	virtual  ~VServiceProxy();
	
	//VSharedPtr<IVContainer<VString>> GetDependencies();
	void Initialize(VObjectRegistry* in_pObjectRegistry);
	void Shutdown();
};

//-----------------------------------------------------------------------------
} // namespace kernel
} // namespace v3d
//------------------------------------------------------------------------
#endif // V3D_VSERVICEPROXY_H
