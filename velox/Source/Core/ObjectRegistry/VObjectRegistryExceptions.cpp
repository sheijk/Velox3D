#include <v3d/Core/VObjectRegistryExceptions.h>
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------
using std::string;

namespace v3d {
//-----------------------------------------------------------------------------

VObjectRegistryException::VObjectRegistryException(
	string in_Error, 
	string in_File, 
	int in_nLine) :
	VException(in_Error, in_File, in_nLine)
{
}

//-----------------------------------------------------------------------------
} // namespace v3d
