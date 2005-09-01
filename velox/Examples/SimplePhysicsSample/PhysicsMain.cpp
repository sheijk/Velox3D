#include <vector>
#include <string>

#include <V3d/Core.h>
#include <V3d/Vfs.h>
#include <v3d/Window.h>
#include <V3d/Updater.h>
#include <V3d/System.h>
#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3dLib/Math.h>
#include <V3d/Input.h>
#include <V3d/Image.h>
#include <V3d/Entity.h>

#include "VPhysicManagerPart.h"
#include <V3d/Resource/VResourceDataPtr.h>
#include <V3dLib/Physics.h>
#include <V3d/Scene.h>

using namespace v3d;
using namespace window;
using namespace updater;
using namespace system;
using namespace graphics;
using namespace math;
using namespace input;
using namespace vfs;
using namespace image;
using namespace entity;
using namespace utils;
using namespace physics;

using namespace std;

//#include "PhysicsUtils.h"


#define BOXWIDTH 40
#define PLANE_DISTANCE 50.0f
#define PLANE_DISTANCE2 150.0f
#define VIS_FAC 300.0f
#define MAX_SPHERES 100

//VRigidBodyPart* g_BodyPart[MAX_SPHERES + 6];
//VPhysicBody* pBody[MAX_SPHERES];


class VSimplePhysic : public VVeloxApp
{
public:
	VSimplePhysic();
	virtual ~VSimplePhysic();

	virtual vint Main(vector<string> args);

private:
	
	IVDevice& GetDevice() { return *m_pDevice; }

	/*IVEntityManager::EntityPtr CreateSphereBodyEntity(VVector<vfloat32, 3> in_Position);
	IVEntityManager::EntityPtr CreateBoxBodyEntity(VVector<vfloat32, 3> in_Position);*/

	//void CreateMeshes();

	void InitializeResources();

	/*IVDevice::MeshHandle m_hSphereMesh;
	IVDevice::BufferHandle m_hSphereTexture;
	IVDevice::BufferHandle m_hPlaneTexture;
	IVDevice::MeshHandle m_hBoxMesh;
	IVDevice::MeshHandle m_PlaneMesh;
	IVDevice::MeshHandle m_PlaneMesh2;
	IVDevice::MeshHandle m_PlaneMesh3;
	IVDevice::MeshHandle m_PlaneMesh4;
	IVDevice::MeshHandle m_PlaneMesh5;
	IVDevice::MeshHandle m_PlaneMesh6;

	VGraphicsManager m_GraphicsManager;*/
	IVDevice* m_pDevice;
	
};

//-----------------------------------------------------------------------------
VSimplePhysic::VSimplePhysic()
{
	/*m_hSphereMesh = 0;
	m_hSphereTexture = 0;
	m_pDevice = 0;*/
}

VSimplePhysic::~VSimplePhysic()
{
	m_pDevice = 0;
}

void VSimplePhysic::InitializeResources()
{
	resource::VResourceId modelResourceId =
		resource::VResourceManagerPtr()->CreateResource("/model3ds");

	modelResourceId->AddData(new resource::VFileName("/data/afighter.3ds"));
}

vint VSimplePhysic::Main(vector<string> args)
{
	InitializeResources();
	
	// create window
	VWindowManagerPtr pWindowManager;
	IVWindowManager::WindowPtr pWindow = pWindowManager->QueryWindow(
		"Simple Physics Sample -press ENTER to disable gravity, SPACE to enable",
		&VDisplaySettings(VSize(800, 600), VPosition(200, 50))
		);

	IVDevice& device(pWindow->QueryGraphicsDevice());
	m_pDevice = &device;
	IVInputManager& input(pWindow->QueryInputManager());

	scene::VDefaultRenderAlgorithm* pDefaultRenderAlgorithm = new scene::VDefaultRenderAlgorithm();

	entity::VEntity myRootEntity;
	scene::VSimpleScene* pSimpleScene = new scene::VSimpleScene();
	scene::VShooting* pShooting = new scene::VShooting(m_pDevice, pDefaultRenderAlgorithm );
	VPhysicManagerPart* pPhysicsManager = new VPhysicManagerPart();
    
	myRootEntity.AddPart(scene::VShooting::GetDefaultId(), SharedPtr(pShooting));	
	myRootEntity.AddPart(scene::VSimpleScene::GetDefaultId(), SharedPtr(pSimpleScene));
	myRootEntity.AddPart(VPhysicManagerPart::GetDefaultId(), SharedPtr(pPhysicsManager));
	myRootEntity.Activate();

	pPhysicsManager->GetPhysicWorld().GetSpace()->SetSurfaceBounce(0.85f);
	pPhysicsManager->GetPhysicWorld().SetGravity(0,0,3.0f);
	
	VPhysicBody* pPhysicBody;
	VPhysicBoxMassState massState;
	massState.SetMass(0.3f);
	
	pPhysicBody = pPhysicsManager->GetPhysicWorld().CreateBody();
	pPhysicBody->AddState(&massState); 
	pPhysicBody->Create(&pPhysicsManager->GetPhysicWorld());

	entity::VEntity* pObjectEntity = new entity::VEntity();
	VRigidBodyPart* pBodyPart = new VRigidBodyPart;
	
	pObjectEntity->AddPart(VRigidBodyPart::GetDefaultId(), SharedPtr(pBodyPart));
	pObjectEntity->AddPart(VPhysicBody::GetDefaultId(), SharedPtr(pPhysicBody));
	
	myRootEntity.AddChild(SharedPtr(pObjectEntity));
	pObjectEntity->Activate();

	scene::VSceneModelPart* pSceneModel  = new scene::VSceneModelPart(
		*resource::GetResourceData<VModel>("/model3ds"));

	// setup sub systems (for entities)
	//VSimpleDrawList drawList(device);
	//m_GraphicsManager.SetDrawList(drawList);
	//VEntityUpdater<VUpdateablePart> m_PartUpdater;

	//CreateMeshes();
	
	/*m_GraphicsManager.GetDrawList().Add(VModel(m_PlaneMesh));
	m_GraphicsManager.GetDrawList().Add(VModel(m_PlaneMesh2));
	m_GraphicsManager.GetDrawList().Add(VModel(m_PlaneMesh3));
	m_GraphicsManager.GetDrawList().Add(VModel(m_PlaneMesh4));
	m_GraphicsManager.GetDrawList().Add(VModel(m_PlaneMesh5));
	m_GraphicsManager.GetDrawList().Add(VModel(m_PlaneMesh6));*/

	// setup camera
	//VKeyboardCamera cam(input);
	//cam.SetMovementSpeed(1);
	//cam.GetCamera().Move(0, 0, 0.0f);
	//cam.GetCamera().RotateY(90);
	//cam.GetCamera().RotateZ(90);
	//cam.GetCamera().Move(-100, 0, 0.0f);


	//VEntity::PartPtr pCameraPosPart(new VCameraPosPart(cam.GetCamera(), &m_PartUpdater));
	//VEntityManagerPtr pEntityManager;

	/* physics code goes here */
//	VPhysicGeometryPlane ground[6];

//	VPhysicWorld world;
		
	//VPhysicGeometryBox box;
	//VPhysicBoxMassState boxMass;
	//VPhysicGeometrySphere sphere[MAX_SPHERES];
	//VPhysicSphereMassState sphereMass[MAX_SPHERES];
	//		
	//VEntity::PartPtr* pBodyPart[MAX_SPHERES];

	//world.GetSpace()->SetSurfaceMu(dInfinity);
	//world.GetSpace()->SetSurfaceMu2(dInfinity);
	//world.GetSpace()->SetSurfaceBounce(0.85f);
	//
	//world.SetGravity(0,0,3.0);

	//ground[0].SetPlane(graphics::VVertex3f(0,0,-1), -PLANE_DISTANCE);
	//ground[0].CreatePlane(world.GetSpace());

	//ground[1].SetPlane(graphics::VVertex3f(0,-1,0), -PLANE_DISTANCE);
	//ground[1].CreatePlane(world.GetSpace());
	//
	//ground[2].SetPlane(graphics::VVertex3f(-1,0,0), -PLANE_DISTANCE);
	//ground[2].CreatePlane(world.GetSpace());

	//ground[3].SetPlane(graphics::VVertex3f(0,0,1), -PLANE_DISTANCE2);
	//ground[3].CreatePlane(world.GetSpace());

	//ground[4].SetPlane(graphics::VVertex3f(0,1,0), -PLANE_DISTANCE2);
	//ground[4].CreatePlane(world.GetSpace());

	//ground[5].SetPlane(graphics::VVertex3f(1,0,0), -PLANE_DISTANCE2);
	//ground[5].CreatePlane(world.GetSpace());

	//// add some balls
	//for(vint i = 1; i < MAX_SPHERES; ++i)
	//{
	//	sphere[i].SetSphereRadius(1.3f);
	//	sphere[i].CreateSphere(world.GetSpace());
	//	sphereMass[i].SetMass(0.2f);

	//	pBody[i] = world.CreateBody();
	//	pBodyPart[i] = world.GetBodyPart(pBody[i]);
	//									
	//	VVector<vfloat32, 3> pos;

 //		if(i % 2)
	//	{
	//		pos.Set(0, i*5.4f);
	//		pos.Set(1, i*.95);
	//	}
	//	else
	//	{
	//		pos.Set(0, -i*7.23f);
	//		pos.Set(1, -i*.85);
	//	}
	//		
	//	pos.Set(2, -i*1.5f);
	//	
	//	IVEntityManager::EntityPtr pBallEntity = CreateSphereBodyEntity(pos);

	//	pBallEntity->AddPart(VFourCC("phys"),*pBodyPart[i]);
	//	pBallEntity->Activate();
	//	pEntityManager->Add(pBallEntity);

	//	pBody[i]->AddState(&sphereMass[i]);
	//	pBody[i]->SetPosition(pos.Get(0), pos.Get(1), pos.Get(2));
	//	
	//	pBody[i]->SetCollisionBody(&sphere[i]);
	//	//sphere[i].SetCategoryGroup(VPhysicGeometry::Group::Group2);
	//	//sphere[i].SetCollisionGroup(VPhysicGeometry::Group::Group1);
	//	
	//}
	//
	//boxMass.SetMass(12.0f);
	//box.SetWidth(BOXWIDTH);
	//box.SetLength(BOXWIDTH);
	//box.SetHeight(BOXWIDTH);
	//box.CreateBox(world.GetSpace());
	//
	//pBody[0] = world.CreateBody();
	//pBodyPart[0] = world.GetBodyPart(pBody[0]);
	//
	//VVector<vfloat32, 3> xpos;
	//xpos.Set(0, 0);
	//xpos.Set(1, 0);
	//xpos.Set(2, 0.0f);

	//IVEntityManager::EntityPtr pBoxEntity = CreateBoxBodyEntity(xpos);
	//
	//pBoxEntity->AddPart(VFourCC("phys"),*pBodyPart[0]);
	//pBoxEntity->Activate();
	//pEntityManager->Add(pBoxEntity);

	//pBody[0]->AddState(&boxMass);
	//pBody[0]->SetPosition(xpos.Get(0), xpos.Get(1), xpos.Get(2));
	//pBody[0]->SetCollisionBody(&box);
	//
	///*physics code end here*/

	VUpdateManagerPtr pUpdater;
	VSystemManagerPtr pSystem;

	pSystem->SetStatus(true);
	pUpdater->Start();

	input::IVButton* pEscapeButton;
	input::IVButton* pEnterButton;
	input::IVButton* pSpace;

	input::IVButton* pUp;
	input::IVButton* pDown;
	input::IVButton* pLeft;
	input::IVButton* pRight;

    pEscapeButton	= &input.GetStandardKey(KeyEscape);
	pEnterButton	= &input.GetStandardKey(KeyReturn);
	pSpace			= &input.GetStandardKey(KeySpace);
	pUp				= &input.GetStandardKey(KeyA);
	pDown			= &input.GetStandardKey(KeyS);
	pLeft			= &input.GetStandardKey(KeyN);
	pRight			= &input.GetStandardKey(KeyM);
	

	while(pSystem->GetStatus())
	{
		if(pEscapeButton->IsDown() == true)
		{
			pSystem->SetStatus(false);
		}

		if(pEnterButton->IsDown() == true)
			pPhysicsManager->GetPhysicWorld().SetGravity(0,0,0);

		if(pSpace->IsDown() == true)
			pPhysicsManager->GetPhysicWorld().SetGravity(0,0,3.0);
		
	//	m_GraphicsManager.UpdateAll();



		//device.SetMatrix(IVDevice::ViewMatrix, cam.GetTransform());
		device.BeginScene();

		/*resource::VResourceId pModelResourceId = resource::VResourceManagerPtr()->GetResourceByName("/model3ds");

		for(vuint i = 0; i < pModelResourceId->GetData<VModel>()->GetPartCount(); i++)
		{
			for(vuint matid = 0; matid < pModelResourceId->GetData<VModel>()->GetPart(i).GetMaterial()->PassCount(); ++matid)
			{
				const IVPass* pPass = & pModelResourceId->GetData<VModel>()->GetPart(i).GetMaterial()->GetPass(matid);

				ApplyMaterial(device, pPass);
				device.RenderMesh(&(*(pModelResourceId->GetData<VModel>()->GetPart(i).GetMesh())));
			}
		}*/

		device.EndScene();
		pPhysicsManager->Update();
	//	drawList.Render();
		device.EndScene();
		pUpdater->StartNextFrame();
		//cam.Move(vfloat32(pUpdater->GetFrameDuration()) * 10);
	}

	pUpdater->Stop();

	//clean things up
	/*for(uint8 i=1; i < MAX_SPHERES; ++i)
		sphere[i].Destroy();
	
	for(uint8 i = 0; i<6; ++i)
		ground[i].Destroy();

	
	box.Destroy();
	world.Destroy();*/

	return 0;
}

//void VSimplePhysic::CreateMeshes()
//{
	//V3D_ASSERT(m_pDevice != 0);
	//V3D_ASSERT(m_hSphereMesh == 0);
	//V3D_ASSERT(m_hSphereTexture == 0);

	//VBoxMesh<VTexturedVertex> box(BOXWIDTH);
	//box.GenerateCoordinates();
	//box.GenerateTexCoords();

	//VPolarSphereMesh<VTexturedVertex> sphere(10, 10);
	//sphere.GenerateCoordinates();
	//sphere.GenerateTexCoords();

	//VPlaneMesh<VTexturedVertex> plane(0.0f,0.0f,1.0f,-PLANE_DISTANCE, VIS_FAC);
	//plane.GenerateCoordinates();
	//plane.GenerateTexCoords();

	//VPlaneMesh<VTexturedVertex> plane2(0.0f,1.0f,0.0f,-PLANE_DISTANCE, VIS_FAC);
	//plane2.GenerateCoordinates();
	//plane2.GenerateTexCoords();

	//VPlaneMesh<VTexturedVertex> plane3(1.0f,0.0f,0.0f,-PLANE_DISTANCE, VIS_FAC);
	//plane3.GenerateCoordinates();
	//plane3.GenerateTexCoords();

	//
	//VPlaneMesh<VTexturedVertex> plane4(0.0f,0.0f,-1.0f,-PLANE_DISTANCE2, VIS_FAC);
	//plane4.GenerateCoordinates();
	//plane4.GenerateTexCoords();

	//VPlaneMesh<VTexturedVertex> plane5(0.0f,-1.0f,0.0f,-PLANE_DISTANCE2, VIS_FAC);
	//plane5.GenerateCoordinates();
	//plane5.GenerateTexCoords();

	//VPlaneMesh<VTexturedVertex> plane6(-1.0f,0.0f,0.0f,-PLANE_DISTANCE2, VIS_FAC);
	//plane6.GenerateCoordinates();
	//plane6.GenerateTexCoords();

	//VEffectDescription planeSurface;
	//VEffectDescription sphereSurface;
	//VRenderPass& pass(sphereSurface.AddShaderPath().AddRenderPass());
	//VRenderPass& pass2(planeSurface.AddShaderPath().AddRenderPass());
	//
	//// load texture
	//VImage ballTex(64, 64, 24);
	//VImageServicePtr()->CreateImage("/data/ball.tga", ballTex);
	//m_hSphereTexture = m_pDevice->CreateBuffer(IVDevice::Texture, &ballTex.GetData());

 //   pass.AddState(TextureState(
	//	m_hSphereTexture, 
	//	ballTex.GetWidth(), ballTex.GetHeight(),
	//	FilterLinear, FilterLinear,
	//	TextureRepeat, TextureRepeat));

	//pass.AddState(DefaultColorState(1, 1, 1, 1));

	//// load texture
	//VImage planeTex(256, 256, 24);
	//VImageServicePtr()->CreateImage("/data/detail.jpg", planeTex);
	//m_hPlaneTexture = m_pDevice->CreateBuffer(IVDevice::Texture, &planeTex.GetData());

	//pass2.AddState(TextureState(
	//	m_hPlaneTexture,
	//	planeTex.GetWidth(),
	//	planeTex.GetHeight(),
	//	FilterLinear,
	//	FilterLinear,
 //       TextureRepeat,
	//	TextureRepeat
	//	));
 //   	
	//pass2.AddState(DefaultColorState(1,1,1,1));

	//m_hSphereMesh = BuildMesh(*m_pDevice, sphere, sphereSurface);
	//m_hBoxMesh	= BuildMesh(*m_pDevice, box, sphereSurface);
	//
	//m_PlaneMesh = BuildMesh(*m_pDevice, plane, planeSurface);
	//m_PlaneMesh2 = BuildMesh(*m_pDevice, plane2, planeSurface);
	//m_PlaneMesh3 = BuildMesh(*m_pDevice, plane3, planeSurface);
	//m_PlaneMesh4 = BuildMesh(*m_pDevice, plane4, planeSurface);
	//m_PlaneMesh5 = BuildMesh(*m_pDevice, plane5, planeSurface);
	//m_PlaneMesh6 = BuildMesh(*m_pDevice, plane6, planeSurface);
	
//}

//IVEntityManager::EntityPtr VSimplePhysic::CreateSphereBodyEntity(
//	VVector<vfloat32, 3> in_Position)
//{
//	IVEntityManager::EntityPtr pBallEntity(new VEntity());
//
//	VMeshPart* pMeshPart = new VMeshPart(&m_GraphicsManager);
//	pMeshPart->AddMesh(m_hSphereMesh);
//
//	pBallEntity->AddPart(VFourCC("mesh"), VEntity::PartPtr(pMeshPart));
//
//	VRigidBodyPart* pRigidBodyPart = new VRigidBodyPart();
//
//	static int i = 0;
//	g_BodyPart[i] = pRigidBodyPart;
//	i++;
//
//	pRigidBodyPart->SetPosition(in_Position);
//	pBallEntity->AddPart(VFourCC("body"), VEntity::PartPtr(pRigidBodyPart));
//
//	return pBallEntity;
//}
//
//IVEntityManager::EntityPtr VSimplePhysic::CreateBoxBodyEntity(
//	VVector<vfloat32, 3> in_Position)
//{
//	IVEntityManager::EntityPtr pBoxEntity(new VEntity());
//
//	VMeshPart* pMeshPart = new VMeshPart(&m_GraphicsManager);
//	pMeshPart->AddMesh(m_hBoxMesh);
//
//	pBoxEntity->AddPart(VFourCC("mesh"), VEntity::PartPtr(pMeshPart));
//
//	VRigidBodyPart* pRigidBodyPart = new VRigidBodyPart();
//
//	//TODO: FIXME
//	g_BodyPart[3] = pRigidBodyPart;
//	
//
//	pRigidBodyPart->SetPosition(in_Position);
//	pBoxEntity->AddPart(VFourCC("body"), VEntity::PartPtr(pRigidBodyPart));
//
//	return pBoxEntity;
//}

namespace {
	VSimplePhysic g_RacerApp;
}