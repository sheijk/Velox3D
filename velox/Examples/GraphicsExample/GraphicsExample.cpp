#include <v3d/Core.h>
#include <v3d/Updater.h>
#include <v3d/System.h>
#include <v3d/Graphics.h>
#include <V3d/Window.h>
#include <V3d/Math.h>
#include <V3d/Input.h>
#include <V3d/Resource.h>

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

class GraphicsExample : public VVeloxApp
{
public:
	GraphicsExample();

	virtual vint Main(std::vector<std::string> args);

private:
	IVWindowManager::IVWindowPtr m_pWindow;
	IVDevice* m_pDevice;
	IVButton* m_pEscapeKey;
	VServicePtr<updater::IVUpdateManager> m_pUpdater;
	VServicePtr<system::IVSystemManager> m_pSystem;

	IVDevice& Device();

	void Init();
	void Shutdown();
	void CreateResources();
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const std::string APP_NAME = "GraphicsExample";

//-----------------------------------------------------------------------------

/**
 * @author sheijk
 */
vint GraphicsExample::Main(std::vector<std::string> args)
{
	Init();
	CreateResources();

	vout << "Resource data present after CreateResource()" << vendl;
	VResourceManagerPtr()->DumpResourceInfo();

	IVDevice::MeshHandle hCube = Device().CreateMesh("/cube");
	IVDevice::MaterialHandle hCubeMat = Device().CreateMaterial("/cube");

	vfloat32 angle = 0.0f;

	VCamera cam;
	cam.MoveForward(-7);
	cam.ApplyTo(Device());
	//Device().SetMatrix(IVDevice::ViewMatrix, *cam.GetMatrix());


	m_pUpdater->Start();
	while(m_pSystem->GetStatus())
	{
		Device().BeginScene();

		angle += vfloat32(m_pUpdater->GetFrameDuration()) * 360;
		Device().SetMatrix(IVDevice::ModelMatrix, RotationZMatrix(DegreeToRadian(angle)));

		RenderMesh(Device(), hCube, hCubeMat);

		Device().EndScene();

		m_pUpdater->StartNextFrame();

		if( m_pEscapeKey->IsDown() )
			m_pSystem->SetStatus(false);
	}
	m_pUpdater->Stop();
	
	vout << "Resource data present when terminating program" << vendl;
	VResourceManagerPtr()->DumpResourceInfo();

	Shutdown();

	return 0;
}

//-----------------------------------------------------------------------------

GraphicsExample::GraphicsExample()
{
	m_pWindow.Assign(0);
	m_pDevice = 0;
	m_pEscapeKey = 0;
}

void GraphicsExample::Init()
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

void GraphicsExample::Shutdown()
{
	m_pDevice = 0;
	m_pWindow.Release();
	m_pEscapeKey = 0;
}

void GraphicsExample::CreateResources()
{
    VTriangleMesh<VSimpleVertex> triangleMesh;

	VResourceId res = BuildResource("/triangle", triangleMesh);
	res->AddData(new VEffectDescription(ColorEffect(VColor4f(1, 0, 0, 1))));

	// load and effect description and a mesh from the vfs
	VResourceId cubeRes = VResourceManagerPtr()->CreateResource("/cube");
	VEffectLoader effectLoader;
	effectLoader.LoadEffect("/data/greenmat.xml", cubeRes);

	VModelLoader modelLoader;
	modelLoader.LoadMesh("/data/cubemesh.xml", cubeRes);
}

IVDevice& GraphicsExample::Device()
{
	V3D_ASSERT(m_pDevice != 0);

	return *m_pDevice;
}

//-----------------------------------------------------------------------------
namespace {
	GraphicsExample g_theApp;
}
