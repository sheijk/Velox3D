#include <v3d/Core.h>
#include <v3d/Updater.h>
#include <v3d/System.h>
#include <v3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Window.h>
#include <V3d/Math.h>
#include <V3d/Input.h>
#include <V3d/Resource.h>
#include <V3d/Scene.h>
#include <V3d/Entity.h>

#include <string>

using namespace v3d;
using namespace v3d::updater;
using namespace v3d::system;
using namespace v3d::graphics;
using namespace v3d::window;
using namespace v3d::math;
using namespace v3d::input;
using namespace v3d::resource;
using namespace v3d::scene;
using namespace v3d::entity;

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const std::string APP_NAME = "RacerDemo";

class RacerDemo : public VVeloxApp
{
public:
	RacerDemo();

	virtual vint Main(std::vector<std::string> args);

private:
	IVWindowManager::IVWindowPtr m_pWindow;
	IVDevice* m_pDevice;
	IVButton* m_pEscapeKey;
	VServicePtr<updater::IVUpdateManager> m_pUpdater;
	VServicePtr<system::IVSystemManager> m_pSystem;

	VSharedPtr<VKeyboardCamera> m_pCamera;
	VSharedPtr<IVShooting> m_pRootShooting;

	IVDevice& Device();

	void Init();
	void Shutdown();
	void CreateResources();

	VSharedPtr<VEntity> CreateRoot()
	{
		VSharedPtr<VEntity> pRoot(new VEntity());

		VSharedPtr<VNaiveSceneManagerPart> pSceneManager(new VNaiveSceneManagerPart());
		pRoot->AddPart(pSceneManager);

		VSharedPtr<VSimpleShooting> pShooting(new VSimpleShooting());
		pShooting->SetCamera(m_pCamera.Get());
		pShooting->SetRenderTarget(m_pDevice);
		m_pRootShooting = pShooting;
		pRoot->AddPart(m_pRootShooting);

		return pRoot;
	}

	VSharedPtr<VEntity> CreateWorld()
	{
		VSharedPtr<VEntity> pEntity(new VEntity());
		return pEntity;
	}

	VSharedPtr<VEntity> CreateAmbient()
	{
		VSharedPtr<VEntity> pEntity(new VEntity());
		return pEntity;
	}

	//VSharedPtr<VEntity> CreatePlayer()
	//{
	//	VSharedPtr<VEntity> plr(new VEntity());

	//	plr->AddPart(new VRigidBodyPart());

	//	return plr;
	//}

	VSharedPtr<VEntity> CreateTerrain()
	{
		const static std::string TERRAIN_MAT = "/data/terrainmat";

		static vbool terrainResourcesCreated = false;

		if( ! terrainResourcesCreated )
		{
			VResourceId matres = VResourceManagerPtr()->CreateResource(TERRAIN_MAT.c_str());
			VEffectDescription effect;
			VRenderPass& pass(effect.AddShaderPath().AddRenderPass());
			pass.AddState(TextureState("/data/test2.jpg"));
			pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
			matres->AddData(CopyPtr(effect));
		}

		VSharedPtr<VEntity> pEntity(new VEntity());
		VSharedPtr<VTerrainPart> pTerrain(new VTerrainPart());
		pTerrain->SetMaterial(GetResourceData<IVMaterial>(TERRAIN_MAT.c_str()));
		pEntity->AddPart(pTerrain);
		pEntity->AddPart(SharedPtr(new VRigidBodyPart()));
		return pEntity;
	}

	VSharedPtr<VEntity> CreateSkyBox()
	{
		VSharedPtr<VEntity> pEntity(new VEntity());
		VSharedPtr<VSkyboxPart> pSkyboxPart(new VSkyboxPart());
		pSkyboxPart->SetTextureDir("/data/cubemap/", ".jpg");
		pEntity->AddPart(pSkyboxPart);
		pEntity->AddPart(SharedPtr(new VRigidBodyPart()));
		return pEntity;
	}
};

//-----------------------------------------------------------------------------

/**
 * @author sheijk
 */
vint RacerDemo::Main(std::vector<std::string> args)
{
	Init();
	CreateResources();

	// indenting represents scene graph hierarchy
	VSharedPtr<VEntity> pRoot = CreateRoot();
		VSharedPtr<VEntity> pAmbient = CreateAmbient();
		pRoot->AddChild(pAmbient);
			pAmbient->AddChild(CreateSkyBox());
		VSharedPtr<VEntity> pWorld = CreateWorld();
		pRoot->AddChild(pWorld);
			pWorld->AddChild(CreateTerrain());


	pRoot->Activate();

	m_pUpdater->Start();
	while(m_pSystem->GetStatus())
	{
		Device().BeginScene();

		const vfloat32 frameDuration = vfloat32(m_pUpdater->GetFrameDuration());

		m_pCamera->Move(frameDuration);
		m_pCamera->ApplyTo(Device());

		m_pRootShooting->UpdateAndCull();
		m_pRootShooting->Render();

		Device().EndScene();

		m_pUpdater->StartNextFrame();

		if( m_pEscapeKey->IsDown() )
			m_pSystem->SetStatus(false);
	}
	m_pUpdater->Stop();

	pRoot->Deactivate();
	
	Shutdown();

	return 0;
}

//-----------------------------------------------------------------------------

RacerDemo::RacerDemo()
{
	m_pWindow.Assign(0);
	m_pDevice = 0;
	m_pEscapeKey = 0;
}

void RacerDemo::Init()
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

	m_pCamera.Assign(new VKeyboardCamera(m_pWindow->QueryInputManager()));
}

void RacerDemo::Shutdown()
{
	m_pDevice = 0;
	m_pWindow.Release();
	m_pEscapeKey = 0;
}

void RacerDemo::CreateResources()
{
}

IVDevice& RacerDemo::Device()
{
	V3D_ASSERT(m_pDevice != 0);

	return *m_pDevice;
}

//-----------------------------------------------------------------------------
namespace {
	RacerDemo g_theApp;
}
