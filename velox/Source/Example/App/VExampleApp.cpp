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
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Utils/Graphics/VCubeMeshDescr.h>
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
	V3D_DEBUGMSG("Velox Main app says hi!");

	// get update manager
	IVUpdateManager& updater = * QueryObject<IVUpdateManager>("updater.service");
	
	IVSystemManager* system = QueryObject<IVSystemManager>("system.service");
	IVWindowManager* winmanager = QueryObject<IVWindowManager>("window.manager");
	
	// warum nicht typedef IVWindowManager::WindowPtr ... oder so? waere leichter "wartbar" (sheijk)
	typedef VPointer<IVWindow>::SharedPtr IVWindowInterface;
	IVWindowInterface win;


	system->GetCPU(); // just for testing...
	win = winmanager->CreateWindow("v3d window");

	IVDevice* m_Device;
	m_Device = &(win->QueryGraphicsDevice());

	VCubeMeshDescr test(1);
	IVMesh* testMesh;

//	testMesh = m_Device->CreateMesh(&test);

	
	// main loop
	updater.Start();
	system->SetStatus(true);

	while(system->GetStatus())
	{
		m_Device->BeginScene();
//		m_Device->RenderMesh(testMesh);
		updater.StartNextFrame();
		m_Device->EndScene();
	}

	updater.Stop();

	return 0;
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------