#include <v3d/Core.h>
#include <v3d/Updater.h>
#include <v3d/System.h>
#include <v3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Window.h>
#include <V3dLib/Math.h>
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

class %%name%% : public VVeloxApp
{
public:
	%%name%%();

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
const std::string APP_NAME = "%%name%%";

//-----------------------------------------------------------------------------

/**
 * @author sheijk
 */
vint %%name%%::Main(std::vector<std::string> args)
{
	Init();
	CreateResources();

	IVDevice::MeshHandle hTriangle = Device().CreateMesh("/triangle");
	IVDevice::MaterialHandle hTriangleMat = Device().CreateMaterial("/triangle");
	
	vfloat32 angle = 0.0f;

	VCamera cam;
	cam.MoveForward(-7);
	Device().SetMatrix(IVDevice::ViewMatrix, *cam.GetMatrix());

	m_pUpdater->Start();
	while(m_pSystem->GetStatus())
	{
		Device().BeginScene();

		angle += m_pUpdater->GetFrameDuration() * 360;
		Device().SetMatrix(IVDevice::ModelMatrix, RotationZMatrix(DegreeToRadian(angle)));

		RenderMesh(Device(), hTriangle, hTriangleMat);

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

%%name%%::%%name%%()
{
	m_pWindow.Assign(0);
	m_pDevice = 0;
	m_pEscapeKey = 0;
}

void %%name%%::Init()
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

void %%name%%::Shutdown()
{
	m_pDevice = 0;
	m_pWindow.Release();
	m_pEscapeKey = 0;
}

void %%name%%::CreateResources()
{
    VTriangleMesh<VSimpleVertex> triangleMesh;

	VResourceId res = BuildResource("/triangle", triangleMesh);
	res->AddData(new VEffectDescription(ColorEffect(VColor4f(1, 0, 0, 1))));
}

IVDevice& %%name%%::Device()
{
	V3D_ASSERT(m_pDevice != 0);

	return *m_pDevice;
}

//-----------------------------------------------------------------------------
namespace {
	%%name%% g_theApp;
}
