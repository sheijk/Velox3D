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
#include <V3dLib/Property.h>
#include <V3dLib/Utils/VCameraPart.h>
#include <V3dLib/Utils/VTrackballPart.h>
#include <V3dLib/Utils/VFPSMoverPart.h>

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
using namespace v3d::utils;

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const std::string APP_NAME = "RacerDemo";
const std::string MIRROR_TEXTURE_RES = "/mirror-texture";

const std::string MAT_WHITE_UNLIT = "/system/mat/unlit-white";

//-----------------------------------------------------------------------------

class VCircleMoverPart : public VPartBaseAdapter<IVUpdateablePart>
{
public:
	VCircleMoverPart();

	void Update(vfloat32 in_fSeconds);

	void Activate();
	void Deactivate();

	vfloat32 GetRadius() const { return m_fRadius; }
	void SetRadius(const vfloat32& in_Value) { m_fRadius = in_Value; }
	VVector3f GetCenter() const { return m_Center; }
	void SetCenter(const VVector3f& in_Value) { m_Center = in_Value; }
	vfloat32 GetSpeed() const { return m_fSpeed; }
	void SetSpeed(const vfloat32& in_Value) { m_fSpeed = in_Value; }

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
	
private:
	entity::VPartConnection<entity::VUpdateManagerPart> m_pUpdateManager;
	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBody;

    vfloat32 m_fRadius;
	VVector3f m_Center;
	vfloat32 m_fSpeed;

	vfloat32 m_fAngle;
};

V3D_TYPEINFO_WITHPARENT(VCircleMoverPart, v3d::entity::IVUpdateablePart);

VCircleMoverPart::VCircleMoverPart() :
	m_pRigidBody(entity::VPartDependency::Neighbour, RegisterTo()),
	m_pUpdateManager(entity::VPartDependency::Ancestor, RegisterTo())
{
	m_fSpeed = math::Pi() * 1;
	m_fAngle = .0f;
	m_fRadius = 10.0f;
}

void VCircleMoverPart::Update(vfloat32 in_fSeconds)
{
	m_fAngle += in_fSeconds * m_fSpeed;
	VVector3f newPos(sin(m_fAngle), 0, cos(m_fAngle));
	newPos *= m_fRadius;
	newPos += m_Center;
	m_pRigidBody->SetPosition(newPos);
}

void VCircleMoverPart::Activate()
{
	m_pUpdateManager->Register(this);
}

void VCircleMoverPart::Deactivate()
{
	m_pUpdateManager->Unregister(this);
}

//-----------------------------------------------------------------------------


void DumpInfo(VEntity& in_Entity, const std::string& prefix = "")
{
	if( in_Entity.IsActive() == false )
	{
		vout
			<< (in_Entity.IsActive() ? " " : "!")
			<< prefix
			<< "Entity"
			<< vendl;

		VRangeIterator<IVPart> partIter = in_Entity.PartIterator();
		while( partIter.HasNext() )
		{
			vout 
				<< prefix 
				<< "\tPart " 
				<< partIter->GetTypeInfo().GetName()
				<< (partIter->IsReady() ? "" : " (misssing requirements)") 
				<< vendl;

			++partIter;
		}
	}
	else {
		VRangeIterator<VEntity> childIter = in_Entity.ChildIterator();
		while( childIter.HasNext() )
		{
			DumpInfo(*childIter, prefix + "\t");
			++childIter;
		}
	}
}
/*
void CollectInactiveNodes(const VEntity* pRoot, std::vector<const VEntity*>* inactiveNodes)
{
    if( pRoot != NULL )
	{
		if( ! pRoot->IsActive() )
		{
			inactiveNodes->push_back(pRoot);
		}
		else
		{
			VRangeIterator<VEntity> child = pRoot->ChildIterator();
			while( child.HasNext() )
			{
				CollectInactiveNodes(&*child, inactiveNodes);

				++child;
			}
		}
	}
}

void PrintInactiveNodeNames(VEntity* pRoot)
{
	std::vector<const VEntity*> inactiveNodes;
	CollectInactiveNodes(pRoot, &inactiveNodes);

	for(vuint num = 0; num < inactiveNodes->size(); ++num)
	{
		const VEntity* node = inactiveNodes[num];
		vout << node-> name !!
	}
}
*/

//-----------------------------------------------------------------------------

class RacerDemo : public VVeloxApp
{
public:
	RacerDemo();

	virtual vint Main(std::vector<std::string> args);

private:
	IVWindowManager::IVWindowPtr m_pWindow;
	IVDevice* m_pDevice;
	IVButton* m_pEscapeKey;
	IVButton* m_pCamToggleKey;
	VServicePtr<updater::IVUpdateManager> m_pUpdater;
	VServicePtr<system::IVSystemManager> m_pSystem;

	//VSharedPtr<VKeyboardCamera> m_pCamera;
	VSharedPtr<VSimpleShooting> m_pRootShooting;
	VSharedPtr<IVLightManager> m_pLightManager;
	VSharedPtr<VUpdateManagerPart> m_pUpdateManager;

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
		//pShooting->SetCamera(m_pCamera.Get());
		pShooting->SetRenderTarget(m_pDevice);
		m_pRootShooting = pShooting;
		pRoot->AddPart(m_pRootShooting);

		m_pLightManager.Assign(new VNaiveLightManager());
		pRoot->AddPart(m_pLightManager);

		m_pUpdateManager.Assign(new VUpdateManagerPart());
		pRoot->AddPart(m_pUpdateManager);

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

	VSharedPtr<VEntity> CreateGfxEntity(
		VSharedPtr<IVGraphicsPart> gfxPart,	
		const math::VRBTransform& transform = VRBTransform())
	{
		VSharedPtr<VEntity> pEntity(new VEntity());
		VSharedPtr<VRigidBodyPart> pRBPart(new VRigidBodyPart());
		pRBPart->SetTransform(transform);
		pEntity->AddPart(pRBPart);
		pEntity->AddPart(gfxPart);
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
		pSkyboxPart->SetBaseColor(VColor4f(.6f, .4f, .4f, 1));
		pEntity->AddPart(pSkyboxPart);
		pEntity->AddPart(SharedPtr(new VRigidBodyPart()));
		return pEntity;
	}

	VSharedPtr<VFloatParamValue> m_pTimeValue;

	void CreateWater(const VRect3D& area, VSharedPtr<VEntity> pParent)
	{
		VSharedPtr<VMatrix44fParamValue> m_pCameraMatValue;

		VSharedPtr<VEntity> pMirrorEntity(new VEntity());

		VSharedPtr<VMirrorShooting> pMirrorShooting(new VMirrorShooting());
		VDisplaySettings mirrorTexSettings;
		mirrorTexSettings.SetSize(512, 512);
		VResourceId(MIRROR_TEXTURE_RES.c_str())->AddData(Device().CreateOffscreenContext(&mirrorTexSettings));
		pMirrorShooting->SetRenderTargetResource(MIRROR_TEXTURE_RES);
		pMirrorShooting->SetPlane(area.GetPlane());
		pMirrorEntity->AddPart(pMirrorShooting);
		pParent->AddChild(pMirrorEntity);

		m_pCameraMatValue = pMirrorShooting->GetTextureMatrixValue();

		{
			//VSharedPtr<VMeshPartBase> pPlaneMesh(new VSphereMeshPart(20.0f));

			VSharedPtr<VPlaneMeshPart> pPlaneMesh(new VPlaneMeshPart());
			pPlaneMesh->SetRight(area.right);
			pPlaneMesh->SetUp(area.up);
			pPlaneMesh->CenterAt(area.GetPosition());

			pPlaneMesh->SetMaterial(GetResourceData<IVMaterial>(MIRROR_TEXTURE_RES.c_str()));

			pPlaneMesh->AddParamValue("cam", m_pCameraMatValue);
			pPlaneMesh->AddParamValue("mirrorTex", SharedPtr(new VTextureValue(MIRROR_TEXTURE_RES.c_str())));
			m_pTimeValue.Assign(new VFloatParamValue(0));
			pPlaneMesh->AddParamValue("time", m_pTimeValue);
			//pPlaneMesh->AddParamValue("mirrorTex", SharedPtr(new VTextureValue("/data/tgatest.tga")));

			pPlaneMesh->AddParamValue("c", SharedPtr(new VGenericValue<VVector4f>(ToVector4f(1, 0, 0, 1))));
			//pPlaneMesh->AddParamValue("scale", SharedPtr(new VGenericValue<vfloat32>(.1f)));

			pParent->AddChild(CreateGfxEntity(pPlaneMesh));
		}
	}

	/**
	 * The water rendering has a bug which lets it render incorrectly if no
	 * object with cube mapping is rendered in the scene...
	 */
	VSharedPtr<VEntity> CreateReflectiveObj(VSharedPtr<VEntity> in_pParent = SharedPtr<VEntity>(0))
	{
		VSharedPtr<VEntity> pEntity(new VEntity());

		pEntity->AddPart(SharedPtr(new VSphereMeshPart(1.0f)));
		VSharedPtr<VRigidBodyPart> pRBPart(new VRigidBodyPart());
		pRBPart->SetPosition(VVector3f(0, -100, 0));
		pEntity->AddPart(pRBPart);

		if( in_pParent.Get() != 0 )
		{
			in_pParent->AddChild(pEntity);
		}

		return pEntity;
	}

	/** Creates a light source with a small mesh */
	VSharedPtr<VEntity> CreateLight(
		const VColor4f& in_Color, 
		const VVector3f& in_Position,
		VSharedPtr<VEntity> in_pParent = SharedPtr<VEntity>(0))
	{
		VSharedPtr<VEntity> pEntity(new VEntity());

		VSharedPtr<VLightPart> pLightPart(new VLightPart());
		pEntity->AddPart(pLightPart);
		pLightPart->Light().SetAmbientColor(VColor4f(0, 0, 0, 0));
		pLightPart->Light().SetDiffuseColor(in_Color);
		pLightPart->Light().SetSpecularColor(in_Color);
		pLightPart->Light().SetPosition(in_Position);

		VSharedPtr<VRigidBodyPart> pRBPart(new VRigidBodyPart());
		pRBPart->SetPosition(in_Position);
		pEntity->AddPart(pRBPart);

		VSharedPtr<VSphereMeshPart> pMesh(new VSphereMeshPart(.1f));
		pMesh->SetMaterial(GetResourceData<IVMaterial>(MAT_WHITE_UNLIT.c_str()));
		pEntity->AddPart(pMesh);

		if( in_pParent.Get() != 0 )
			in_pParent->AddChild(pEntity);

		return pEntity;
	}

	VSharedPtr<VEntity> CreateMovingLight(
		const VColor4f& in_Color, 
		const VVector3f& in_Position,
		vfloat32 in_fRadius,
		vfloat32 in_fSpeed,
		VSharedPtr<VEntity> in_pParent = SharedPtr<VEntity>(0))
	{
		VSharedPtr<VEntity> pEntity = CreateLight(in_Color, in_Position, in_pParent);

		VSharedPtr<VCircleMoverPart> pMover(new VCircleMoverPart());
		pMover->SetCenter(in_Position);
		pMover->SetRadius(in_fRadius);
		pMover->SetSpeed(in_fSpeed);
		pEntity->AddPart(pMover);

		return pEntity;
	}

	VSharedPtr<VEntity> CreateSphere(const VVector3f& pos, vfloat32 radius,
		VSharedPtr<VEntity> in_pParent = SharedPtr<VEntity>(0))
	{
		VSharedPtr<VEntity> pEntity(new VEntity());

		VSharedPtr<VRigidBodyPart> pBody(new VRigidBodyPart());
		pEntity->AddPart(pBody);
		pBody->SetPosition(pos);

		VSharedPtr<VSphereMeshPart> pGfx(SharedPtr(new VSphereMeshPart(radius)));
		pGfx->SetMaterial(GetResourceData<IVMaterial>("/materials/white"));
		pEntity->AddPart(pGfx);

		if( in_pParent.Get() != 0 )
			in_pParent->AddChild(pEntity);

		return pEntity;
	}

	VSharedPtr<VEntity> CreateTrackballCamPart(
		VSharedPtr<VEntity> in_pParent = SharedPtr<VEntity>(0))
	{
		VSharedPtr<VEntity> pEntity(new VEntity());

		pEntity->AddPart(SharedPtr(new VRigidBodyPart()));
		pEntity->AddPart(SharedPtr(new VCameraPart()));

		VSharedPtr<VTrackballPart> pTrackball(new VTrackballPart());
		pTrackball->SetTrackball(SharedPtr(new VMouseTrackball(&m_pWindow->QueryInputManager().GetStandardMouse())));
		pEntity->AddPart(pTrackball);

		if( in_pParent.Get() != 0 )
			in_pParent->AddChild(pEntity);

		return pEntity;
	}

	VSharedPtr<VEntity> CreateKeyboardCamPart(
		VSharedPtr<VEntity> in_pParent = SharedPtr<VEntity>(0))
	{
		VSharedPtr<VEntity> pEntity(new VEntity());

		pEntity->AddPart(SharedPtr(new VRigidBodyPart()));
		pEntity->AddPart(SharedPtr(new VCameraPart()));

		VSharedPtr<VFPSMoverPart> pFPS(new VFPSMoverPart());
		pFPS->QueryButtons(m_pWindow->QueryInputManager());
		pEntity->AddPart(pFPS);

		if( in_pParent.Get() != 0 )
			in_pParent->AddChild(pEntity);

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

	//m_pCamera->GetCamera().Move(0, 1.0f, 0);

	//property::SetProperty("v3d.graphics.showNormals", true);

	// indenting represents scene graph hierarchy
	VSharedPtr<VEntity> pRoot = CreateRoot();
		VSharedPtr<VEntity> pAmbient = CreateAmbient();
		pRoot->AddChild(pAmbient);
			pAmbient->AddChild(CreateSkyBox());
			pAmbient->AddChild(CreateReflectiveObj());
			VRect3D mirrorArea;
			mirrorArea.right = ToVector3f(100, 0, 0);
			mirrorArea.up = ToVector3f(0, 0, -100);
			mirrorArea.distance = 0;
			CreateWater(mirrorArea, pAmbient);
			const vfloat32 mapSize = 70.0f;
			CreateMovingLight(VColor4f(1, 0, 0), VVector3f(0, 15, 5), 20.0f, .05f, pAmbient);
			CreateMovingLight(VColor4f(0, 1, 0), VVector3f(10, 20, 0), 30.0f, -.2f, pAmbient);
			CreateMovingLight(VColor4f(0, 0, 1), VVector3f(0, 25, 10), 50.0f, .1f, pAmbient);
			CreateMovingLight(VColor4f(0, 1, 1), VVector3f(20, 20, 0), 80.0f, -.1f, pAmbient);
			CreateLight(VColor4f(1, 1, 1), VVector3f(0, 5, 0), pAmbient);

			CreateTrackballCamPart(pAmbient);
			CreateKeyboardCamPart(pAmbient);

			{ // test geometry
				const vfloat32 minv = -20.0f;
				const vfloat32 maxv = 20.0f;
				const vfloat32 step = 20.0f;

				for(vfloat32 x = minv; x <= maxv; x += step)
				for(vfloat32 y = minv; y <= maxv; y += step)
				for(vfloat32 z = minv; z <= maxv; z += step)
					CreateSphere(ToVector3f(x, y, z), 1.0f, pAmbient);
			}
		VSharedPtr<VEntity> pWorld = CreateWorld();
		pRoot->AddChild(pWorld);
			pWorld->AddChild(CreateTerrain());


	pRoot->Activate();
	DumpInfo(*pRoot);

	m_pUpdater->Start();
	while(m_pSystem->GetStatus())
	{
		Device().BeginScene();

		const vfloat32 frameDuration = vfloat32(m_pUpdater->GetFrameDuration());

		if( m_pTimeValue.Get() != 0 )
			m_pTimeValue->SetValue(m_pTimeValue->GetValue() + frameDuration);

		m_pUpdateManager->Update(frameDuration);

		//m_pCamera->Move(frameDuration);
		//m_pCamera->ApplyTo(Device());

		m_pRootShooting->UpdateAndCull();
		//m_pCamera->ApplyTo(Device());
		//m_pLightManager->ApplyLights(&Device(), NULL);
		m_pRootShooting->Render();

		Device().EndScene();

		m_pUpdater->StartNextFrame();

		if( m_pCamToggleKey->IsDown() )
		{
			static vuint camNum = 0;
			camNum = (camNum + 1) % m_pRootShooting->CameraCount();

			m_pRootShooting->SetActiveCamera(camNum);

			m_pCamToggleKey->SetDown(false);
		}

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
	m_pCamToggleKey = 0;
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
	m_pCamToggleKey = &m_pWindow->QueryInputManager().GetStandardKey(KeyTab);

	// init system and updater service
	m_pSystem->SetStatus(true);

	//m_pCamera.Assign(new VKeyboardCamera(m_pWindow->QueryInputManager()));
}

void RacerDemo::Shutdown()
{
	m_pDevice = 0;
	m_pWindow.Release();
	m_pEscapeKey = 0;
}

void RacerDemo::CreateResources()
{
	VResourceId whiteUnlit = VResourceManagerPtr()->CreateResource(MAT_WHITE_UNLIT.c_str());
	VEffectDescription whiteUnlitEffect;
	whiteUnlitEffect.AddShaderPath().AddRenderPass();
	whiteUnlitEffect.ShaderPath(0).RenderPass(0).AddState(DefaultColorState(1, 1, 1, 1));
	whiteUnlitEffect.ShaderPath(0).RenderPass(0).AddState(LightingState(false));
	whiteUnlit->AddData(CopyPtr(whiteUnlitEffect));

	VResourceId mirrorRes = VResourceManagerPtr()->CreateResource(MIRROR_TEXTURE_RES.c_str());
	mirrorRes->AddData(CopyPtr(GLSLEffect("/data/shaders/mirror-vertex.glsl", "/data/shaders/mirror-fragment.glsl")));

	VResourceId whiteMat = VResourceManagerPtr()->CreateResource("/materials/white");
	whiteMat->AddData(CopyPtr(ColorEffect(1, 1, 1, 1)));
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
