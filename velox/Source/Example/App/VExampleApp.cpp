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
#include <v3d/Image/IVImageFactory.h>


//TODO...
//#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
#include "../../UtilsLib/Importer/VObjModelImporter.h"
#include "../../UtilsLib/Importer/VModel3D.h"
#include <v3d/Input/IVInputManager.h>
#include <v3d/Graphics/VCamera.h>
#include "../../UtilsLib/Importer/VQuake2BspImporter.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace example{
//-----------------------------------------------------------------------------
using namespace v3d::updater;
using namespace v3d::console;
using namespace v3d::graphics;
using namespace v3d::window;
using namespace v3d::system;
using namespace v3d::input;
using namespace v3d::image;

VExampleApp::VExampleApp(VStringParam in_strName)
	: VNamedObject(in_strName, 0)
{
	V3D_DEBUGMSG("Example app has been created and registered");
}

VExampleApp::~VExampleApp()
{
	V3D_DEBUGMSG("Example app has been destroyed and unregistered");
}

void ApplyMaterial(IVDevice* in_pDevice, IVMaterial* in_pRenderStates)
{
	for(vuint prio = 0; prio < in_pRenderStates->StateCount(); ++prio)
	{
		in_pDevice->ApplyState(in_pRenderStates->GetState(prio));
	}
}

vint VExampleApp::Main()
{
	V3D_DEBUGMSG("Velox Main app says hi!");

	// get services
	IVUpdateManager* pUpdateManager = QueryObject<IVUpdateManager>("updater.service");
	IVSystemManager* pSystemManager = QueryObject<IVSystemManager>("system.service");
	IVWindowManager* pWindowManager = QueryObject<IVWindowManager>("window.manager");
	IVImageFactory*  pFactory		= QueryObject<IVImageFactory>("image.service");

	//geting later...
	IVInputManager* pInputManager;


	IVWindowManager::IVWindowPtr pWindow;
	IVDevice* pDevice;
	IVButton* pEscButton;
	IVButton* pUpButton;
	IVButton* pDownButton;
	IVButton* pLeftButton;
	IVButton* pRightButton;

	IVButton* pLeftMouseButton;
	IVButton* pRightMouseButton;

	util::importer::VModel3D Model;
	util::importer::VOBJModelImporter Importer;
	util::importer::VQuake2BspImporter bspImporter;

	VMeshDescription MeshDesc;
	IVDevice::MeshHandle Mesh;

	VCamera* pCamera;

	//run system

	//pSystemManager->GetCPU(); // just for testing...

	pWindow = pWindowManager->QueryWindow("v3d window");
	pDevice = &(pWindow->QueryGraphicsDevice());

	pInputManager = &(pWindow->QueryInputManager());

	pEscButton			= &pInputManager->GetStandardKey(IVInputManager::Escape);
	pUpButton			= &pInputManager->GetStandardKey(IVInputManager::CursorUp);
	pDownButton			= &pInputManager->GetStandardKey(IVInputManager::CursorDown);
	pLeftButton			= &pInputManager->GetStandardKey(IVInputManager::CursorLeft);
	pRightButton		= &pInputManager->GetStandardKey(IVInputManager::CursorRight);

	pLeftMouseButton	= &pInputManager->GetMouseButton(1);
	pRightMouseButton	= &pInputManager->GetMouseButton(0);


	pCamera = new VCamera();
	pCamera->SetZ(-10.0f);
	pDevice->SetCamera(pCamera);

	Importer.Create("/data/test.obj", &Model);
	bspImporter.Create("/data/test.bsp", "none");

	// create a test mesh

	IVDevice::Buffer VertexData(
		reinterpret_cast<vbyte*>(Model.m_Objects[0]->m_VerticesList),
		Model.m_Objects[0]->m_iNumVertices * 3 * sizeof(float));

	IVDevice::Buffer VertexIndex(
		reinterpret_cast<vbyte*>(Model.m_Objects[0]->m_pVertexIndex),
		Model.m_Objects[0]->m_iNumFaces * 3 * sizeof(int));

	IVDevice::Buffer TexData(
		reinterpret_cast<vbyte*>(Model.m_Objects[0]->m_TextureCoordsList),
		Model.m_Objects[0]->m_iNumTexCoords2f * 2 * sizeof(float));


	//VFloatBuffer VertexData((vfloat32*)bspImporter.m_pVertices,bspImporter.m_iNumVertices *3);
	//VIntBuffer VertexIndex(bspImporter.m_pIndexList, bspImporter.m_iNumFaceElements);
	//VFloatBuffer TexData(bspImporter.m_TextureCoordsList,
	//	Model.m_Objects[0]->m_iNumTexCoords2f * 2);

	IVDevice::BufferHandle VertexHandle;
	IVDevice::BufferHandle VertexIndexHandle;
	IVDevice::BufferHandle TexHandle;

	//assign handles
	VertexHandle = pDevice->CreateBuffer(
		IVDevice::VertexBuffer,
		&VertexData,
		IVDevice::Buffer::CopyData
		);
	VertexIndexHandle = pDevice->CreateBuffer(
		IVDevice::VertexBuffer,
		&VertexIndex,
		IVDevice::Buffer::CopyData
		);
	TexHandle = pDevice->CreateBuffer(
		IVDevice::VertexBuffer,
		&TexData,
		IVDevice::Buffer::CopyData);


	/*MeshDesc.triangleVertices = VMeshDescription::FloatDataRef(VertexHandle,
		0, bspImporter.m_iNumVertices *3,
		1);
	MeshDesc.triangleIndices = VMeshDescription::IntDataRef(VertexIndexHandle,
		0, bspImporter.m_iNumFaceElements,
		1);

	MeshDesc.triangleCoords = VMeshDescription::FloatDataRef(TexHandle,
		0, Model.m_Objects[0]->m_iNumTexCoords2f *2,
		1);*/

	MeshDesc.triangleVertices = VMeshDescription::ByteDataRef(
		VertexHandle,
		0,
		Model.m_Objects[0]->m_iNumVertices * 3,
		1
		);
	MeshDesc.triangleIndices = VMeshDescription::ByteDataRef(VertexIndexHandle,
		0, Model.m_Objects[0]->m_iNumFaces *3,
		1);

	MeshDesc.triangleTexCoords = VMeshDescription::ByteDataRef(TexHandle,
		0, Model.m_Objects[0]->m_iNumTexCoords2f *2,
		1);



	Mesh = pDevice->CreateMesh(MeshDesc);

	// main loop
	pUpdateManager->Start();
	pSystemManager->SetStatus(true);

	// main loop...
	IVImageFactory::ImagePtr myImage = pFactory->CreateImage("/data/tgatest.tga");

    VMaterialDescription texMat;

	VMaterialDescription::TextureRef* pTexRef =
		new VMaterialDescription::TextureRef();

	IVDevice::BufferHandle hTextureBuffer = pDevice->CreateBuffer(
		IVDevice::Texture,
		myImage->pData,
		IVDevice::Buffer::DropData
		);

	pTexRef->nWidth = myImage->iWidth;
	pTexRef->nHeight = myImage->iHeight;
	pTexRef->hData = hTextureBuffer;

	texMat.AddTexture(pTexRef);

	IVDevice::MaterialHandle pTextureMaterial = pDevice->CreateMaterial(texMat);

	while(pSystemManager->GetStatus())
	{
		pDevice->BeginScene();
		ApplyMaterial(pDevice, pTextureMaterial);
		pDevice->RenderMesh(Mesh);
        pDevice->EndScene();

		pUpdateManager->StartNextFrame();
		pUpdateManager->GetFrameDuration();

		// input checking
		if (pEscButton->IsDown() == true)
			pSystemManager->SetStatus(false);

		if(pUpButton->IsDown() == true)
			pCamera->AddZ(0.2f);

		if(pDownButton->IsDown() == true)
			pCamera->AddZ(-0.2f);

		if(pLeftButton->IsDown() == true)
			pCamera->AddX(0.2f);

		if(pRightButton->IsDown() == true)
			pCamera->AddX(-0.2f);

		if(pRightMouseButton->IsDown() == true)
			pCamera->AddY(-.3f);
		if(pLeftMouseButton->IsDown() == true)
			pCamera->AddY(.3f);

	}

	pUpdateManager->Stop();

	//exiting...
	return 0;
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------