#ifndef V3D_VOBJECTREGISTRYEXCEPTION_H
#define V3D_VOBJECTREGISTRYEXCEPTION_H
//------------------------------------------------------------------------
#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

class VObjectRegistryException : public VException
{
public:
	VObjectRegistryException(
		std::string in_Error, 
		std::string in_File, 
		int in_nLine);
};

//-----------------------------------------------------------------------------
} // namespace v3d
//------------------------------------------------------------------------
#endif // V3D_VOBJECTREGISTRYEXCEPTION_H
