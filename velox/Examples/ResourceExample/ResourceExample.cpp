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

class ResourceExample : public VVeloxApp
{
public:
	ResourceExample();

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
const std::string APP_NAME = "ResourceExample";

void AddAllMeshes(VResourceId in_pResource, IVDrawList& io_DrawList, vuint* out_pCount = 0);

//-----------------------------------------------------------------------------

/**
 * @author sheijk
 */
vint ResourceExample::Main(std::vector<std::string> args)
{
	Init();
	CreateResources();

	VSimpleDrawList drawList(Device());
	AddAllMeshes(VResourceManagerPtr()->GetResourceByName("/skybox"), drawList);

	vfloat32 angle = 0.0f;

	VCamera cam;
	cam.MoveForward(-7);
	Device().SetMatrix(IVDevice::ViewMatrix, *cam.GetMatrix());

	m_pUpdater->Start();
	while(m_pSystem->GetStatus())
	{
		// update
		angle += m_pUpdater->GetFrameDuration() * 360;

		// render
		Device().BeginScene();

		drawList.Render();

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

ResourceExample::ResourceExample()
{
	m_pWindow.Assign(0);
	m_pDevice = 0;
	m_pEscapeKey = 0;
}

void ResourceExample::Init()
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

void ResourceExample::Shutdown()
{
	m_pDevice = 0;
	m_pWindow.Release();
	m_pEscapeKey = 0;
}

void AddAllMeshes(VResourceId in_pResource, IVDrawList& io_DrawList, vuint* out_pCount)
{
	try
	{
		IVDevice::MeshHandle hMesh =
			io_DrawList.GetDevice().CreateMesh(in_pResource->GetQualifiedName().c_str());
		IVDevice::MaterialHandle hMaterial =
			io_DrawList.GetDevice().CreateMaterial(in_pResource->GetQualifiedName().c_str());

		io_DrawList.Add(VModelMesh(hMesh, hMaterial));

		if( out_pCount != 0 )
			*out_pCount += 1;
	}
	catch(const VResourceException&)
	{}

	VRangeIterator<VResource> child = in_pResource->ChildIterator();
	while(child.HasNext())
	{
		AddAllMeshes(&*child, io_DrawList, out_pCount);
		++child;
	}
}

void CreateQuad(VResourceId in_pResource,
				VVector3f pos,
				VVector3f xaxis,
				VVector3f yaxis)
{
	// create quad vertices
	VVertexFormat vertexFormat(
		VVertexFormat::Coordinates | VVertexFormat::TexCoords | VVertexFormat::Normals,
		4, 
		0);

	VVertexBuffer* pVertices = new VVertexBuffer(vertexFormat);

	pVertices->SetCoordinate(pos, 0);
	pVertices->SetCoordinate(pos + xaxis, 1);
	pVertices->SetCoordinate(pos + xaxis + yaxis, 2);
	pVertices->SetCoordinate(pos + yaxis, 3);

	pVertices->SetTexCoord(0, 0, VTexCoord2f(1, 1));
	pVertices->SetTexCoord(0, 1, VTexCoord2f(0, 1));
	pVertices->SetTexCoord(0, 2, VTexCoord2f(0, 0));
	pVertices->SetTexCoord(0, 3, VTexCoord2f(1, 0));

	VNormal3f normal(Normalized(Cross(xaxis, yaxis)));
	for(vuint i = 0; i < 4; ++i)
		pVertices->SetNormal(normal, i);

	// create mesh description
	VMeshDescription* pMeshDescription = new VMeshDescription(vertexFormat);
	pMeshDescription->SetGeometryType(VMeshDescription::Quads);
	pMeshDescription->SetCoordinateResource(in_pResource->GetQualifiedName());
	pMeshDescription->SetTexCoordResource(0, in_pResource->GetQualifiedName());
	pMeshDescription->SetNormalResource(in_pResource->GetQualifiedName());

	// add data
	in_pResource->AddData(pMeshDescription);
	in_pResource->AddData(pVertices);
}

VEffectDescription MakeSkyBoxEffect(const std::string& in_strTextureName)
{
	VEffectDescription effect;

	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());
	pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthReadOnly));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));
	VState textureState = TextureState(
		in_strTextureName.c_str(),
		FilterLinear, FilterLinear,
		TextureClampToEdge, TextureClampToEdge);
	pass.AddState(textureState);

	return effect;
}

void CreateSkyBoxResource(VResourceId in_pResource, const std::string& in_strTexturePath)
{
	const vfloat32 size = 7;
	const vfloat32 diameter = 2*size;

	// create vertex buffer
	VResourceId resNegZ = in_pResource->AddSubResource("negz");
	CreateQuad(resNegZ, 
		VVector3f(-size, -size, -size), VVector3f(diameter, 0, 0), VVector3f(0, diameter, 0));
	resNegZ->AddData(new VEffectDescription(MakeSkyBoxEffect((in_strTexturePath + "/negz.jpg").c_str())));

	VResourceId resNegX = in_pResource->AddSubResource("negx");
	CreateQuad(resNegX, 
		VVector3f(-size, -size, size), VVector3f(0, 0, -diameter), VVector3f(0, diameter, 0));
	resNegX->AddData(new VEffectDescription(MakeSkyBoxEffect((in_strTexturePath + "/negx.jpg").c_str())));

	VResourceId resPosX = in_pResource->AddSubResource("posx");
	CreateQuad(resPosX, 
		VVector3f(size, -size, -size), VVector3f(0, 0, diameter), VVector3f(0, diameter, 0));
	resPosX->AddData(new VEffectDescription(MakeSkyBoxEffect((in_strTexturePath + "/posx.jpg").c_str())));

	VResourceId resNegY = in_pResource->AddSubResource("negy");
	CreateQuad(resNegY, 
		VVector3f(size, -size, -size), VVector3f(-diameter, 0, 0), VVector3f(0, 0, diameter));
	resNegY->AddData(new VEffectDescription(MakeSkyBoxEffect((in_strTexturePath + "/negy.jpg").c_str())));

	VResourceId resPosY = in_pResource->AddSubResource("posy");
	CreateQuad(resPosY, 
		VVector3f(size, size, size), VVector3f(-diameter, 0, 0), VVector3f(0, 0, -diameter));
	resPosY->AddData(new VEffectDescription(MakeSkyBoxEffect((in_strTexturePath + "/posy.jpg").c_str())));

	VResourceId resPosZ = in_pResource->AddSubResource("posz");
	CreateQuad(resPosZ, 
		VVector3f(size, -size, size), VVector3f(-diameter, 0, 0), VVector3f(0, diameter, 0));
	resPosZ->AddData(new VEffectDescription(MakeSkyBoxEffect((in_strTexturePath + "/posz.jpg").c_str())));
}

VVertexBuffer* CreateSphere(VVertexFormat::DataTypes in_DataTypes, 
							vuint in_nRings, vuint in_nSectors,
							vfloat32 in_fBottom = -1.0f, vfloat32 in_fTop = 1.0f)
{
	in_DataTypes = in_DataTypes | VVertexFormat::Indices;
	const vuint vertexCount = in_nSectors * in_nRings;
	const vuint indexCount = 2 * (in_nSectors+1) * in_nRings;
	VVertexFormat format(in_DataTypes, vertexCount, indexCount);
	VVertexBuffer* pVertexBuffer = new VVertexBuffer(format);

	using namespace std;

	const float pi = 3.141592654f;

	const float deltaAngle = 2 * pi / in_nSectors;
	const float height = in_fTop - in_fBottom;
	const float deltaY = height / (in_nRings-1);

	// generate indices
	//for(vuint index = 0; index < geometry.GetIndexBuffer().GetSize(); ++index)
	for(vuint index = 0; index < indexCount; ++index)
	{
		pVertexBuffer->SetIndex(0, index);
	}

	vuint indexNum = 0;

	for(vuint ring = 0; ring < in_nRings-1; ++ring)
	{
		for(vuint sector = 0; sector < in_nSectors; ++sector)
		{
			pVertexBuffer->SetIndex(ring * in_nSectors + sector, indexNum);
			++indexNum;
			pVertexBuffer->SetIndex((ring+1) * in_nSectors + sector, indexNum);
			++indexNum;
		}
		pVertexBuffer->SetIndex(ring * in_nSectors + 0, indexNum);
		++indexNum;
		pVertexBuffer->SetIndex((ring+1) * in_nSectors + 0, indexNum);
		++indexNum;
	}

	// generate vertices
	float angle = 0;
	for(vuint sector = 0; sector < in_nSectors; ++sector, angle += deltaAngle)
	{
		const float xpos = cos(angle);
		const float zpos = sin(angle);

		float ypos = in_fBottom;
		int ring = 0;
		for(vuint ring = 0; ring < in_nRings; ++ring, ypos += deltaY)
		{
			const float scale = sqrt(1 - ypos*ypos);

			vuint vertexNum = ring * in_nSectors + sector;

			VVector3f pos;
			pos.SetX(xpos * scale);
			pos.SetY(ypos);
			pos.SetZ(zpos * scale);

			if( in_DataTypes & VVertexFormat::Coordinates )
				pVertexBuffer->SetCoordinate(pos, vertexNum);

			VNormal3f normal(Normalized(pos));
			if( in_DataTypes & VVertexFormat::Normals )
				pVertexBuffer->SetNormal(normal, vertexNum);
		}
	}

	return pVertexBuffer;
}

void ResourceExample::CreateResources()
{
	CreateSkyBoxResource(VResourceManagerPtr()->CreateResource("/skybox"), "/data/skybox");
}

IVDevice& ResourceExample::Device()
{
	V3D_ASSERT(m_pDevice != 0);

	return *m_pDevice;
}

//-----------------------------------------------------------------------------
namespace {
	ResourceExample g_theApp;
}
