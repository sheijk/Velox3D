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

#include <V3dLib/Graphics/Geometry.h>
#include <V3dLib/Graphics/Generators.h>
#include <V3dLib/Graphics/Misc.h>

#include <v3d/Math/VMatrixOps.h>

//TODO...
//#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <v3d/Input/IVInputManager.h>
//#include "../../UtilsLib/Importer/VQuake2BspImporter.h"

#include <V3dLib/Graphics/Misc.h>
#include <V3dLib/Graphics/SimpleSG.h>
#include <v3d/Core/MemManager.h>
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



void VExampleApp::QueryButtons(IVInputManager* in_pInputManager)
{
	m_pKeyboardDevice    = &in_pInputManager->GetStandardKeyboard();
	m_pMouseDevice       = &in_pInputManager->GetStandardMouse();

	m_pEscapeButton = &m_pKeyboardDevice->GetKey(KeyEscape);
	m_pUpButton     = &m_pKeyboardDevice->GetKey(KeyUp);
	m_pDownButton   = &m_pKeyboardDevice->GetKey(KeyDown);
	m_pLeftButton   = &m_pKeyboardDevice->GetKey(KeyLeft);
	m_pRightButton  = &m_pKeyboardDevice->GetKey(KeyRight);


	m_pLeftMouseButton	= &m_pMouseDevice->GetButton(1);
	m_pRightMouseButton	= &m_pMouseDevice->GetButton(0);

	m_pMouseXAxis		= &m_pMouseDevice->GetXAxis();
	m_pMouseYAxis		= &m_pMouseDevice->GetYAxis();
}


void VExampleApp::MoveCamera(VCamera* in_pCamera)
{
	const vfloat32 fSeconds = m_pUpdateManager->GetFrameDuration();

	if(m_pUpButton->IsDown() == true)
		in_pCamera->MoveForward(5.0f * fSeconds);

	if(m_pDownButton->IsDown() == true)
		in_pCamera->MoveForward(-5.0f * fSeconds);

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

boost::signals::connection consoleCallbackConn;

void OnConsoleCommand(VStringParam in_strCommand)
{
	if( std::string("exit") == in_strCommand )
	{
		VServicePtr<IVSystemManager>()->SetStatus(false);
	}
	else if( std::string("disconnect") == in_strCommand )
	{
		consoleCallbackConn.disconnect();
	}
		
	vout << "Cmd: \"" << in_strCommand << "\"" << vendl;
}

vint VExampleApp::Main()
{
	V3D_DEBUGMSG("Velox Main app says hi!");

	// get services
	VServicePtr<IVSystemManager> pSystemManager;
	VServicePtr<IVWindowManager> pWindowManager;
	VServicePtr<IVConsoleService> pConsole;

	consoleCallbackConn = pConsole->RegisterCommandListener(&OnConsoleCommand);

	m_pUpdateManager = QueryObject<IVUpdateManager>("updater.service");
	
	IVWindowManager::IVWindowPtr pWindow;
	pWindow = pWindowManager->QueryWindow("app");
	m_pDevice = &(pWindow->QueryGraphicsDevice());

	IVInputManager* pInputManager;
	pInputManager = &(pWindow->QueryInputManager());

	VCamera* pCamera;

	QueryButtons(pInputManager);

	pCamera = new VCamera();
	
	// build scene graph
	VPointer<IVNode>::AutoPtr pRootNode;

	VMatrix44f identity;
	Identity(identity);

	pRootNode.Assign(new VTransformNode(identity));

	// create textured mesh and add it to SG
	//{
	//	VMeshDescription meshDesc = BuildModel(m_pDevice, "/data/test.obj");
	//	VMaterialDescription texMat = BuildTextureMaterial(
	//		m_pDevice, "/data/fuss.jpg");

	//	IVDevice::MeshHandle pMesh = m_pDevice->CreateMesh(meshDesc, texMat);

	//	VMatrix44f transform;
	//	Identity(transform);
	//	// change x value
	//	transform.Set(0, 3, 3);
	//	VTransformNode* pTransformNode = new VTransformNode(transform);
	//	pRootNode->AddChild(pTransformNode);

 //       VMeshNode* pMeshNode = new VMeshNode(pMesh);
	//	pTransformNode->AddChild(pMeshNode);
	//}

	{
		VBoxMesh<ColoredVertex> box(1);
		box.GenerateCoordinates();

		for(int vertnum = 0; vertnum < box.GetVertexBuffer().GetSize(); ++vertnum)
		{
			box.GetVertexBuffer()[vertnum].color = VColor4f(1, 0, 0, 1);
		}		
		
		VMeshDescription md = BuildMeshDescription(
			*m_pDevice,
			box.GetVertexBuffer().GetDataAddress(),
			box.GetVertexBuffer().GetSize()
			);

		IVDevice::MeshHandle hMesh = m_pDevice->CreateMesh(
			md, 
			VMaterialDescription());
		
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

		drawList.Render();

        m_pDevice->EndScene();

		m_pUpdateManager->StartNextFrame();
		m_pUpdateManager->GetFrameDuration();

		if (m_pEscapeButton->IsDown() == true)
			pSystemManager->SetStatus(false);

		// input checking
		MoveCamera(pCamera);

	}

	m_pUpdateManager->Stop();

	//exiting...
	return 404;
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------