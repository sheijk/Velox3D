#include "VExampleApp.h"
//-----------------------------------------------------------------------------
#include <ExampleService/IVExampleService.h>
#include <Kernel/ObjReg/VObjectRegistry.h>

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