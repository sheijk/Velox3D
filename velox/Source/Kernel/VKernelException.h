#ifndef V3D_VKERNELEXCEPTION_H
#define V3D_VKERNELEXCEPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VException.h>

#include <string>

//-----------------------------------------------------------------------------
namespace v3d {
namespace kernel {
//-----------------------------------------------------------------------------

	V3D_DECLARE_EXCEPTION(VKernelException, VException);
	V3D_DECLARE_EXCEPTION(VKernelIniException, VKernelException);

//-----------------------------------------------------------------------------
} // namespace kernel
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VKERNELEXCEPTION_H
