#include <v3d/Core.h>
#include <v3d/Updater.h>
#include <v3d/System.h>
#include <v3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Window.h>
#include <V3dLib/Property.h>
#include <V3dLib/Math.h>
#include <V3d/Input.h>

using namespace v3d;
using namespace v3d::system;
using namespace v3d::updater;
using namespace v3d::graphics;
using namespace v3d::window;
using namespace v3d::property;
using namespace v3d::math;
using namespace v3d::input;

class VGraphicsDemoApp : public IVApplication, public VNamedObject
{
public:
	VGraphicsDemoApp();
	virtual ~VGraphicsDemoApp();

	virtual vint Main();

private:
};

VGraphicsDemoApp::VGraphicsDemoApp() : VNamedObject("main", 0)
{
}

VGraphicsDemoApp::~VGraphicsDemoApp()
{
}

void AddDayPass(
	IVDevice& device,
	VEffectDescription& effect, 
	std::string greenPropertyName)
{
	// add one shader path with one pass and store a ref to the pass
	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());

	//pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
	VState colorState("color");
	colorState.SetParameter("red", greenPropertyName);
	colorState.SetParameter("green", greenPropertyName);
	colorState.SetParameter("blue", greenPropertyName);
	colorState.SetParameter("alpha", 1.0f);
	pass.AddState(colorState);

	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));

	image::VImageServicePtr pImageService;
	image::VImage image(1024, 512, 24);
	pImageService->CreateImage("/data/day.jpg", image);

	IVDevice::BufferHandle hTexBuffer = device.CreateBuffer(
		IVDevice::Texture,
		&image.GetData(),
		VBufferBase::CopyData);

	VState textureState = TextureState(
		hTexBuffer,
		image.GetWidth(), image.GetHeight(),
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);

	VMatrix44f identity;
	Identity(identity);
	textureState.SetParameter("matrix", identity);

	pass.AddState(textureState);
}

void AddNightPass(
	IVDevice& device,
	VEffectDescription& effect,
	std::string daytimeId)
{
	VRenderPass& pass(effect.ShaderPath(0).AddRenderPass());

	VState colorState = DefaultColorState(VColor4f(1, 1, 1, 1));
	colorState.SetParameter("alpha", daytimeId);
	pass.AddState(colorState);

	pass.AddState(BlendingState(BlendEnabled, BlendSourceAlpha, BlendDestColor));
	pass.AddState(DepthBufferState(DepthOnLessEqual, DepthTestEnabled, DepthReadOnly));

	image::VImageServicePtr pImageService;
	image::VImage image(1024, 512, 24);
	pImageService->CreateImage("/data/night.jpg", image);

	IVDevice::BufferHandle hTexBuffer = device.CreateBuffer(
		IVDevice::Texture,
		&image.GetData(),
		VBufferBase::DropData);

	VState textureState = TextureState(
		hTexBuffer,
		image.GetWidth(), image.GetHeight(),
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);
	pass.AddState(textureState);
}

void AddCloudPass(
	IVDevice& device,
	VEffectDescription& effect, 
	std::string textmatPropName)
{
	VRenderPass& pass(effect.ShaderPath(0).AddRenderPass());

	VState colorState = DefaultColorState(VColor4f(1, 1, 1, .8f));
	colorState.SetParameter("red", "@cloud.alpha");
	colorState.SetParameter("green", "@cloud.alpha");
	colorState.SetParameter("blue", "@cloud.alpha");
	//colorState.SetParameter("alpha", "@cloud.alpha");
	pass.AddState(colorState);
	//pass.AddState(PolygonModeState(PMLine, PMLine));
	//pass.AddState(BlendingState(BlendEnabled, BlendSourceAlpha, BlendDestColor));
	pass.AddState(BlendingState(BlendEnabled, BlendSourceAlpha, BlendDestAlpha));
	pass.AddState(DepthBufferState(DepthOnLessEqual, DepthTestEnabled, DepthReadOnly));

	image::VImageServicePtr pImageService;
	image::VImage image(1024, 512, 24);
	pImageService->CreateImage("/data/sky.jpg", image);

	IVDevice::BufferHandle hTexBuffer = device.CreateBuffer(
		IVDevice::Texture,
		&image.GetData(),
		VBufferBase::DropData);

	VState textureState = TextureState(
		hTexBuffer,
		image.GetWidth(), image.GetHeight(),
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);

	textureState.SetParameter("matrix", textmatPropName);

	pass.AddState(textureState);
}

template<typename VertexStructure>
void MirrorTexCoordU(VertexStructure& vertex)
{
	vertex.texCoords.u = 1 - vertex.texCoords.u;
}

template<typename VertexStructure>
void MirrorTexCoordV(VertexStructure& vertex)
{
	vertex.texCoords.v = 1 - vertex.texCoords.v;
}

template<typename VertexStructure>
void SwitchTextCoordUV(VertexStructure& vertex)
{
	vfloat32 u = vertex.texCoords.u;
	vertex.texCoords.u = vertex.texCoords.v;
	vertex.texCoords.v = u;
}

IVDevice::MeshHandle CreateSphereMesh(
	IVDevice& device,
	const VEffectDescription& effect
	)
{
	VPolarSphereMesh<VTexturedVertex> sphere(40, 40);
	sphere.GenerateCoordinates();
	sphere.GenerateTexCoords();
	ForEachVertex(sphere.GetVertexBuffer(), ScaleRandom<VTexturedVertex>(1.975f, 2.0f));
	ForEachVertex(sphere.GetVertexBuffer(), MirrorTexCoordV<VTexturedVertex>);
	IVDevice::MeshHandle hSphereMesh = 
		BuildMesh(device, sphere, effect);

	return hSphereMesh;
}

IVDevice::MeshHandle CreateBackgroundMesh(IVDevice& device)
{
	VEffectDescription effect;
	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());

	pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));
	
	image::VImageServicePtr pImageService;
	image::VImage image(1024, 512, 24);
	pImageService->CreateImage("/data/stars.jpg", image);

	IVDevice::BufferHandle hTexBuffer = device.CreateBuffer(
		IVDevice::Texture,
		&image.GetData(),
		VBufferBase::DropData);

	VState textureState = TextureState(
		hTexBuffer,
		image.GetWidth(), image.GetHeight(),
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);

	pass.AddState(textureState);

	VPolarSphereMesh<VTexturedVertex> sky(30, 30);
	sky.GenerateCoordinates();
	sky.GenerateTexCoords();
	ForEachVertex(sky.GetVertexBuffer(), ScaleVertex<VTexturedVertex>(10, 10, 10));

	return BuildMesh(device, sky, effect);
}

IVDevice::MeshHandle CreateMoonMesh(IVDevice& device)
{
	VEffectDescription effect;
	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());

	pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));
	
	image::VImageServicePtr pImageService;
	image::VImage image(512, 256, 24);
	pImageService->CreateImage("/data/moon.jpg", image);

	IVDevice::BufferHandle hTexBuffer = device.CreateBuffer(
		IVDevice::Texture,
		&image.GetData(),
		VBufferBase::DropData);

	VState textureState = TextureState(
		hTexBuffer,
		image.GetWidth(), image.GetHeight(),
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);

	pass.AddState(textureState);

	VPolarSphereMesh<VTexturedVertex> moon(30, 30);
	moon.GenerateCoordinates();
	moon.GenerateTexCoords();
	ForEachVertex(moon.GetVertexBuffer(), ScaleVertex<VTexturedVertex>(0.175f, 0.175f, 0.175f));

	return BuildMesh(device, moon, effect);
}

class VSwingFunction
{
	vfloat32 m_fValue;
	vfloat32 m_fDifference;

	const vfloat32 m_fMin;
	const vfloat32 m_fMax;

public:
	VSwingFunction(vfloat32 diff, vfloat32 minval, vfloat32 maxval)
		: m_fDifference(diff), m_fMin(minval), m_fMax(maxval)
	{
		m_fValue = (m_fMax+m_fMin)/2.0f;

		V3D_ASSERT(m_fMin <= m_fValue);
		V3D_ASSERT(m_fValue <= m_fMax);
	}

	vfloat32 GetValue() const { return m_fValue; }

	void Update(vfloat32 in_fAmount)
	{
		m_fValue += in_fAmount * m_fDifference;

		if( m_fMax < m_fValue )
		{
			m_fDifference = - m_fDifference;
			m_fValue = m_fMax;
		}
		else if( m_fValue < m_fMin ) 
		{
			m_fDifference = - m_fDifference;
			m_fValue = m_fMin;
		}

		V3D_ASSERT(m_fMin <= m_fValue);
		V3D_ASSERT(m_fValue <= m_fMax);
	}
};

vint VGraphicsDemoApp::Main()
{
	vout << "This is the velox demo application" << vendl;

	// create window
	VServicePtr<window::IVWindowManager> pWindowManager;

	window::IVWindowManager::IVWindowPtr pWindow = 
		pWindowManager->QueryWindow(".v3d graphics demo");
	IVDevice& device(pWindow->QueryGraphicsDevice());

	// create properties
	property::VProperty<VMatrix44f> skyTexMatrix("skytexmatrix");
	skyTexMatrix.Set(IdentityMatrix());
	VProperty<vfloat32> daytimeProperty("daytime");
	VProperty<vfloat32> nighttimProperty("nighttime");
	VProperty<vfloat32> cloudAlphaProperty("cloud.alpha");

	// create a two pass effect description
	VEffectDescription effect;
	AddDayPass(device, effect, "@daytime");
	AddNightPass(device, effect, "@nighttime");
	AddCloudPass(device, effect, skyTexMatrix.GetRefId());

	PrintEffectDescription(effect);

	// create a sphere using the material effect
	IVDevice::MeshHandle hSphereMesh = CreateSphereMesh(device, effect);

	IVDevice::MeshHandle hSkyMesh = CreateBackgroundMesh(device);
	IVDevice::MeshHandle hMoonMesh = CreateMoonMesh(device);

	// display it
	VCamera cam;
	cam.MoveForward(-7);

	VServicePtr<updater::IVUpdateManager> pUpdater;
	VServicePtr<system::IVSystemManager> pSystem;
	pSystem->SetStatus(true);

	input::IVButton& escapeKey(pWindow->QueryInputManager().GetStandardKey(KeyEscape));

	VMatrix44f texmat;
	Identity(texmat);
	vfloat32 angle = 0;

	VMatrix44f modelmat;
	Identity(modelmat);
	math::Translate(modelmat, 1.0f, 0.3f, 0.0f);
	math::RotateX(modelmat, DegreeToRadian(-20));
	math::RotateY(modelmat, DegreeToRadian(-30));

	VMatrix44f skyMatrix;
	Identity(skyMatrix);
	RotateZ(skyMatrix, DegreeToRadian(-30));
	RotateY(skyMatrix, DegreeToRadian(90));
	
	VMatrix44f moonMatrix;

	VSwingFunction daytimeVal(.5f, -3.0f, 4.0f);

	pUpdater->Start();
	while(pSystem->GetStatus())
	{
		device.BeginScene();
		device.SetMatrix(IVDevice::ViewMatrix, *cam.GetMatrix());

		// update texture matrix and change property
		angle += (vfloat32)pUpdater->GetFrameDuration() * 2;
		while(angle >= 360.0f)
			angle -= 360.0f;
		daytimeVal.Update((vfloat32)pUpdater->GetFrameDuration());
		//vout << "time=" << pUpdater->GetFrameDuration();
		//vout << " green=" << greenVal.GetValue() << vendl;

		texmat.Set(0, 3, angle / 360.0f);

		skyTexMatrix.Set(texmat);
		vfloat32 daytime = daytimeVal.GetValue();
		if( daytime < 0 ) daytime = 0;
		if( daytime > 1 ) daytime = 1;
		daytimeProperty.Set(daytime);
		nighttimProperty.Set(1.0f - daytime);
		cloudAlphaProperty.Set(0.1f + .9f*daytime);

		device.SetMatrix(IVDevice::ModelMatrix, modelmat);

		// render the mesh (with 2 passes)
		RenderMesh(device, hSphereMesh);

		device.SetMatrix(IVDevice::ModelMatrix, skyMatrix);
		RenderMesh(device, hSkyMesh);

		Identity(	moonMatrix);
		Translate(	moonMatrix, 1.0f, 0.3f, 0.0f);
		RotateX(	moonMatrix, DegreeToRadian(-15));
		RotateZ(	moonMatrix, DegreeToRadian(20));
		RotateY(	moonMatrix, DegreeToRadian(angle * 5));
		Translate(	moonMatrix, 0, 0, 3);
		//RotateY(	moonMatrix, DegreeToRadian(90));
		RotateY(	moonMatrix, DegreeToRadian(-angle * 5));

		device.SetMatrix(IVDevice::ModelMatrix, moonMatrix);

		RenderMesh(device, hMoonMesh);

		device.EndScene();

		pUpdater->StartNextFrame();

		if( escapeKey.IsDown() )
		{
			pSystem->SetStatus(false);
		}
	}
	pUpdater->Stop();

	device.DeleteMesh(hSphereMesh);

	vout << "Have a nice day" << vendl;
	return 0;
}

//-----------------------------------------------------------------------------

class VGraphicsDemoModule : public VModuleBase
{
	VPointer<VGraphicsDemoApp>::SharedPtr m_pApplication;

public:
	void Initialize();
	void Shutdown();
};

void VGraphicsDemoModule::Initialize()
{
	m_pApplication.Assign(new VGraphicsDemoApp());
}

void VGraphicsDemoModule::Shutdown()
{
	m_pApplication.Release();
}

const char* v3d::GetModuleName()
{
	return "GraphicsDemoApp";
}

namespace {
	VGraphicsDemoModule g_AppModule;
}