#include "VExampleApp.h"
//-----------------------------------------------------------------------------
#include <v3d/ExampleService/IVExampleService.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VLogging.h>
#include <v3d/Core/VIOStream.h>
#include <v3d/Updater/IVUpdateManager.h>
#include <v3d/Window/IVWindow.h>
#include <v3d/Window/IVWindowManager.h>
#include <v3d/System/IVSystemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace example{
//-----------------------------------------------------------------------------
using namespace v3d::console;
using v3d::updater::IVUpdateManager;
using namespace v3d::graphics;
using namespace v3d::window;
using namespace v3d::system;



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

	
	//m_Console = QueryObject<IVConsoleSerivce>("console.service");

	/*if(!m_Console)
		V3D_THROW(VException, "console service not found");*/
	
	V3D_DEBUGMSG("Velox Main app says hi!");

	// get update manager
	IVUpdateManager& updater = * QueryObject<IVUpdateManager>("updater.service");
	
	IVSystemManager* system = QueryObject<IVSystemManager>("system.service");
	IVWindowManager* winmanager = QueryObject<IVWindowManager>("window.manager");
	
	typedef VPointer<IVWindow>::SharedPtr IVWindowInterface;
	IVWindowInterface win;


	win = winmanager->CreateWindow("v3d window");

	
	// main loop
	updater.Start();
	system->SetStatus(true);

	while(system->GetStatus())
	{
		updater.StartNextFrame();
	}

	updater.Stop();

	return 0;
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------