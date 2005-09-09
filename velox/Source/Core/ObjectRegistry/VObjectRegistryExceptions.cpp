#include <v3d/Core/VObjectRegistryExceptions.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VObjectRegistryException::VObjectRegistryException(
	VStringParam in_Error, 
	VStringParam in_File, 
	int in_nLine) :
	VException(in_Error, in_File, in_nLine)
{
}

//-----------------------------------------------------------------------------
} // namespace v3d
