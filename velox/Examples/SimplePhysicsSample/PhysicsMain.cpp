#include <vector>
#include <string>

#include <V3d/Core.h>
#include <V3d/Vfs.h>
#include <v3d/Window.h>
#include <V3d/Updater.h>
#include <V3d/System.h>
#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Math.h>
#include <V3d/Input.h>
#include <V3d/Image.h>
#include <V3d/Entity.h>

#include <v3dLib/Physics/VPhysicManagerPart.h>
#include <V3d/Resource/VResourceDataPtr.h>
#include <V3dLib/Physics.h>
#include <V3d/Scene.h>
#include <V3d/Graphics/VModel.h>

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
using namespace resource;
using namespace std;

class VSimplePhysic : public VVeloxApp
{
public:
	VSimplePhysic();
	virtual ~VSimplePhysic();

	virtual vint Main(vector<string> args);

private:

	void CreateSphereResource(VStringParam in_sName, vfloat32 in_fScale);
	
	void CreateTextureEffect(VStringParam in_sTextureFileName,
							 VStringParam in_sEffectResourceName,
							 VStringParam in_sResourceName
							 );
	void CreatePlaneResource(
		VStringParam in_sResourceName,
		VVector3f in_Normal,
		vfloat32 in_fDistance,
		vfloat32 in_fVisFactor);

	void CreateBoxResource(VStringParam in_sResourceName, vfloat32 in_fWidth);
	void CreateBoxResource(VStringParam in_sResourceName, VVector3f	in_Expansion);
	
	void InitializeResources();

	VEffectDescription CreateTextureEffectDescription(VStringParam in_sResourceName);

	void CreateSpherePhysicObject(
		vfloat32 in_fMasss,
		vfloat32 in_fRadius,
		entity::VEntity* in_pParentEntity,
		VPhysicManagerPart* in_pPhysicManager,
		std::string in_sResourceName);

	void CreatePlanePhysicObject(
		VVector3f in_Normal,
		vfloat32 in_fDistance,
		entity::VEntity* in_pParentEntity,
		VPhysicManagerPart* in_pPhysicManager,
		std::string in_sResourceName);

	void CreateBoxPhysicObject(
		vfloat32 in_fMasss,
		VVector3f in_Expansion,
		entity::VEntity* in_pParentEntity,
		VPhysicManagerPart* in_pPhysicManager,
		std::string in_sResourceName);

	IVDevice& GetDevice() { return *m_pDevice; }
	
	IVDevice* m_pDevice;
	VPhysicWorld* m_pWorld;
};

//-----------------------------------------------------------------------------
VSimplePhysic::VSimplePhysic()
{
}

VSimplePhysic::~VSimplePhysic()
{
	m_pDevice = 0;
}


void VSimplePhysic::CreateSphereResource(VStringParam in_sName, vfloat32 in_fScale = 1.0f)
{
	VResourceManagerPtr pResManager;

	VPolarSphereMesh<VTexturedVertex> sphere(10,10);
	sphere.GenerateCoordinates();
	sphere.GenerateTexCoords();
	ForEachVertex(sphere.GetVertexBuffer(), 
		ScaleVertex<VTexturedVertex>(in_fScale, in_fScale, in_fScale));
	
	VResourceId sphereResourceId = pResManager->CreateResource(in_sName);
	VResourceId sphereRes = BuildResource(in_sName, sphere);
}

void VSimplePhysic::CreateTextureEffect(VStringParam in_sTextureFileName,
										VStringParam in_sEffectResourceName,
										VStringParam in_sResourceName)
{
	resource::VResourceManagerPtr pResManager;
		
	try
	{
		VResourceId res = pResManager->GetResourceByName(in_sEffectResourceName);
	}

	catch(v3d::resource::VResourceNotFoundException)
	{
		VResourceId res = pResManager->CreateResource(in_sEffectResourceName);
		res->AddData(new VFileName(in_sTextureFileName));
	}

	VResourceId res = pResManager->GetResourceByName(in_sResourceName);

	res->AddData(new VEffectDescription(CreateTextureEffectDescription(in_sEffectResourceName)));
}

void VSimplePhysic::CreatePlaneResource(VStringParam in_sResourceName,
										VVector3f in_Normal,
										vfloat32 in_fDistance,
										vfloat32 in_fVisFactor = 300.0f)
{
	VPlaneMesh<VTexturedVertex> plane(
		in_Normal[0],
		in_Normal[1],
		in_Normal[2],
		in_fDistance,
		in_fVisFactor
		);
	plane.GenerateCoordinates();
	plane.GenerateTexCoords();

	VResourceId res = BuildResource(in_sResourceName, plane);
}

void VSimplePhysic::CreateBoxResource(VStringParam in_sResourceName, vfloat32 in_fWidth)
{
	CreateBoxResource(in_sResourceName, VVector3f(in_fWidth, in_fWidth, in_fWidth));
}

void VSimplePhysic::CreateBoxResource(VStringParam in_sResourceName, VVector3f in_Expansion)
{
	VBoxMesh<VTexturedVertex> box(in_Expansion[0], in_Expansion[1], in_Expansion[2]);
	box.GenerateCoordinates();
	box.GenerateTexCoords();

	VResourceId res = BuildResource(in_sResourceName, box);
}


void VSimplePhysic::InitializeResources()
{
	resource::VResourceId modelResourceId =
		resource::VResourceManagerPtr()->CreateResource("/model3ds");

	modelResourceId->AddData(new resource::VFileName("/data/afighter.3ds"));

	std::string sphereName("/data/ball");
	CreateSphereResource(sphereName.c_str(), 10.0f);
	CreateTextureEffect("/data/moon.jpg","/textures/sphere", sphereName.c_str());

	std::string sphereName2("/data/sphere");
	CreateSphereResource(sphereName2.c_str(), 5.0f);
	CreateTextureEffect("","/textures/sphere", sphereName2.c_str());

	std::string planeName("/data/plane");
	CreatePlaneResource(planeName.c_str(), VVector3f(0,0,-1), 50);
	CreateTextureEffect("/data/plane.jpg","/textures/plane", planeName.c_str());

	std::string planeName2("/data/plane2");
	CreatePlaneResource(planeName2.c_str(), VVector3f(0,-1,0), 50);
	CreateTextureEffect("","/textures/plane", planeName2.c_str());

	std::string planeName3("/data/plane3");
	CreatePlaneResource(planeName3.c_str(), VVector3f(-1,0,0), 50);
	CreateTextureEffect("","/textures/plane", planeName3.c_str());

	std::string planeName4("/data/plane4");
	CreatePlaneResource(planeName4.c_str(), VVector3f(0,0,1), 150);
	CreateTextureEffect("","/textures/plane", planeName4.c_str());

	std::string planeName5("/data/plane5");
	CreatePlaneResource(planeName5.c_str(), VVector3f(0,1,0), 150);
	CreateTextureEffect("","/textures/plane", planeName5.c_str());
	std::string planeName6("/data/plane6");
	CreatePlaneResource(planeName6.c_str(), VVector3f(1,0,0), 150);
	CreateTextureEffect("","/textures/plane", planeName6.c_str());

	std::string planeName7("/data/plane7");
	CreatePlaneResource(planeName7.c_str(), VVector3f(0,0.5f,0.5f), 150);
	CreateTextureEffect("","/textures/plane", planeName7.c_str());

	std::string boxName("/data/box");
	CreateBoxResource(boxName.c_str(), 10.0f);
	CreateTextureEffect("", "/textures/sphere", boxName.c_str());
}

void VSimplePhysic::CreateBoxPhysicObject(vfloat32 in_fMasss,
						   VVector3f in_Expansion,
						   entity::VEntity* in_pParentEntity,
						   VPhysicManagerPart* in_pPhysicManager,
						   std::string in_sResourceName)
{
	VPhysicBody* pPhysicBody;
	VPhysicBoxMassState* pMassState = new VPhysicBoxMassState();
	VPhysicGeometryBox* pBoxGeometry = new VPhysicGeometryBox();
	pMassState->SetMass(in_fMasss);
	pBoxGeometry->SetWidth(in_Expansion[0]);
	pBoxGeometry->SetLength(in_Expansion[1]);
	pBoxGeometry->SetHeight(in_Expansion[2]);
	pBoxGeometry->CreateBox(in_pPhysicManager->GetPhysicWorld()->GetSpace());

	pPhysicBody = in_pPhysicManager->GetPhysicWorld()->CreateBody();
	pPhysicBody->AddState(pMassState);
	pPhysicBody->Create(in_pPhysicManager->GetPhysicWorld());
	pPhysicBody->SetCollisionBody(pBoxGeometry);

	entity::VEntity* pObjectEntityBox= new entity::VEntity();
	VRigidBodyPart* pBodyPartBox = new VRigidBodyPart;

	pObjectEntityBox->AddPart(VRigidBodyPart::GetDefaultId(), SharedPtr(pBodyPartBox));
	pObjectEntityBox->AddPart(VPhysicBody::GetDefaultId(), SharedPtr(pPhysicBody));

	in_pParentEntity->AddChild(SharedPtr(pObjectEntityBox));
	pObjectEntityBox->Activate();

	resource::VResourceManagerPtr pResManager;

	VResourceId box = pResManager->GetResourceByName(in_sResourceName.c_str());

	graphics::VModelMesh::MeshPtr meshResourcePtr = 0;
	graphics::VModelMesh::MaterialPtr materialResourcePtr = 0;

	meshResourcePtr = box->GetData<graphics::IVMesh>();
	materialResourcePtr = box->GetData<graphics::IVMaterial>();

	scene::VModelPart* pSceneModel  = new scene::VModelPart(VModel(VModelMesh(
		meshResourcePtr, materialResourcePtr)));

	pObjectEntityBox->AddPart(scene::VModelPart::GetDefaultId(), SharedPtr(pSceneModel));
	pSceneModel->Activate();
}

VEffectDescription VSimplePhysic::CreateTextureEffectDescription(VStringParam in_sResourceName)
{
	// create an effect description for the mesh
	VEffectDescription effect;
	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());

	pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));

	// add resource info

	graphics::VState textureState = TextureState(in_sResourceName);

	pass.AddState(textureState);

	return effect;
}

void VSimplePhysic::CreateSpherePhysicObject(
	vfloat32 in_fMasss,
	vfloat32 in_fRadius,
	entity::VEntity* in_pParentEntity,
	VPhysicManagerPart* in_pPhysicManager,
	std::string in_sResourceName)
{
	VPhysicBody* pPhysicBodySphere;
	VPhysicSphereMassState* pMassState = new VPhysicSphereMassState();
	VPhysicGeometrySphere* pSphereGeometry = new VPhysicGeometrySphere();
	pMassState->SetMass(in_fMasss);
	pSphereGeometry->SetSphereRadius(in_fRadius);
	pSphereGeometry->CreateSphere(in_pPhysicManager->GetPhysicWorld()->GetSpace());

	pPhysicBodySphere = in_pPhysicManager->GetPhysicWorld()->CreateBody();
	pPhysicBodySphere->AddState(pMassState);
	pPhysicBodySphere->Create(in_pPhysicManager->GetPhysicWorld());
	pPhysicBodySphere->SetCollisionBody(pSphereGeometry);

	entity::VEntity* pObjectEntitySphere= new entity::VEntity();
	VRigidBodyPart* pBodyPartSphere = new VRigidBodyPart;

	pObjectEntitySphere->AddPart(VRigidBodyPart::GetDefaultId(), SharedPtr(pBodyPartSphere));
	pObjectEntitySphere->AddPart(VPhysicBody::GetDefaultId(), SharedPtr(pPhysicBodySphere));

	in_pParentEntity->AddChild(SharedPtr(pObjectEntitySphere));
	pObjectEntitySphere->Activate();

	resource::VResourceManagerPtr pResManager;

	VResourceId sphere = pResManager->GetResourceByName(in_sResourceName.c_str());

	graphics::VModelMesh::MeshPtr meshResourcePtrSphere = 0;
	graphics::VModelMesh::MaterialPtr materialResourcePtrSphere = 0;

	meshResourcePtrSphere = sphere->GetData<graphics::IVMesh>();
	materialResourcePtrSphere = sphere->GetData<graphics::IVMaterial>();

	scene::VModelPart* pSceneModelSphere  = new scene::VModelPart(VModel(VModelMesh(
		meshResourcePtrSphere, materialResourcePtrSphere)));

	pObjectEntitySphere->AddPart(scene::VModelPart::GetDefaultId(), SharedPtr(pSceneModelSphere));
	pSceneModelSphere->Activate();
}

void VSimplePhysic::CreatePlanePhysicObject(
	VVector3f in_Normal,
	vfloat32 in_fDistance,
	entity::VEntity* in_pParentEntity,
	VPhysicManagerPart* in_pPhysicManager,
	std::string in_sResourceName)
{
	resource::VResourceManagerPtr pResMan;
	entity::VEntity* pObjectEntity = new entity::VEntity();
	VRigidBodyPart* pBodyPart = new VRigidBodyPart;

	VPhysicGeometryPlane plane;
	plane.SetPlane(graphics::VVertex3f(in_Normal[0], in_Normal[1], in_Normal[2]),in_fDistance);
	plane.CreatePlane(in_pPhysicManager->GetPhysicWorld()->GetSpace());

	VResourceId planeRes = pResMan->GetResourceByName(in_sResourceName.c_str());

	graphics::VModelMesh::MeshPtr meshResourcePtr = 0;
	graphics::VModelMesh::MaterialPtr materialResourcePtr = 0;

	meshResourcePtr = planeRes->GetData<graphics::IVMesh>();
	materialResourcePtr = planeRes->GetData<graphics::IVMaterial>();

	scene::VModelPart* pSceneModel  = new scene::VModelPart(VModel(VModelMesh(
		meshResourcePtr, materialResourcePtr)));
	pObjectEntity->AddPart(scene::VModelPart::GetDefaultId(),SharedPtr(pSceneModel));
	pObjectEntity->AddPart(VRigidBodyPart::GetDefaultId(), SharedPtr(pBodyPart));
	in_pParentEntity->AddChild(SharedPtr(pObjectEntity));
	pSceneModel->Activate();
}

vint VSimplePhysic::Main(vector<string> args)
{
	InitializeResources();

	m_pWorld = new VPhysicWorld();

	// create window
	VWindowManagerPtr pWindowManager;
	VDisplaySettings dis(VSize(1024,768), VPosition(0,0));
	dis.SetFullscreen(false);
	IVWindowManager::WindowPtr pWindow = pWindowManager->QueryWindow(
		"Simple Physics Sample -press ENTER to disable gravity, SPACE to enable",
		&dis//&VDisplaySettings(VSize(800, 600), VPosition(200, 50))
		);

	IVDevice& device(pWindow->QueryGraphicsDevice());
	m_pDevice = &device;
	IVInputManager& input(pWindow->QueryInputManager());
	
	//create scene
	//scene::VNaiveSceneManagerPart* pDefaultRenderAlgorithm = new scene::VNaiveSceneManagerPart();

	entity::VEntity myRootEntity;
	scene::VNaiveSceneManagerPart* pSimpleScene = new scene::VNaiveSceneManagerPart();
	scene::VSimpleShooting* pShooting = new scene::VSimpleShooting();//(m_pDevice);//, pDefaultRenderAlgorithm );
	VPhysicManagerPart* pPhysicsManager = new VPhysicManagerPart(m_pWorld);
	pShooting->SetRenderTarget(m_pDevice);
    
	myRootEntity.AddPart(scene::VSimpleShooting::GetDefaultId(), SharedPtr(pShooting));	
	myRootEntity.AddPart(scene::VNaiveSceneManagerPart::GetDefaultId(), SharedPtr(pSimpleScene));
	myRootEntity.AddPart(VPhysicManagerPart::GetDefaultId(), SharedPtr(pPhysicsManager));
	myRootEntity.Activate();

	//customize the physic manager
	pPhysicsManager->GetPhysicWorld()->GetSpace()->SetSurfaceBounce(0.85f);
	pPhysicsManager->GetPhysicWorld()->SetGravity(0,0,0.0f);
	

	VPhysicBody* pPhysicBody;
	VPhysicBoxMassState massState;
	massState.SetMass(4.3f);
	
	pPhysicBody = pPhysicsManager->GetPhysicWorld()->CreateBody();
	pPhysicBody->AddState(&massState); 
	pPhysicBody->Create(pPhysicsManager->GetPhysicWorld());

	entity::VEntity* pObjectEntity = new entity::VEntity();
	VRigidBodyPart* pBodyPart = new VRigidBodyPart;
		
	pObjectEntity->AddPart(VRigidBodyPart::GetDefaultId(), SharedPtr(pBodyPart));
	pObjectEntity->AddPart(VPhysicBody::GetDefaultId(), SharedPtr(pPhysicBody));
	
	myRootEntity.AddChild(SharedPtr(pObjectEntity));
	pObjectEntity->Activate();

	//scene::VSceneModelPart* pSceneModel  = new scene::VSceneModelPart(
	//	*resource::GetResourceData<VModel>("/model3ds"));
	//pObjectEntity->AddPart(scene::VSceneModelPart::GetDefaultId(), SharedPtr(pSceneModel));
	//pSceneModel->Activate();

	CreateSpherePhysicObject(3.0f, 10.0f, &myRootEntity, pPhysicsManager, "/data/ball" );
	CreateSpherePhysicObject(1.0f, 5.0f, &myRootEntity, pPhysicsManager, "/data/sphere" );
	CreatePlanePhysicObject(VVector3f(0,0,-1),50, &myRootEntity, pPhysicsManager, "/data/plane");
	CreatePlanePhysicObject(VVector3f(0,-1,0),50, &myRootEntity, pPhysicsManager, "/data/plane2");
	CreatePlanePhysicObject(VVector3f(-1,0,0),50, &myRootEntity, pPhysicsManager, "/data/plane3");
	CreatePlanePhysicObject(VVector3f(0,0,1),150, &myRootEntity, pPhysicsManager, "/data/plane4");
	CreatePlanePhysicObject(VVector3f(0,1,0),150, &myRootEntity, pPhysicsManager, "/data/plane5");
	CreatePlanePhysicObject(VVector3f(1,0,0),150, &myRootEntity, pPhysicsManager, "/data/plane6");
	CreatePlanePhysicObject(VVector3f(0,0.5f,0.5f),150, &myRootEntity, pPhysicsManager, "/data/plane7");
	CreateBoxPhysicObject(6.2f, VVector3f(10.0, 10.0f, 10.0f),&myRootEntity, pPhysicsManager, "/data/box");
	
	VUpdateManagerPtr pUpdater;
	VSystemManagerPtr pSystem;

	pSystem->SetStatus(true);
	pUpdater->Start();

	// setup camera
	VKeyboardCamera cam(input);
	cam.SetMovementSpeed(4);
	cam.GetCamera().Move(0, 0, 0.0f);
	cam.GetCamera().RotateY(90);
	cam.GetCamera().RotateZ(90);
	cam.GetCamera().Move(0, 0, -10.0f);
	
	//setup keys
	input::IVButton* pEscapeButton;
	input::IVButton* pEnterButton;
	input::IVButton* pSpace;
	input::IVButton* pB;
	input::IVButton* pN;

    pEscapeButton	= &input.GetStandardKey(KeyEscape);
	pEnterButton	= &input.GetStandardKey(KeyReturn);
	pSpace			= &input.GetStandardKey(KeySpace);
	pB					= &input.GetStandardKey(KeyB);
	pN					= &input.GetStandardKey(KeyN);



	while(pSystem->GetStatus())
	{
		if(pEscapeButton->IsDown() == true)
		{
			pSystem->SetStatus(false);
		}

		if(pEnterButton->IsDown() == true)
			pPhysicsManager->GetPhysicWorld()->SetGravity(0,0,-3);

		if(pSpace->IsDown() == true)
 			pPhysicsManager->GetPhysicWorld()->SetGravity(0,0,3.0);

		if(pB->IsDown() == true)
			pPhysicsManager->GetPhysicWorld()->SetGravity(0,0,0.0);

		if(pN->IsDown() == true)
		{
			static int nCount=0;
			std::stringstream ss;
			ss << nCount;
			std::string sphereName("/data/ball");
			sphereName.append(ss.str().c_str());
			nCount++;

			CreateSphereResource(sphereName.c_str(), 2.0f);
			CreateTextureEffect("","/textures/sphere", sphereName.c_str());
			CreateSpherePhysicObject(2.3f, 2.0f, &myRootEntity, pPhysicsManager, sphereName.c_str());
		}
			
	
		device.SetMatrix(IVDevice::ViewMatrix, cam.GetTransform());

		device.BeginScene();

		pShooting->UpdateAndCull();
		pShooting->Render();

		device.EndScene();

		//pPhysicsManager->Update();

		pUpdater->StartNextFrame();
		cam.Move(vfloat32(pUpdater->GetFrameDuration()) * 10);
	}

	pUpdater->Stop();

	return 0;
}

namespace {
	VSimplePhysic g_RacerApp;
}
