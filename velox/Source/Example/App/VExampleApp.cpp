#include "VExampleApp.h"
//-----------------------------------------------------------------------------
#include <v3d/ExampleService/IVExampleService.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VLogging.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace example {
//-----------------------------------------------------------------------------

VExampleApp::VExampleApp() : VNamedObject("main", 0)
{
	V3D_DEBUGMSG("Example app has been created and registered");
}

VExampleApp::~VExampleApp()
{
	V3D_DEBUGMSG("Example app has been destroyed and unregistered");
}

vint VExampleApp::Main()
{
	// get the example service
	IVExampleService* pExServ = QueryObject<IVExampleService>("exService");

	if( 0 != pExServ )
	{
		V3D_DEBUGMSG("example service could be queried and will be used now");
		return pExServ->GiveMeFive();
	}
	else 
	{
		V3D_DEBUGMSG("Example service could not be queried, -> failure");
		return -1;
	}
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------
