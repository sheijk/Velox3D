#include "VObjectRegistryExceptions.h"
//------------------------------------------------------------------------
using std::string;

VObjectRegistryException::VObjectRegistryException(
	string in_Error, 
	string in_File, 
	int in_nLine) :
	VException(in_Error, in_File, in_nLine)
{
}
