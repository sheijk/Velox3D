#include <vector>
#include <string>

#include <V3d/Core.h>
#include <V3d/Vfs.h>
#include <v3d/Window.h>
#include <V3d/Updater.h>
#include <V3d/System.h>
#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3dLib/Graphics/Renderers/Terrain/VTerrainRenderer.h>
#include <V3dLib/Math.h>
#include <V3d/Input.h>
#include <V3d/Image.h>
#include <V3d/Entity.h>

#include "Graphics/VMeshPart.h"
#include "Shared/VUpdateablePart.h"

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
using namespace racer;
using namespace utils;

using namespace std;

#include "RacerUtils.h"
//-----------------------------------------------------------------------------

/**
 * Gets a VRigidBodyPart named "body" and sets it's position vector to the
 * camera's position vector
 */
class VCameraPosPart : public VUpdateablePart
{
	VRigidBodyPart* m_pRigidBody;
	const IVCamera& m_Camera;

public:
	VCameraPosPart(
		const IVCamera& in_Camera, 
		VEntityUpdater<VUpdateablePart>* in_pUpdater
		);

	virtual void TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part);
	virtual void Update();
};

VCameraPosPart::VCameraPosPart(
	const IVCamera& in_Camera,
	VEntityUpdater<VUpdateablePart>* in_pUpdater
) : 
	VUpdateablePart(in_pUpdater),
	m_Camera(in_Camera)
{
	m_pRigidBody = 0;
}

void VCameraPosPart::TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part)
{
	if( in_Id.AsStdString() == "body" && in_Part.IsOfType<VRigidBodyPart>() )
	{
		m_pRigidBody = in_Part.Convert<VRigidBodyPart>();
	}
}

void VCameraPosPart::Update()
{
	if( m_pRigidBody != 0 )
	{
		m_pRigidBody->SetPosition(m_Camera.GetPosition());
	}
}

//-----------------------------------------------------------------------------

class VRacerApp : public VVeloxApp
{
	IVDevice& GetDevice() { return *m_pDevice; }

	IVEntityManager::EntityPtr CreateSkyEntity();
	IVEntityManager::EntityPtr CreateHeightmapEntity();

	VGraphicsManager m_GraphicsManager;
	IVDevice* m_pDevice;
public:
	virtual vint Main(vector<string> args);
};

//-----------------------------------------------------------------------------
vint VRacerApp::Main(vector<string> args)
{
	vout << "brumm brumm" << vendl;

	// create window
	VWindowManagerPtr pWindowManager;
	IVWindowManager::WindowPtr pWindow = pWindowManager->QueryWindow(
		"Racer Testing App",
		&VDisplaySettings(VSize(640, 480), VPosition(1024-640, 0))
		);

	IVDevice& device(pWindow->QueryGraphicsDevice());
	m_pDevice = &device;
	IVInputManager& input(pWindow->QueryInputManager());

	// setup sub systems (for entities)
	VSimpleDrawList drawList(device);
	m_GraphicsManager.SetDrawList(drawList);
	VEntityUpdater<VUpdateablePart> m_PartUpdater;

	// setup camera
	VKeyboardCamera cam(input);
	cam.SetMovementSpeed(1);
	cam.GetCamera().Move(0, 0, 2.0f);
	cam.GetCamera().RotateY(180);
	cam.GetCamera().RotateZ(45);
	cam.GetCamera().RotateX(-80);

	VEntity::PartPtr pCameraPosPart(new VCameraPosPart(cam.GetCamera(), &m_PartUpdater));

	// get entity manager
	VEntityManagerPtr pEntityManager;

	// create sky entity
	IVEntityManager::EntityPtr pSkyEntity = CreateSkyEntity();
	pSkyEntity->AddPart(VFourCC("camp"), pCameraPosPart);
	pSkyEntity->Activate();
	pEntityManager->Add(pSkyEntity);

	// create heightmap entity
	IVEntityManager::EntityPtr pHeightmapEntity = CreateHeightmapEntity();
	pHeightmapEntity->Activate();
	pEntityManager->Add(pHeightmapEntity);

	VUpdateManagerPtr pUpdater;
	VSystemManagerPtr pSystem;
	pSystem->SetStatus(true);
	pUpdater->Start();
	while(pSystem->GetStatus())
	{
		m_PartUpdater.UpdateAll();
		m_GraphicsManager.UpdateAll();

		device.SetMatrix(IVDevice::ViewMatrix, cam.GetTransform());

		device.BeginScene();

		drawList.Render();

		device.EndScene();

		pUpdater->StartNextFrame();

		cam.Move(vfloat32(pUpdater->GetFrameDuration()) * 10);
	}
	pUpdater->Stop();

	return 0;
}

IVEntityManager::EntityPtr VRacerApp::CreateHeightmapEntity()
{
	VMeshPart* pMeshPart = new VMeshPart(&m_GraphicsManager);

    // create heightmap mesh
	VPointer< VHeightmapMesh<VTexturedVertex> >::SharedPtr pHeightmap
		= LoadHeightmap<VTexturedVertex>("/data/rocks.raw");
	pHeightmap->GenerateTexCoords();

	ForEachVertex(
		pHeightmap->GetVertexBuffer(), 
		ScaleVertex<VTexturedVertex>(200.0f, 200.0f, 50.0f));

	VEffectDescription hmeffect;
	VRenderPass& pass(hmeffect.AddShaderPath().AddRenderPass());

	VImageServicePtr pImageService;
	VImage image(2048, 2048, 24);
	pImageService->CreateImage("/data/rocks2048.tga", image);

	IVDevice::BufferHandle hTexBuffer = GetDevice().CreateBuffer(
		IVDevice::Texture,
		&image.GetData(),
		VBufferBase::DropData);

	VState textureState = TextureState(
		hTexBuffer,
		image.GetWidth(), image.GetHeight(),
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);
	pass.AddState(textureState);

	pass.AddState(DefaultColorState(VColor4f(1,1,1,1)));

	pMeshPart->AddMesh(BuildMesh(GetDevice(), *pHeightmap, hmeffect));

	// add detail texture
	VImage detailTex(512, 512, 24);
	pImageService->CreateImage("/data/detail.jpg", detailTex);

	IVDevice::BufferHandle hDetailTexBuffer = GetDevice().CreateBuffer(
		IVDevice::Texture,
		&detailTex.GetData(),
		VBufferBase::DropData);

	VState detailState = TextureState(
		hDetailTexBuffer,
		detailTex.GetWidth(), detailTex.GetHeight(),
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);

	VEffectDescription detailMat;
	VRenderPass& detPass = detailMat.AddShaderPath().AddRenderPass();
	detPass.AddState(detailState);
	detPass.AddState(DefaultColorState(VColor4f(1, 1, 1, .5)));
	detPass.AddState(DepthBufferState(DepthOnLessEqual, DepthTestEnabled, DepthReadOnly));
	detPass.AddState(BlendingState(BlendEnabled, BlendSourceColor, BlendDestColor));

	for(int i = 0; i < pHeightmap->GetVertexBuffer().GetSize(); ++i)
	{
		pHeightmap->GetVertexBuffer()[i].texCoords.u *= 5;
		pHeightmap->GetVertexBuffer()[i].texCoords.v *= 5;
	}

	pMeshPart->AddMesh(BuildMesh(GetDevice(), *pHeightmap, detailMat));

	IVEntityManager::EntityPtr pEntity(new VEntity());
	pEntity->AddPart(VFourCC("mesh"), VEntity::PartPtr(pMeshPart));
    return pEntity;	
}

IVEntityManager::EntityPtr VRacerApp::CreateSkyEntity()
{
	// build a wire frame sphere
	VEffectDescription wireFrame;
	VRenderPass& pass(wireFrame.AddShaderPath().AddRenderPass());
	pass.AddState(PolygonModeState(PMLine, PMLine));
	pass.AddState(DefaultColorState(VColor4f(0, .2f, 1, 1)));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthReadOnly));

    VPolarSphereMesh<VColoredVertex> sky(40, 40);
	sky.GenerateCoordinates();
	for(vuint i = 0; i < sky.GetVertexBuffer().GetSize(); ++i)
	{
		VColoredVertex& vertex(sky.GetVertexBuffer()[i]);
		
		vertex.color.red =		(vertex.position.y+1)/2.0f;
		vertex.color.green =	vertex.color.red;
		vertex.color.blue =		1.0f;
		vertex.color.alpha =	1.0f;

		std::swap(vertex.position.y, vertex.position.z);
	}

	ForEachVertex(sky.GetVertexBuffer(), ScaleVertex<VColoredVertex>(20.0f, 20.0f, 20.0f));

	VMeshPart* pSkyMeshPart = new VMeshPart(&m_GraphicsManager);
	pSkyMeshPart->AddMesh(VModel(BuildMesh(GetDevice(), sky, wireFrame)));

	IVEntityManager::EntityPtr pSkyEntity(new VEntity());
	pSkyEntity->AddPart(VFourCC("mesh"), VEntity::PartPtr(pSkyMeshPart));
	pSkyEntity->AddPart(VFourCC("body"), VEntity::PartPtr(new VRigidBodyPart()));
	return pSkyEntity;
}

	//{
	//	IVDevice::MeshHandle hUnitCubeMesh = 0;

	//	// create a box at the origin for orientation
	//	VBoxMesh<VSimpleVertex> unitCube(1.0f);
	//	unitCube.GenerateCoordinates();

	//	VEffectDescription redWire;
	//	VRenderPass& pass(redWire.AddShaderPath().AddRenderPass());
	//	pass.AddState(DefaultColorState(VColor4f(1, 0, 0, 1)));
	//	pass.AddState(PolygonModeState(PMLine, PMLine));
	//	pass.AddState(DepthBufferState(DepthAlways, DepthTestEnabled, DepthWrite));

	//	hUnitCubeMesh = BuildMesh(device, unitCube, redWire);
	//
	//	drawList.Add(VModel(hUnitCubeMesh));
	//}


namespace {
	VRacerApp g_RacerApp;
}