#include "VExampleService.h"
//-----------------------------------------------------------------------------

const std::string VExampleService::s_strId = "exService";

VExampleService::VExampleService() :
	VNamedObject(s_strId, 0)
{

}

VExampleService::~VExampleService()
{

}

const std::string& VExampleService::GetServiceId()
{
	return s_strId;
}
