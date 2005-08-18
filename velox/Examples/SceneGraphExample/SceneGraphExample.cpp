#include <v3d/Core.h>
#include <v3d/Updater.h>
#include <v3d/System.h>
#include <v3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Window.h>
#include <V3dLib/Math.h>
#include <V3d/Input.h>
#include <V3d/Resource.h>
#include <V3d/Entity/VEntityManager.h>
#include <V3d/Entity/VEntity.h>
#include <V3dlib/EntityParts/VSceneGraphPart.h>

#include <string>

using namespace v3d;
using namespace v3d::updater;
using namespace v3d::system;
using namespace v3d::graphics;
using namespace v3d::window;
using namespace v3d::math;
using namespace v3d::input;
using namespace v3d::resource;
using namespace v3d::entity;

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------

class VSceneGraphExample : public VVeloxApp
{
public:
	VSceneGraphExample();

	virtual vint Main(std::vector<std::string> args);

private:
	IVWindowManager::IVWindowPtr m_pWindow;
	IVDevice* m_pDevice;
	IVButton* m_pEscapeKey;
	VSceneGraphPart* m_pSGRoot;
	VSharedPtr<VEntity> m_pRoot;
	VServicePtr<updater::IVUpdateManager> m_pUpdater;
	VServicePtr<system::IVSystemManager> m_pSystem;

	IVDevice& Device();

	void Init();
	void Shutdown();
	void CreateResources();
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const std::string APP_NAME = "Entity SceneGraph Example";

//-----------------------------------------------------------------------------

/**
 * Create a Entity with a VSceneGraphPart and a VRigidBodyPart
 */
VSharedPtr<VEntity> CreateEntity(VSceneGraphPart* pSGPart)
{
	VSharedPtr<VEntity> pEntity(new VEntity());

	//create and add RigidBodyPart with Identity Relative Transformation
	pEntity->AddPart("body", static_cast<VSharedPtr<IVPart> >(new VRigidBodyPart()));

	//create and add SceneGraphPart with Identity Relative Transformation
	pEntity->AddPart("sgpa", static_cast<VSharedPtr<IVPart> >(pSGPart));

	return pEntity;
}

vint VSceneGraphExample::Main(std::vector<std::string> args)
{
	Init();
	CreateResources();

	IVDevice::MeshHandle hCube = Device().CreateMesh("/data/cube");
	IVDevice::MaterialHandle hCubeMat = Device().CreateMaterial("/data/cube");

	VCamera cam;
	cam.MoveForward(-7);
	Device().SetMatrix(IVDevice::ViewMatrix, *cam.GetMatrix());

	//create Root Entity
	m_pRoot = CreateEntity(m_pSGRoot);

	//create the Translate for the Child with the SceneGraph Root as Parent
	VSceneGraphPart* pSphere = new VSceneGraphPart();

	//add in SceneGraph Root and the Entity Root the Child pSphere
	m_pRoot->AddChild(CreateEntity(pSphere));
	m_pSGRoot->AddChild(pSphere);

	//create the Translate
	VRBTransform Translate;
	vfloat32 trans = 0.0f;

	m_pUpdater->Start();
	while(m_pSystem->GetStatus())
	{
		Device().BeginScene();

		//set the relative Transformation from the SceneGraph Child
		trans += 0.00025f;
		Translate.SetPosition(VVector3f(trans, trans, 0.0f));		
		pSphere->SetRelativeTransform(Translate);

		//update the SceneGraph Root with his Childs
		m_pSGRoot->Update();

		//set the Mesh Matrix and render the Mesh
		Device().SetMatrix(IVDevice::ModelMatrix, Translate.GetAsMatrix());
		RenderMesh(Device(), hCube, hCubeMat);

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

VSceneGraphExample::VSceneGraphExample()
{
	m_pWindow.Assign(0);
	m_pDevice = 0;
	m_pEscapeKey = 0;
	m_pSGRoot = new VSceneGraphPart();
}

void VSceneGraphExample::Init()
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

void VSceneGraphExample::Shutdown()
{
	m_pDevice = 0;
	m_pWindow.Release();
	m_pEscapeKey = 0;
}

void VSceneGraphExample::CreateResources()
{
	VPolarSphereMesh<VTexturedVertex> cube(50, 50);
	cube.GenerateCoordinates();
	ForEachVertex(cube.GetVertexBuffer(), ScaleVertex<VTexturedVertex>(1.175f, 1.175f, 1.175f));

	VResourceId cubeRes = BuildResource("/data/cube", cube);
	cubeRes->AddData(new VEffectDescription(ColorEffect(VColor4f(0, 1, 0, 1))));
}

IVDevice& VSceneGraphExample::Device()
{
	V3D_ASSERT(m_pDevice != 0);

	return *m_pDevice;
}

//-----------------------------------------------------------------------------
namespace {
	VSceneGraphExample g_theApp;
}