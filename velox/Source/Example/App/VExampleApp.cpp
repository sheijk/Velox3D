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
	const cnVertexCount = 36;
	VFloatBuffer vertexData(new float[cnVertexCount], cnVertexCount);
	VFloatBuffer colorData(new float[cnVertexCount], cnVertexCount);



	colorData[0]  = 0.0f;
	colorData[1]  = 1.0f;
	colorData[2]  = 0.0f;

	vertexData[0] = 0.0f;
	vertexData[1] = 1.0f;
	vertexData[2] = 0.0f;

	colorData[3]  = 0.0f;
	colorData[4]  = 0.0f;
	colorData[5]  = 1.0f;

	vertexData[3] = -1.0f;
	vertexData[4] = -1.0f;
	vertexData[5] = 1.0f;

	colorData[6]  = 1.0f;
	colorData[7]  = 0.0f;
	colorData[8]  = 0.0f;

	vertexData[6] = 1.0f;
	vertexData[7] = -1.0f;
	vertexData[8] = 1.0f;

	colorData[9]  = 0.3f;
	colorData[10]  = 0.4f;
	colorData[11]  = 0.6f;

	vertexData[9] = 0.0f;
	vertexData[10] = 1.0f;
	vertexData[11] = 0.0f;

	colorData[12]  = 0.4f;
	colorData[13]  = 0.0f;
	colorData[14]  = 0.7f;

	vertexData[12] = 1.0f;
	vertexData[13] = -1.0f;
	vertexData[14] = 1.0f;

	colorData[15]  = 0.0f;
	colorData[16]  = 0.0f;
	colorData[17]  = 0.7f;

	vertexData[15] = 1.0f;
	vertexData[16] = -1.0f;
	vertexData[17] = -1.0f;

	colorData[18]  = 0.7f;
	colorData[19]  = 0.0f;
	colorData[20]  = 0.0f;

	vertexData[18] = 0.0f;
	vertexData[19] = 1.0f;
	vertexData[20] = 0.0f;

	colorData[21]  = 0.6f;
	colorData[22]  = 0.3f;
	colorData[23]  = 0.4f;

	vertexData[21] = 1.0f;
	vertexData[22] = -1.0f;
	vertexData[23] = -1.0f;

	colorData[24]  = 1.0f;
	colorData[25]  = 1.0f;
	colorData[26]  = 1.0f;


	vertexData[24] = -1.0f;
	vertexData[25] = -1.0f;
	vertexData[26] = -1.0f;

	colorData[27]  = 0.1f;
	colorData[28]  = 0.6f;
	colorData[29]  = 0.9f;


	vertexData[27] = 0.0f;
	vertexData[28] = 1.0f;
	vertexData[29] = 0.0f;

	colorData[30]  = 0.0f;
	colorData[31]  = 1.0f;
	colorData[32]  = 1.0f;


	vertexData[30] = -1.0f;
	vertexData[31] = -1.0f;
	vertexData[32] = -1.0f;

	colorData[33]  = 1.0f;
	colorData[34]  = 0.0f;
	colorData[35]  = 1.0f;

	vertexData[33] = -1.0f;
	vertexData[34] = -1.0f;
	vertexData[35] = 1.0f;

	IVDevice::FloatBufferHandle bufHandle;

	bufHandle = pDevice->CreateBuffer(&vertexData, VFloatBuffer::CopyData);

	IVDevice::FloatBufferHandle colorHandle;

	colorHandle = pDevice->CreateBuffer(&colorData, VFloatBuffer::CopyData);


	VMeshDescription desc;
	desc.triangleVertices = VMeshDescription::FloatDataRef(bufHandle, 0, cnVertexCount, 1);
	desc.theColorsVertices = VMeshDescription::FloatDataRef(colorHandle, 0, cnVertexCount, 1);


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