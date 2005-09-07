#include "VServiceProxyLinux.h"
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

VServiceProxy::VServiceProxy(const string &in_strDLL)
{
}

VServiceProxy::~VServiceProxy()
{
}

void VServiceProxy::Initialize(VObjectRegistry* in_pObjectRegistry)
{
    V3D_THROW(
        VKernelException, 
        VString("VServiceProxy_LINUX::Initialize -> not yet implemented")
    );
}

void VServiceProxy::Shutdown()
{
    V3D_THROW(
        VKernelException, 
        VString("VServiceProxy_LINUX::Shutdowne -> not yet implemented")
    );
}

//-----------------------------------------------------------------------------
} // namespace kernel
} // namespace v3d
