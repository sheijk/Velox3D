#include "VExampleApp.h"
//-----------------------------------------------------------------------------
#include <v3d/ExampleService/IVExampleService.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VLogging.h>
#include <v3d/Core/VIOStream.h>
#include <v3d/Updater/IVUpdateManager.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace example{
//-----------------------------------------------------------------------------
using namespace v3d::console;
using v3d::updater::IVUpdateManager;

VExampleApp::VExampleApp(VStringParam in_strName) 
	: VNamedObject(in_strName, 0)
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

	/*if( 0 != pExServ )
	{
		V3D_DEBUGMSG("example service could be queried and will be used now");
		//return pExServ->GiveMeFive();
	}
	else 
	{
		V3D_DEBUGMSG("Example service could not be queried, -> failure");
		return -1;
	}*/

	Initialize();
	
	V3D_DEBUGMSG("Velox Main app says hi!");

	// get update manager
	IVUpdateManager& updater = * QueryObject<IVUpdateManager>("updater.service");
	
	// main loop
	bool bActive = true;

	//TODO: fix. (bool Active() in update manager?)
	//updater.Mainloop();
	updater.Start();
	while(bActive)
	{
		updater.StartNextFrame();
	}
	updater.Stop();

	return 0;
}

void VExampleApp::Initialize()
{

	m_Console = QueryObject<IVConsoleSerivce>("console.service");

	if(!m_Console)
		V3D_THROW(VException, "console service not found");
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------