#include "VExampleService.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace example {
//-----------------------------------------------------------------------------

VExampleService::VExampleService(VStringParam in_strName) :
	IVExampleService(in_strName, 0)
{

}

VExampleService::~VExampleService()
{

}

vint VExampleService::GiveMeFive()
{
	return 5;
}

//-----------------------------------------------------------------------------
} // example
} // v3d
//-----------------------------------------------------------------------------

