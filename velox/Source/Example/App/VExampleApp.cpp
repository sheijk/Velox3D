#include "VExampleApp.h"
//-----------------------------------------------------------------------------
#include <v3d/ExampleService/IVExampleService.h>
#include <v3d/Core/VObjectRegistry.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace example {
//-----------------------------------------------------------------------------

VExampleApp::VExampleApp() : VNamedObject("main", 0)
{
}

VExampleApp::~VExampleApp()
{
}

vint VExampleApp::Main()
{
	//try
	//{
		// get the example service
		IVExampleService* pExServ = QueryObject<IVExampleService>("exService");

		if( 0 != pExServ )
		{
			return pExServ->GiveMeFive();
		}
	/*
	}
	catch(std::bad_cast exc)
	{
		int i = 1;
	}
	*/
	return -1;
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------
