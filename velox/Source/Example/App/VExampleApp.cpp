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
	
	// warum nicht typedef IVWindowManager::WindowPtr ... oder so? 
	// waere leichter "wartbar" (sheijk)
	typedef VPointer<IVWindow>::SharedPtr WindowInterface;
	WindowInterface win;


	system->GetCPU(); // just for testing...
	win = winmanager->CreateWindow("v3d window");

	IVDevice* pDevice;
	pDevice = &(win->QueryGraphicsDevice());

	// create a test mesh
    // dafuer brauchen wir spaeter hilfsklassen...
	const cnVertexCount = 9;
	VFloatBuffer vertexData(new float[cnVertexCount], cnVertexCount);

	vertexData[0] = 1.0f;
	vertexData[1] = 0.0f;
	vertexData[2] = 0.0f;

	vertexData[3] = 0.0f;
	vertexData[4] = 1.0f;
	vertexData[5] = 0.0f;

	vertexData[6] = -1.0f;
	vertexData[7] = 0.0f;
	vertexData[8] = 0.0f;

	IVDevice::FloatBufferHandle bufHandle;

	bufHandle = pDevice->CreateBuffer(&vertexData, VFloatBuffer::CopyData);

	VMeshDescription desc;
	desc.triangleVertices = VMeshDescription::FloatDataRef(bufHandle, 0, 9, 1);

	IVMesh& mesh( pDevice->CreateMesh(desc) );
	
	// main loop
	updater.Start();
	system->SetStatus(true);

	while(system->GetStatus())
	{
		pDevice->BeginScene();
		pDevice->RenderMesh(mesh);
		updater.StartNextFrame();
		pDevice->EndScene();
	}

	updater.Stop();

	return 0;
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------