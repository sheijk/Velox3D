#include <v3d/Core.h>
#include <v3d/Updater.h>
#include <v3d/System.h>
#include <v3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Window.h>
#include <V3d/Math.h>
#include <V3d/Input.h>
#include <V3d/Resource.h>
#include <V3d/Entity/VEntityManager.h>
#include <V3d/Entity/VEntity.h>
#include <V3dlib/EntityParts/VSceneGraphPart.h>
#include <V3dlib/EntityParts/VSGAnimationPart.h>
#include <V3dlib/EntityParts/VUpdateablePart.h>

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
 * Create a Entity with a VSceneGraphPart, a VRigidBodyPart 
 * and a VSGAnimationPart
 */
VSharedPtr<VEntity> CreateEntity(VSceneGraphPart* pSGPart, VSGAnimationPart* pSGAnimPart)
{
	VSharedPtr<VEntity> pEntity(new VEntity());

	//create and add RigidBodyPart with Identity Relative Transformation
	pEntity->AddPart(VRigidBodyPart::GetDefaultId(), static_cast<VSharedPtr<IVPart> >(new VRigidBodyPart()));

	//add SGAnimationPart
	pEntity->AddPart(VSGAnimationPart::GetDefaultId(), static_cast<VSharedPtr<IVPart> >(pSGAnimPart));

	//add SceneGraphPart with Identity Relative Transformation
	pEntity->AddPart(VSceneGraphPart::GetDefaultId(), static_cast<VSharedPtr<IVPart> >(pSGPart));

	return pEntity;
}

/**
* Create a Entity with a VSceneGraphPart and a VRigidBodyPart 
*/
VSharedPtr<VEntity> CreateEntity(VSceneGraphPart* pSGPart)
{
	VSharedPtr<VEntity> pEntity(new VEntity());

	//create and add RigidBodyPart with Identity Relative Transformation
	pEntity->AddPart(VRigidBodyPart::GetDefaultId(), static_cast<VSharedPtr<IVPart> >(new VRigidBodyPart()));

	//create and add SceneGraphPart with Identity Relative Transformation
	pEntity->AddPart(VSceneGraphPart::GetDefaultId(), static_cast<VSharedPtr<IVPart> >(pSGPart));

	return pEntity;
}

vint VSceneGraphExample::Main(std::vector<std::string> args)
{
	Init();
	CreateResources();

	VUpdateManagerPart* pUpdate = new VUpdateManagerPart();

	IVDevice::MeshHandle hCube = Device().CreateMesh("/data/cube");
	IVDevice::MaterialHandle hCubeMat = Device().CreateMaterial("/data/cube");
	IVDevice::MeshHandle hMoon = Device().CreateMesh("/data/moon");
	IVDevice::MaterialHandle hMoonMat = Device().CreateMaterial("/data/moon");
	IVDevice::MeshHandle hSun = Device().CreateMesh("/data/sun");
	IVDevice::MaterialHandle hSunMat = Device().CreateMaterial("/data/sun");

	VCamera cam;
	cam.MoveForward(-7);
	cam.ApplyTo(Device());
	//Device().SetMatrix(IVDevice::ViewMatrix, *cam.GetMatrix());

	//create Root Entity
	VSharedPtr<VEntity> m_pRoot = CreateEntity(m_pSGRoot);
	m_pRoot->AddPart(VUpdateManagerPart::GetDefaultId(), static_cast<VSharedPtr<IVPart> >(pUpdate));

	//create a Sun
	VSceneGraphPart* pSun = new VSceneGraphPart();
	VSGAnimationPart* pSunAnim = new VSGAnimationPart();

	//create a Planet for the Child
	VSceneGraphPart* pPlanet = new VSceneGraphPart();
	VSGAnimationPart* pPlanetAnim = new VSGAnimationPart();

	//create a Moon for the Sphere as a Child
	VSceneGraphPart* pMoon = new VSceneGraphPart();
	VSGAnimationPart* pMoonAnim = new VSGAnimationPart();

	//add the Sun in a Entity
	VSharedPtr<VEntity> pSunEntity = CreateEntity(pSun, pSunAnim);

	//add the Planet in a Entity
	VSharedPtr<VEntity> pPlanetEntity = CreateEntity(pPlanet, pPlanetAnim);

	//add the Moon in a Entity
	VSharedPtr<VEntity> pMoonEntity = CreateEntity(pMoon, pMoonAnim);
	
	pSunEntity->AddChild(pPlanetEntity);
	pPlanetEntity->AddChild(pMoonEntity);
	m_pRoot->AddChild(pSunEntity);
	m_pRoot->Activate();
	// ensure the activation was successful
	V3D_ASSERT(m_pRoot->IsActive());

	vfloat32 trans = 1.0f;
	vfloat32 time = 0.0f;

	m_pUpdater->Start();
	while(m_pSystem->GetStatus())
	{
		Device().BeginScene();

		time += m_pUpdater->GetFrameDuration();

		//set the relative Transformation from the SceneGraph Sphere Child
		trans = sin(time/10);
		pPlanetAnim->SetPosition(VVector3f(trans, trans, 0.0f));		

		//set the relative Transformation from the Sphere Child Moon
		pMoonAnim->SetPosition(VVector3f(-trans, -trans, 0.0f));

		//update the SceneGraph Root with his Childs
		pUpdate->Update(time);
		m_pSGRoot->Update();

		//set the Mesh Matrix and render the Mesh
		Device().SetMatrix(IVDevice::ModelMatrix, pMoonAnim->GetRelativeTransform().AsMatrix());
		RenderMesh(Device(), hMoon, hMoonMat);	

		Device().SetMatrix(IVDevice::ModelMatrix, pPlanetAnim->GetRelativeTransform().AsMatrix());
		RenderMesh(Device(), hCube, hCubeMat);

		Device().SetMatrix(IVDevice::ModelMatrix, pSunAnim->GetRelativeTransform().AsMatrix());
		RenderMesh(Device(), hSun, hSunMat);

		Device().EndScene();

		m_pUpdater->StartNextFrame();

		if( m_pEscapeKey->IsDown() )
			m_pSystem->SetStatus(false);
	}
	m_pUpdater->Stop();

	m_pRoot->Deactivate();
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
	VPolarSphereMesh<VTexturedVertex> cube(20, 20);
	cube.GenerateCoordinates();
	ForEachVertex(cube.GetVertexBuffer(), ScaleVertex<VTexturedVertex>(0.5f, 0.5f, 0.5f));

	VResourceId cubeRes = BuildResource("/data/cube", cube);
	cubeRes->AddData(new VEffectDescription(ColorEffect(VColor4f(0, 1, 0, 1))));

	VPolarSphereMesh<VTexturedVertex> moon(10, 10);
	moon.GenerateCoordinates();
	ForEachVertex(moon.GetVertexBuffer(), ScaleVertex<VTexturedVertex>(0.175f, 0.175f, 0.175f));

	VResourceId moonRes = BuildResource("/data/moon", moon);
	moonRes->AddData(new VEffectDescription(ColorEffect(VColor4f(1, 0, 0, 1))));

	VPolarSphereMesh<VTexturedVertex> sun(25, 25);
	sun.GenerateCoordinates();
	ForEachVertex(sun.GetVertexBuffer(), ScaleVertex<VTexturedVertex>(0.7f, 0.7f, 0.7f));

	VResourceId sunRes = BuildResource("/data/sun", sun);
	sunRes->AddData(new VEffectDescription(ColorEffect(VColor4f(0, 1, 1, 1))));
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