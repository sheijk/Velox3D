#ifndef V3D_VKERNELEXCEPTION_H
#define V3D_VKERNELEXCEPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VException.h>

#include <string>

//-----------------------------------------------------------------------------
namespace v3d {
namespace kernel {
//-----------------------------------------------------------------------------

class VKernelException : public VException
{
public:
	VKernelException(
		VStringParam in_Error, 
		VStringParam in_File, 
		int in_nLine)
		: VException(in_Error, in_File, in_nLine)
	{
	}
};

//-----------------------------------------------------------------------------
} // namespace kernel
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VKERNELEXCEPTION_H
