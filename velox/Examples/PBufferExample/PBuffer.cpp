#include <v3d/Core.h>
#include <v3d/Updater.h>
#include <v3d/System.h>
#include <v3d/Graphics.h>
#include <V3d/Window.h>
#include <V3d/Math.h>
#include <V3d/Input.h>
#include <V3d/Resource.h>
//#include "../../Source/Graphics/OpenGL/Context/VPBufferWindowContext.h"
//#include "../../Source/Graphics/OpenGL/VOpenGLDevice.h"
#include "../../Source/Graphics/OpenGL/VPBufferTexture.h"

#include <string>

using namespace v3d;
using namespace v3d::updater;
using namespace v3d::system;
using namespace v3d::graphics;
using namespace v3d::window;
using namespace v3d::math;
using namespace v3d::input;
using namespace v3d::resource;

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------

class VPBufferExample : public VVeloxApp
{
public:
	VPBufferExample();

	virtual vint Main(std::vector<std::string> args);

private:
	IVWindowManager::IVWindowPtr m_pWindow;
	IVDevice* m_pDevice;
	IVDevice* m_pPBufferDevice;
	IVButton* m_pEscapeKey;
	IVTexture* m_pTexState;
	VServicePtr<updater::IVUpdateManager> m_pUpdater;
	VServicePtr<system::IVSystemManager> m_pSystem;

	IVDevice& Device();
	IVInputManager& GetInputManager();
	IVKeyboardDevice& GetKeyboard();
	IVMouseDevice& GetMouse();

	void Init();
	void Shutdown();
	void CreateResources();
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const std::string APP_NAME = "PBuffer Example";

//-----------------------------------------------------------------------------

void DrawScene(IVDevice& device)
{
	static IVDevice::MeshHandle hTriangle = device.CreateMesh("/data/cube");
	static IVDevice::MaterialHandle hTriangleMat = device.CreateMaterial("/data/cube");

	RenderMesh(device, hTriangle, hTriangleMat);
}

vint VPBufferExample::Main(std::vector<std::string> args)
{
	Init();
	CreateResources();

	IVDevice::MeshHandle hPlane = &*GetResourceData<IVMesh>("/data/plane");
	IVDevice::MaterialHandle hPlaneMat = &*GetResourceData<IVMaterial>("/data/plane");

	vfloat32 angle = 0.0f;

	//VCamera cam;
	VKeyboardCamera cam(GetInputManager());
	cam.GetCamera().MoveForward(-7);
	cam.ApplyTo(Device());
	cam.SetIgnoreMouse(true);

	cam.ApplyTo(*m_pPBufferDevice);

	m_pPBufferDevice->SetClearColor(1, 0, 0, 1);

	m_pUpdater->Start();
	while(m_pSystem->GetStatus())
	{
		cam.Move(m_pUpdater->GetFrameDuration());
		cam.ApplyTo(Device());

		// render something to the texture
		m_pPBufferDevice->BeginScene();
		DrawScene(Device());
		m_pPBufferDevice->EndScene();

		// use the generated texture for the plane
		Device().BeginScene();
		//ApplyMaterial(Device(), &hPlaneMat->GetPass(0));
		glColor3f(1, 1, 1);
		m_pTexState->Bind();
		Device().RenderMesh(hPlane);
		m_pTexState->Unbind();	
		Device().EndScene();

		m_pUpdater->StartNextFrame();

		if( m_pEscapeKey->IsDown() )
			m_pSystem->SetStatus(false);
	}
	m_pUpdater->Stop();

	Shutdown();

	return 0;
}

//-----------------------------------------------------------------------------

VPBufferExample::VPBufferExample()
{
	m_pWindow.Assign(0);
	m_pDevice = 0;
	m_pEscapeKey = 0;
	m_pPBufferDevice = 0;
}

void VPBufferExample::Init()
{
	// create window
	VServicePtr<window::IVWindowManager> pWindowManager;

	VDisplaySettings displaySettings;
	displaySettings.SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_pWindow =	pWindowManager->QueryWindow(
		APP_NAME.c_str(), &displaySettings);

	m_pDevice = &m_pWindow->QueryGraphicsDevice();

	// get the escape key
	m_pEscapeKey = &m_pWindow->QueryInputManager().GetStandardKey(KeyEscape);

	// init system and updater service
	m_pSystem->SetStatus(true);
}

void VPBufferExample::Shutdown()
{
	m_pDevice = 0;
	m_pWindow.Release();
	m_pEscapeKey = 0;
}

void VPBufferExample::CreateResources()
{
	VDisplaySettings displaySettings;
	displaySettings.SetSize(512, 512);
	displaySettings.SetBitsPerPixel(32);
	displaySettings.SetDepthBits(16);

	VResourceId contextRes = VResourceManagerPtr()->CreateResource("/context");
	contextRes->AddData(Device().CreateOffscreenContext(&displaySettings));

	VPolarSphereMesh<VTexturedVertex> cube(100, 100);
	cube.GenerateCoordinates();
	cube.GenerateTexCoords();
	ForEachVertex(cube.GetVertexBuffer(), ScaleVertex<VTexturedVertex>(1.175f, 1.175f, 1.175f));

	VResourceId cubeRes = BuildResource("/data/cube", cube);
	cubeRes->AddData(new VEffectDescription(ColorEffect(VColor4f(0, 1, 0, 1))));

	m_pPBufferDevice = const_cast<IVDevice*>(&*contextRes->GetData<IVDevice>());
	m_pTexState = const_cast<VPBufferTexture*>(&*contextRes->GetData<VPBufferTexture>());
	//m_pTexState = const_cast<IVTexture*>(&*GetResourceData<IVTexture>("/data/day.jpg"));

	V3D_ASSERT(m_pPBufferDevice != 0);

	VPlaneMesh<VTexturedVertex> plane(0, 1, 0, 1, 2);
	plane.GenerateCoordinates();
	plane.GenerateTexCoords();
	VResourceId planeRes = BuildResource("/data/plane", plane);
	//planeRes->AddData(new VEffectDescription(ColorEffect(VColor4f(1, 1, 1, 1))));
	VEffectDescription effect = ColorEffect(VColor4f(1, 1, 1, 1));
	//effect.ShaderPath(0).RenderPass(0).AddState(TextureState("/data/tgatest.tga"));
	effect.ShaderPath(0).RenderPass(0).AddState(TextureState(contextRes->GetQualifiedName().c_str()));
	planeRes->AddData(CopyPtr(effect));

	/*VEffectDescription textureEffect;
	MakeDefaultMaterial(textureEffect.AddShaderPath().AddRenderPass());
	textureEffect.ShaderPath(0).RenderPass(0).AddState(
		TextureState(contextRes->GetQualifiedName().c_str()));
	planeRes->AddData(new VEffectDescription(textureEffect));*/
}

IVDevice& VPBufferExample::Device()
{
	V3D_ASSERT(m_pDevice != 0);

	return *m_pDevice;
}

IVInputManager& VPBufferExample::GetInputManager()
{
	return m_pWindow->QueryInputManager();
}

IVKeyboardDevice& VPBufferExample::GetKeyboard()
{
	return GetInputManager().GetStandardKeyboard();
}

IVMouseDevice& VPBufferExample::GetMouse()
{
	return GetInputManager().GetStandardMouse();
}

//-----------------------------------------------------------------------------
namespace {
	VPBufferExample g_theApp;
}