#include "VExampleService.h"
//-----------------------------------------------------------------------------

VExampleService::VExampleService() :
	IVExampleService("exService", 0)
{

}

VExampleService::~VExampleService()
{

}

vint VExampleService::GiveMeFive()
{
	return 5;
}


