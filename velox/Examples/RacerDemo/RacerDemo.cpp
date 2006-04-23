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
#include <V3dLib/Utils/VCircleMoverPart.h>
#include <V3d/Vfs.h>
#include <V3d/Xml.h>
#include <V3d/Physics/VPhysics.h>

#include <sstream>
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
using namespace v3d::xml;
using namespace v3d::physics;

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

const std::string SHADERS_DIR = "/system/graphics/mat/";
const std::string MIRROR_VERTEX_SHADER = SHADERS_DIR + "mirror-vertex.glsl";
const std::string MIRROR_FRAGMENT_SHADER = SHADERS_DIR + "mirror-fragment.glsl";

const std::string TERRAIN_MAT = "/data/mat/terrain";

const VColor4f fogColor(.6f, .4f, .4f, 1.0f);
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


void DumpInfo(VEntity& in_Entity, const std::string& prefix = "")
{
	const std::string indent = ".\t";

	vout
		<< (in_Entity.IsActive() ? " " : "!")
		<< prefix
		<< "Entity \"" << in_Entity.GetName() << "\""
		<< vendl;

	VRangeIterator<IVPart> partIter = in_Entity.PartIterator();
	while( partIter.HasNext() )
	{
		vout 
			<< prefix 
			<< indent << "Part " 
			<< partIter->GetTypeInfo().GetName()
			<< (partIter->IsReady() ? "" : " (misssing requirements)") 
			<< vendl;

		++partIter;
	}

	VRangeIterator<VEntity> childIter = in_Entity.ChildIterator();
	while( childIter.HasNext() )
	{
		DumpInfo(*childIter, prefix + indent);
		++childIter;
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
	IVButton* m_pF1Key;
	IVButton* m_pF2Key;
	VServicePtr<updater::IVUpdateManager> m_pUpdater;
	VServicePtr<system::IVSystemManager> m_pSystem;

	//VSharedPtr<VKeyboardCamera> m_pCamera;
	VSharedPtr<VSimpleShooting> m_pRootShooting;
	VSharedPtr<IVLightManager> m_pLightManager;
	//VSharedPtr<VUpdateManagerPart> m_pUpdateManager;
	VUpdateManagerPart* m_pUpdateManager;
	VPhysicManagerPtr m_pPhysicManager;

	IVDevice& Device();

	void Init();
	void Cleanup();
	void CreateResources();

	//VSharedPtr<VEntity> CreateRoot()
	//{
	//	VSharedPtr<VEntity> pRoot(new VEntity());

	//	VSharedPtr<VNaiveSceneManagerPart> pSceneManager(new VNaiveSceneManagerPart());
	//	pRoot->AddPart(pSceneManager);

	//	VSharedPtr<VSimpleShooting> pShooting(new VSimpleShooting());
	//	//pShooting->SetCamera(m_pCamera.Get());
	//	pShooting->SetRenderTarget(m_pDevice);
	//	m_pRootShooting = pShooting;
	//	pRoot->AddPart(m_pRootShooting);

	//	m_pLightManager.Assign(new VNaiveLightManager());
	//	pRoot->AddPart(m_pLightManager);

	//	m_pUpdateManager.Assign(new VUpdateManagerPart());
	//	pRoot->AddPart(m_pUpdateManager);

	//	return pRoot;
	//}

	void CreateTerrainVolumePart(VTerrainPart* in_pTerrain);

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
		static vbool terrainResourcesCreated = false;

		if( ! terrainResourcesCreated )
		{
			VResourceId matres = VResourceManagerPtr()->CreateResource(TERRAIN_MAT.c_str());
			VEffectDescription effect;
			VRenderPass& pass(effect.AddShaderPath().AddRenderPass());
			pass.AddState(TextureState("/data/tex/mud1.tga"));
			pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
			pass.AddState(LightingState(true));
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
		pSkyboxPart->SetBaseColor(fogColor);
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

		if( in_pParent != 0 )
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

void DumpDir(vfs::IVDirectory& dir, const std::string& prefix)
{
	const std::string indent = ".\t";

	vout << prefix << dir.GetName() << "/" << vendl;

	VRangeIterator<vfs::IVDirectory> childdirs = dir.SubDirs();
	while( childdirs.HasNext() )
	{
		DumpDir(*childdirs, prefix + indent);
		++childdirs;
	}

	VRangeIterator<vfs::IVFile> files = dir.Files();
	while( files.HasNext() )
	{
		vout << prefix << indent << files->GetName() << vendl;
		++files;
	}
}

void DumpFileSystem()
{
	DumpDir(*vfs::VFileSystemPtr()->GetDir("/"), "");
}

VSharedPtr<VEntity> LoadScene(const std::string& in_strFileName)
{
	VSharedPtr<vfs::IVStream> pFileStream = vfs::VFileSystemPtr()->OpenFile(
		in_strFileName.c_str(), vfs::VReadAccess);
	VSharedPtr<IVXMLElement> pXMLDocument = VXMLServicePtr()->GetRootElement(pFileStream.Get());
	VSharedPtr<VEntity> pScene = VEntitySerializationServicePtr()->ParseScene(*pXMLDocument);

	return pScene;
}

/**
* @author ins
*/
VTerrainPart* FindTerrain(VSharedPtr<VEntity> in_Entity)
{
	VTerrainPart* terrain = 0;
	VRangeIterator<VEntity> it = in_Entity->ChildIterator();

	while(it.HasNext())
	{
		std::string name =  (*it).GetName();
		if(name == "world")
		{
			VRangeIterator<VEntity> it2 = (*it).ChildIterator();
			while(it2.HasNext())
			{
				std::string name2 = (*it2).GetName();
				if(name2 == "terrain")
				{
					terrain = (*it2).GetPart<VTerrainPart>();
				}
				++it2;
			}
		}
		++it;
	}
	return terrain;
}

//VEntity* FindWorld(VSharedPtr<VEntity> in_Entity)
//{
//	VTerrainPart* terrain = 0;
//	VRangeIterator<VEntity> it = in_Entity->ChildIterator();
//
//	while(it.HasNext())
//	{
//		std::string name =  (*it).GetName();
//		if(name == "world")
//		{
//			return &(*it);
//		}
//		++it;
//	}
//	return 0;
//}

/**
 * @author ins
 * @pre	valid pointer to terrain part
 * @note creates a memory leak, indices will not be deleted
 */
void RacerDemo::CreateTerrainVolumePart(VTerrainPart* in_pTerrain)
{
	VSharedPtr<VBoundingMeshVolumePart> pBoundingVolume(new VBoundingMeshVolumePart);

	vint size = in_pTerrain->GetIndexCount();
	size = (size-2) * 3; //hack, does not take degenerated triangle into account
	vint* pNewIndices = new vint[size];

	vint* pIndices = (vint*)in_pTerrain->GetIndexBuffer()->GetBufferAddress();
	vint nCount = 0;
	int lastIndex1 = 0;
	int lastIndex2 = 0;
	int lastIndex3 = 0;
	//create a index list out of the terrain strip WITHOUT degenerated triangles
	for(int i = 0; i<in_pTerrain->GetIndexCount(); i++)
	{
		if(i==0) //first triangle copy data
		{
			pNewIndices[nCount] = pIndices[i];
			nCount++;
			pNewIndices[nCount] = pIndices[i+1];
			nCount++;
			pNewIndices[nCount] = pIndices[i+2];
			nCount++;
			i=2;
			continue;
		}
		pNewIndices[nCount] = pIndices[i-1];
		lastIndex1 = pNewIndices[nCount];
		nCount++;

		pNewIndices[nCount] = pIndices[i-2];
		lastIndex2 = pNewIndices[nCount];
		nCount++;

		pNewIndices[nCount] = pIndices[i];
		lastIndex3 = pNewIndices[nCount];
		nCount++;

		if(lastIndex1 == lastIndex2 || lastIndex2 == lastIndex3 || lastIndex1 == lastIndex3)
		{
			nCount -=3;
			vuint a = 0;
			i+=2;
			/*pNewIndices[nCount-2] = 0;
			pNewIndices[nCount-1] = 1;
			pNewIndices[nCount] = 2;*/

		}	
	}

	VBoundingMesh mesh((float*)in_pTerrain->GetVertexBuffer()->GetBufferAddress(), in_pTerrain->GetVertexCount(), 3* sizeof(vfloat32),
		pNewIndices, nCount, 3 * sizeof(vint));

	pBoundingVolume->SetBoundingMesh(mesh);
	//we dont need to attach this by now [laziness]
	//in_pTerrain->AddPart(pBoundingVolume);
	m_pPhysicManager->CreateGeom(pBoundingVolume.Get());

}

/**
 * @author sheijk
 */
vint RacerDemo::Main(std::vector<std::string> args)
{
	Init();
	CreateResources();

	DumpFileSystem();

	//m_pCamera->GetCamera().Move(0, 1.0f, 0);

	//property::SetProperty("v3d.graphics.showNormals", true);

	VSharedPtr<VEntity> pRoot = LoadScene("/edit/racer.v3dscene");
	m_pUpdateManager = pRoot->GetPart<VUpdateManagerPart>();
	//m_pUpdateManager.Assign(new VUpdateManagerPart());
	//pRoot->AddPart(m_pUpdateManager);
	VSharedPtr<VSimpleShooting> pShooting(new VSimpleShooting());
	pShooting->SetRenderTarget(m_pDevice);
	m_pRootShooting = pShooting;
	pRoot->AddPart(m_pRootShooting);
	VInputPart* pInputPart = pRoot->GetPart<VInputPart>();
	pInputPart->SetInputManager(&m_pWindow->QueryInputManager());

	// indenting represents scene graph hierarchy
	//VSharedPtr<VEntity> pRoot = CreateRoot();
	//	VSharedPtr<VEntity> pAmbient = CreateAmbient();
	//	pRoot->AddChild(pAmbient);
	//		pAmbient->AddChild(CreateSkyBox());
	//		pAmbient->AddChild(CreateReflectiveObj());
	//		VRect3D mirrorArea;
	//		mirrorArea.right = ToVector3f(100, 0, 0);
	//		mirrorArea.up = ToVector3f(0, 0, -100);
	//		mirrorArea.distance = 0;
	//		CreateWater(mirrorArea, pAmbient);
	//		const vfloat32 mapSize = 70.0f;
	//		CreateMovingLight(VColor4f(1, 0, 0), VVector3f(0, 15, 5), 20.0f, .05f, pAmbient);
	//		CreateMovingLight(VColor4f(0, 1, 0), VVector3f(10, 20, 0), 30.0f, -.2f, pAmbient);
	//		CreateMovingLight(VColor4f(0, 0, 1), VVector3f(0, 25, 10), 50.0f, .1f, pAmbient);
	//		CreateMovingLight(VColor4f(0, 1, 1), VVector3f(20, 20, 0), 80.0f, -.1f, pAmbient);
	//		CreateLight(VColor4f(1, 1, 1), VVector3f(0, 5, 0), pAmbient);

	//		CreateTrackballCamPart(pAmbient);
	//		CreateKeyboardCamPart(pAmbient);

	//		VSharedPtr<VEntity> pLoaded = VEntitySerializationServicePtr()->ParseScene(
	//			*VXMLServicePtr()->GetRootElement(&*vfs::VFileSystemPtr()->OpenFile("/data/deco.xml", vfs::VReadAccess)));
	//		pAmbient->AddChild(pLoaded);

	//		{ // test geometry
	//			const vfloat32 minv = -20.0f;
	//			const vfloat32 maxv = 20.0f;
	//			const vfloat32 step = 20.0f;

	//			for(vfloat32 x = minv; x <= maxv; x += step)
	//			for(vfloat32 y = minv; y <= maxv; y += step)
	//			for(vfloat32 z = minv; z <= maxv; z += step)
	//				CreateSphere(ToVector3f(x, y, z), 1.0f, pAmbient);
	//		}
	//	VSharedPtr<VEntity> pWorld = CreateWorld();
	//	pRoot->AddChild(pWorld);
	//		pWorld->AddChild(CreateTerrain());

	m_pPhysicManager.Assign(new VPhysicManager());
	m_pPhysicManager->RegisterToUpdater();

	pRoot->Activate();
	DumpInfo(*pRoot);


	VTerrainPart* pTerrain = FindTerrain(pRoot);
	m_pF1Key = &m_pWindow->QueryInputManager().GetStandardKey(KeyF1);
	m_pF2Key = &m_pWindow->QueryInputManager().GetStandardKey(KeyF2);

	if(pTerrain)
	{
		CreateTerrainVolumePart(pTerrain);
	}

	
	//TODO: support im device oder so
	glEnable(GL_FOG);
	vfloat32 fogColor2[4] = { fogColor.red, fogColor.green, fogColor.blue, 1.0f };
	glFogfv(GL_FOG_COLOR, fogColor2);
	glFogf(GL_FOG_DENSITY, 1.0f);
	glFogf(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 300.f);
	glFogf(GL_FOG_END, 400.0f);

	VMatrix44f test = math::ScaleMatrix(10.0f);
	vout << test << vendl;

	m_pUpdater->Start();
	while(m_pSystem->GetStatus())
	{
		Device().BeginScene();

		const vfloat32 frameDuration = vfloat32(m_pUpdater->GetFrameDuration());

		if( m_pTimeValue.Get() != 0 )
			m_pTimeValue->SetValue(m_pTimeValue->GetValue() + frameDuration);

		m_pUpdateManager->Update(frameDuration);

		m_pRootShooting->UpdateAndCull();
		m_pRootShooting->Render();

		Device().EndScene();

		m_pUpdater->StartNextFrame();

		static vfloat32 timeTillNextToggle = .0f;
		timeTillNextToggle -= frameDuration;

		if( m_pCamToggleKey->IsDown() && timeTillNextToggle <= .0f )
		{
			static vuint camNum = 0;
			camNum = (camNum + 1) % m_pRootShooting->CameraCount();

			m_pRootShooting->SetActiveCamera(camNum);

			m_pCamToggleKey->SetDown(false);
			timeTillNextToggle = .1f;
		}

		if( m_pEscapeKey->IsDown() )
			m_pSystem->SetStatus(false);

		if( m_pF1Key->IsDown() )
		{
			float f = rand() % 10;
			f+=0.1f; //excluding 0

			VSharedPtr<VEntity> pEntity(new VEntity());
			VSharedPtr<VRigidBodyPart> pRidgidPart(new VRigidBodyPart());
			VSharedPtr<VBoundingSphereVolumePart> pBoundingVolume(new VBoundingSphereVolumePart());
		
			pBoundingVolume->GetBoundingSphere()->SetRadius(f);
			pEntity->AddPart(pBoundingVolume);

			VSharedPtr<VBody> pBody = m_pPhysicManager->Create(
			pBoundingVolume.Get(), f);
			VSharedPtr<VBodyPart> pPhysicPart(new VBodyPart(pBody));

			//pRidgidPart->SetPosition(VVector3f(0,20,0));
			pRidgidPart->SetPosition(m_pRootShooting->GetCamera()->GetPosition());
			//set the position of the body, cos the entity system does not work by now
			pPhysicPart->GetBody()->SetPosition(
				graphics::VVertex3f(
				m_pRootShooting->GetCamera()->GetPosition().GetX(),
				m_pRootShooting->GetCamera()->GetPosition().GetY(),
				m_pRootShooting->GetCamera()->GetPosition().GetZ()
				)
				);

			pEntity->AddPart(pPhysicPart);
			pEntity->AddPart(pRidgidPart);

			//pEntity->AddPart(SharedPtr(new VArrowMeshPart(VColor4f(1,0,1,1))));
			pEntity->AddPart(SharedPtr(new VSphereMeshPart()));
			
			pRoot->AddChild(pEntity);
			//FindWorld(pRoot)->AddChild(pEntity);
			pEntity->Activate();
			//DumpInfo(*pRoot);

		}
		//TODO: write a VBoxMeshPart
		//if( m_pF2Key->IsDown() )
		//{
		//	
		//	float f = rand() % 10;
		//	f+=0.1f; //excluding 0

		//	VSharedPtr<VEntity> pEntity(new VEntity());
		//	VSharedPtr<VRigidBodyPart> pRidgidPart(new VRigidBodyPart());
		//	VSharedPtr<VBoundingBoxVolumePart> pBoundingVolume(new VBoundingBoxVolumePart());

		//	pBoundingVolume->GetBoundingBox()->SetSize(VVector3f(1+f,2-f,1+f));
		//	pEntity->AddPart(pBoundingVolume);

		//	VSharedPtr<VBodyPart> pPhysicPart = m_pPhysicManager->Create(pBoundingVolume.Get(), f);
		//	//pRidgidPart->SetPosition(VVector3f(0,20,0));
		//	pRidgidPart->SetPosition(m_pRootShooting->GetCamera()->GetPosition());
		//	//set the position of the body, cos the entity system does not work by now
		//	pPhysicPart->GetBody()->SetPosition(
		//		graphics::VVertex3f(
		//		m_pRootShooting->GetCamera()->GetPosition().GetX(),
		//		m_pRootShooting->GetCamera()->GetPosition().GetY(),
		//		m_pRootShooting->GetCamera()->GetPosition().GetZ()
		//		)
		//		);

		//	pEntity->AddPart(pPhysicPart);
		//	pEntity->AddPart(pRidgidPart);

		//	//pEntity->AddPart(SharedPtr(new VArrowMeshPart(VColor4f(1,0,1,1))));
		//	pEntity->AddPart(SharedPtr(new VBoxMesh(1+f,2-f,1+f)));

		//	pRoot->AddChild(pEntity);
		//	//FindWorld(pRoot)->AddChild(pEntity);
		//	pEntity->Activate();
		//	//DumpInfo(*pRoot);

		//}
	}
	m_pUpdater->Stop();

	pRoot->Deactivate();
	
	Cleanup();

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

void RacerDemo::Cleanup()
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
	mirrorRes->AddData(CopyPtr(GLSLEffect(MIRROR_VERTEX_SHADER.c_str(), MIRROR_FRAGMENT_SHADER.c_str())));

	VResourceId whiteMat = VResourceManagerPtr()->CreateResource("/materials/white");
	VEffectDescription whiteLit = ColorEffect(1, 1, 1, 1);
	whiteLit.ShaderPath(0).RenderPass(0).AddState(LightingState(true));
	whiteMat->AddData(CopyPtr(whiteLit));
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
