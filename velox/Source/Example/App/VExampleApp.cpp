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

#include <v3d/Utils/Graphics/VBox.h>
#include <v3d/Utils/Graphics/VColor4f.h>
#include <v3d/Utils/Graphics/VTexCoord2f.h>
#include <v3d/Utils/Graphics/VVector3f.h>
#include <v3d/Utils/Graphics/VVertexDataLayout.h>
#include <v3d/Utils/Graphics/VGeometryUtil.h>

#include <v3d/Math/VMatrixOps.h>

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

#include <v3d/Utils/Graphics/SimpleSG/VMeshNode.h>
#include <v3d/Utils/Graphics/SimpleSG/VTransformNode.h>
#include <v3d/Utils/Graphics/SimpleSG/VSceneGraphTools.h>
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
using namespace v3d::utils::graphics;
using namespace v3d::utils::graphics::drawlist;
using namespace v3d::graphics::drawlist;
using namespace v3d::graphics::simplesg;

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
		0
		);
	meshDesc.triangleIndices = VMeshDescription::ByteDataRef(VertexIndexHandle,
		0, Model.m_Objects[0]->m_iNumFaces * 3,
		0);

	meshDesc.triangleTexCoords = VMeshDescription::ByteDataRef(TexHandle,
		0, Model.m_Objects[0]->m_iNumTexCoords2f *2,
		0);

	//meshDesc.geometryType = VMeshDescription::TriangleStrip;

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
	m_pMouseXAxis		= &in_pInputManager->GetMouseXAxis();
	m_pMouseYAxis		= &in_pInputManager->GetMouseYAxis();


}

void VExampleApp::MoveCamera(VCamera* in_pCamera)
{
	const vfloat32 fSeconds = m_pUpdateManager->GetFrameDuration();

	if(m_pUpButton->IsDown() == true)
		in_pCamera->MoveForward(-5.0f * fSeconds);

	if(m_pDownButton->IsDown() == true)
		in_pCamera->MoveForward(5.0f * fSeconds);

	if(m_pLeftButton->IsDown() == true)
		in_pCamera->Strafe(-5 * fSeconds);


	if(m_pRightButton->IsDown() == true)
		in_pCamera->Strafe(5 * fSeconds);


	if(m_pRightMouseButton->IsDown() == true)
		in_pCamera->RotateZ(-5 * fSeconds);


	if(m_pLeftMouseButton->IsDown() == true)
		in_pCamera->RotateZ(5 * fSeconds);

	in_pCamera->RotateX(- m_pMouseYAxis->GetLastMovement() * 5 * fSeconds);
	in_pCamera->RotateY(m_pMouseXAxis->GetLastMovement() * 5 * fSeconds);

}

void Translate(VMatrix44f& io_Matrix, float x, float y, float z)
{
	io_Matrix.Set(0, 3, x);
	io_Matrix.Set(1, 3, y);
	io_Matrix.Set(2, 3, z);
}

VMatrix44f BuildTranslateMatrix(float x, float y, float z)
{
	VMatrix44f mat;

	Identity(mat);
	Translate(mat, x, y, z);

	return mat;
}

using namespace v3d::graphics::simplesg;

IVNode* CreateMeshTransformNode(
								IVDevice::MeshHandle in_hMesh, 
								const VMatrix44f& in_Transform)
{
	VMeshNode* pMeshNode = new VMeshNode(in_hMesh);
	VTransformNode* pTransformNode = new VTransformNode(in_Transform);
	pTransformNode->AddChild(pMeshNode);

	return pTransformNode;
}

struct ColoredVertex
{
	ColoredVertex()
	{
		VVertexDataLayout::SetPositionOffset<ColoredVertex>();
		VVertexDataLayout::SetColorOffset<ColoredVertex>();
		VVertexDataLayout::SetTexCoordOffset<ColoredVertex>();
	}

	VVector3f position;
	VColor4f color;
	VTexCoord2f texCoords;

	static VVertexDataLayout layout;
};

VVertexDataLayout ColoredVertex::layout;

#include <Windows.h>
#include <gl/GL.h>

vint VExampleApp::Main()
{
	V3D_DEBUGMSG("Velox Main app says hi!");

	// get services
	m_pUpdateManager = QueryObject<IVUpdateManager>("updater.service");
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
	//pCamera->SetZ(-10.0f);
	//m_pDevice->SetCamera(pCamera);

	// build scene graph
	VPointer<IVNode>::AutoPtr pRootNode;

	VMatrix44f identity;
	Identity(identity);

	pRootNode.Assign(new VTransformNode(identity));

	// create textured mesh and add it to SG
	{
		VMeshDescription meshDesc = BuildModel(m_pDevice, "/data/test.obj");
		VMaterialDescription texMat = BuildTextureMaterial(
			m_pDevice, "/data/tgatest.tga");

		IVDevice::MeshHandle pMesh = m_pDevice->CreateMesh(meshDesc, texMat);

		VMatrix44f transform;
		Identity(transform);
		// change x value
		transform.Set(0, 3, 3);
		VTransformNode* pTransformNode = new VTransformNode(transform);
		pRootNode->AddChild(pTransformNode);

        VMeshNode* pMeshNode = new VMeshNode(pMesh);
		pTransformNode->AddChild(pMeshNode);
	}

	{
		utils::graphics::VBox<ColoredVertex> box(.9f, .9f, .9f);
		box.CreateCoordinates();

		for(int vertnum = 0; vertnum < box.buffer.GetSize(); ++vertnum)
		{
			box.buffer[vertnum].color = VColor4f(1, 0, 0, 1);
		}		
		
		VMeshDescription md = BuildMeshDescription(
			*m_pDevice,
			box.buffer.GetDataAddress(),
			box.buffer.GetSize()
			);

		IVDevice::MeshHandle hMesh = m_pDevice->CreateMesh(
			md, 
			VMaterialDescription());
		
		//pRootNode->AddChild(
		//	CreateMeshTransformNode(hMesh, BuildTranslateMatrix(0, 0, -6))
		//	);

		//for(int xpos = -15; xpos < 15; xpos += 3)
		//for(int ypos = -15; ypos < 15; ypos += 3)
		//for(int zpos = -15; zpos < 15; zpos += 3)
		//{
		//	pRootNode->AddChild(
		//		CreateMeshTransformNode(hMesh, BuildTranslateMatrix(xpos, ypos, zpos))
		//		);
		//}
	}

	VSimpleDrawList drawList(*m_pDevice);

	// calculate absolute transforms for alle SG nodes
	UpdateLocations(&*pRootNode, identity);

	// put nodes into drawlist
	pRootNode->ApplyCulling(&drawList, 0);

	// main loop
	m_pUpdateManager->Start();
	pSystemManager->SetStatus(true);
	pWindow->SetActive();

	while(pSystemManager->GetStatus())
	{
		m_pDevice->BeginScene();
		m_pDevice->SetMatrix(IVDevice::MatrixMode::ViewMatrix, *pCamera->GetMatrix());

		//ApplyMaterial(m_pDevice, &pMesh->GetMaterial());
		//m_pDevice->RenderMesh(pMesh);
		drawList.Render();

        m_pDevice->EndScene();

		m_pUpdateManager->StartNextFrame();
		m_pUpdateManager->GetFrameDuration();

		if (m_pEscapeButton->IsDown() == true)
			pSystemManager->SetStatus(false);

		// input checking
		MoveCamera(pCamera);

		/* das kommt nicht von mir! ;) */
		static vchar strFrameRate[50] = {0};
		sprintf(strFrameRate, "Current Frames Per Second: %d",
			int( 1 / m_pUpdateManager->GetFrameDuration()));
		pWindow->SetTitle(strFrameRate);
	}

	m_pUpdateManager->Stop();

	//exiting...
	return 0;
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------