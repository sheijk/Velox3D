#ifndef V3D_VKERNELEXCEPTION_H
#define V3D_VKERNELEXCEPTION_H
//-----------------------------------------------------------------------------
#include <Error/VException.h>

#include <string>

class VKernelException : public VException
{
public:
	VKernelException(
		std::string in_Error, 
		std::string in_File, 
		int in_nLine)
		: VException(in_Error, in_File, in_nLine)
	{
	}
};

//-----------------------------------------------------------------------------
#endif // V3D_VKERNELEXCEPTION_H
