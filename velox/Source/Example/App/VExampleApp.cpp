#include "VExampleApp.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VLogging.h>
#include <v3d/Core/VIOStream.h>
#include <v3d/Updater/IVUpdateManager.h>
#include <v3d/Window/IVWindow.h>
#include <v3d/Window/IVWindowManager.h>
#include <v3d/System/IVSystemManager.h>
#include <v3d/Image/IVImageFactory.h>

#include <v3d/Graphics/DrawList/IVDrawList.h>

//TODO...
//#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <v3d/Utils/Graphics/VSimpleDrawList.h>
#include "../../UtilsLib/Importer/VObjModelImporter.h"
#include "../../UtilsLib/Importer/VModel3D.h"
#include <v3d/Input/IVInputManager.h>
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

void ApplyMaterial(IVDevice* in_m_pDevice, IVMaterial* in_pRenderStates)
{
	for(vuint prio = 0; prio < in_pRenderStates->StateCount(); ++prio)
	{
		in_m_pDevice->ApplyState(in_pRenderStates->GetState(prio));
	}
}

VMeshDescription BuildModel(IVDevice* in_pDevice, VStringParam in_pcFileName)
{
	utils::importer::VModel3D Model;
	utils::importer::VOBJModelImporter Importer;
	utils::importer::VQuake2BspImporter bspImporter;

	Importer.Create(in_pcFileName, &Model);
	//bspImporter.Create("/data/test.bsp", "none");

	IVDevice::Buffer VertexData(
		reinterpret_cast<vbyte*>(Model.m_Objects[0]->m_VerticesList),
		Model.m_Objects[0]->m_iNumVertices * 3 * sizeof(float));

	IVDevice::Buffer VertexIndex(
		reinterpret_cast<vbyte*>(Model.m_Objects[0]->m_pVertexIndex),
		Model.m_Objects[0]->m_iNumFaces * 3 * sizeof(int));

	IVDevice::Buffer TexData(
		reinterpret_cast<vbyte*>(Model.m_Objects[0]->m_TextureCoordsList),
		Model.m_Objects[0]->m_iNumTexCoords2f * 2 * sizeof(float));

	IVDevice::BufferHandle VertexHandle;
	IVDevice::BufferHandle VertexIndexHandle;
	IVDevice::BufferHandle TexHandle;

	//assign handles
	VertexHandle = in_pDevice->CreateBuffer(
		IVDevice::VertexBuffer,
		&VertexData,
		IVDevice::Buffer::CopyData
		);
	VertexIndexHandle = in_pDevice->CreateBuffer(
		IVDevice::VertexBuffer,
		&VertexIndex,
		IVDevice::Buffer::CopyData
		);
	TexHandle = in_pDevice->CreateBuffer(
		IVDevice::VertexBuffer,
		&TexData,
		IVDevice::Buffer::CopyData);

	VMeshDescription meshDesc;

	meshDesc.geometryType = VMeshDescription::TriangleStrip;
	meshDesc.triangleVertices = VMeshDescription::ByteDataRef(
		VertexHandle,
		0,
		Model.m_Objects[0]->m_iNumVertices * 3,
		1
		);
	meshDesc.triangleIndices = VMeshDescription::ByteDataRef(VertexIndexHandle,
		0, Model.m_Objects[0]->m_iNumFaces *3,
		1);

	meshDesc.triangleTexCoords = VMeshDescription::ByteDataRef(TexHandle,
		0, Model.m_Objects[0]->m_iNumTexCoords2f *2,
		1);

	return meshDesc;
}

VMaterialDescription BuildTextureMaterial(
	IVDevice* in_pDevice,
	VStringParam in_pcTextureFile)
{
	IVImageFactory* pFactory = QueryObject<IVImageFactory>("image.service");

	IVImageFactory::ImagePtr myImage = pFactory->CreateImage(in_pcTextureFile);

	VMaterialDescription texMat;

	VMaterialDescription::TextureRef* pTexRef =
		new VMaterialDescription::TextureRef();

	IVDevice::BufferHandle hTextureBuffer = in_pDevice->CreateBuffer(
		IVDevice::Texture,
		myImage->pData,
		IVDevice::Buffer::DropData
		);

	pTexRef->nWidth = myImage->iWidth;
	pTexRef->nHeight = myImage->iHeight;
	pTexRef->hData = hTextureBuffer;

	texMat.AddTexture(pTexRef);

	return texMat;
}

void VExampleApp::QueryButtons(IVInputManager* in_pInputManager)
{
	m_pEscapeButton		= &in_pInputManager->GetStandardKey(IVInputManager::Escape);
	m_pUpButton			= &in_pInputManager->GetStandardKey(IVInputManager::CursorUp);
	m_pDownButton		= &in_pInputManager->GetStandardKey(IVInputManager::CursorDown);
	m_pLeftButton		= &in_pInputManager->GetStandardKey(IVInputManager::CursorLeft);
	m_pRightButton		= &in_pInputManager->GetStandardKey(IVInputManager::CursorRight);

	m_pLeftMouseButton	= &in_pInputManager->GetMouseButton(1);
	m_pRightMouseButton	= &in_pInputManager->GetMouseButton(0);
}

void VExampleApp::MoveCamera(VCamera* in_pCamera)
{
	if(m_pUpButton->IsDown() == true)
		in_pCamera->AddZ(0.2f);

	if(m_pDownButton->IsDown() == true)
		in_pCamera->AddZ(-0.2f);

	if(m_pLeftButton->IsDown() == true)
		in_pCamera->AddX(0.2f);

	if(m_pRightButton->IsDown() == true)
		in_pCamera->AddX(-0.2f);

	if(m_pRightMouseButton->IsDown() == true)
		in_pCamera->AddY(-.3f);

	if(m_pLeftMouseButton->IsDown() == true)
		in_pCamera->AddY(.3f);
}

vint VExampleApp::Main()
{
	V3D_DEBUGMSG("Velox Main app says hi!");

	// get services
	IVUpdateManager* pUpdateManager = QueryObject<IVUpdateManager>("updater.service");
	IVSystemManager* pSystemManager = QueryObject<IVSystemManager>("system.service");
	IVWindowManager* pWindowManager = QueryObject<IVWindowManager>("window.manager");

	IVWindowManager::IVWindowPtr pWindow;
	pWindow = pWindowManager->QueryWindow("v3d window");
	m_pDevice = &(pWindow->QueryGraphicsDevice());

	IVInputManager* pInputManager;
	pInputManager = &(pWindow->QueryInputManager());

	VCamera* pCamera;

	//run system

	//pSystemManager->GetCPU(); // just for testing...

	QueryButtons(pInputManager);

	pCamera = new VCamera();
	pCamera->SetZ(-10.0f);
	m_pDevice->SetCamera(pCamera);

	// create textured mesh
	VMeshDescription meshDesc = BuildModel(m_pDevice, "/data/test.obj");
	VMaterialDescription texMat = BuildTextureMaterial(
		m_pDevice, "/data/tgatest.tga");

	IVDevice::MeshHandle pMesh = m_pDevice->CreateMesh(meshDesc, texMat);

	v3d::graphics::drawlist::VSimpleDrawList drawList(*m_pDevice);

	v3d::graphics::drawlist::VModel model;
	model.hMesh = pMesh;
	drawList.Add(model);

	// main loop
	pUpdateManager->Start();
	pSystemManager->SetStatus(true);

	while(pSystemManager->GetStatus())
	{
		m_pDevice->BeginScene();
		
		//ApplyMaterial(m_pDevice, &pMesh->GetMaterial());
		//m_pDevice->RenderMesh(pMesh);
		drawList.Render();

        m_pDevice->EndScene();

		pUpdateManager->StartNextFrame();
		pUpdateManager->GetFrameDuration();

		if (m_pEscapeButton->IsDown() == true)
			pSystemManager->SetStatus(false);

		// input checking
		MoveCamera(pCamera);
	}

	pUpdateManager->Stop();

	//exiting...
	return 0;
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------