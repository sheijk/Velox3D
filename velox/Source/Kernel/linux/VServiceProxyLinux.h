#ifndef V3D_VSERVICEPROXY_LINUX_H
#define V3D_VSERVICEPROXY_LINUX_H
//------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/Modules/VModuleParams.h>

#include "../VKernelException.h"

#include <string>

//-----------------------------------------------------------------------------
namespace v3d {

class VObjectRegistry;

namespace kernel {
//-----------------------------------------------------------------------------

/**
 * A proxy to use the DLL info of a service - Linux/gcc version by nsn
 * @author sheijk
 * @version 1.0
 * @updated 06-Apr-2003 22:59:55
 */
class VServiceProxy
{
private:
	VServiceProxy();
	
public:
	VServiceProxy(const std::string& in_strDLL);

	virtual  ~VServiceProxy();
	
	void Initialize(VObjectRegistry* in_pObjectRegistry);
	void Shutdown();
};

//-----------------------------------------------------------------------------
} // namespace kernel
} // namespace v3d
//------------------------------------------------------------------------
#endif // V3D_VSERVICEPROXY_H
