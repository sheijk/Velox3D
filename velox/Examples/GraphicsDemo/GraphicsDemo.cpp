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

/**
 * This is the Velox GraphicsDemo Example. 
 *
 * It demonstrates:
 * - creating and animating mesh materials using effect descriptions
 * - creating and rendering meshes using the graphics device
 * - usage of geometry generator templates (VeloxLib/Graphics/Generators)
 * - usage of model and view matrices to move models and camera around
 * - usage of system and update manager to create a mainloop and make animations'
 *   speed machine independent
 * 
 * @author sheijk
 */
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

/** Adds the render pass for the daylight earth */
void AddDayPass(
	IVDevice& device,
	VEffectDescription& effect, 
	std::string daylightId)
{
	// add one shader path with one pass and store a ref to the pass
	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());

	// add a default color (which will be used for all vertices if no vertex
	// colors are present)
	VState colorState("color");
	// add references to the daylight property. the given attributes will be
	// set to the property with the id of daylightId's value
	colorState.SetParameter("red", daylightId);
	colorState.SetParameter("green", daylightId);
	colorState.SetParameter("blue", daylightId);
	colorState.SetParameter("alpha", 1.0f);
	pass.AddState(colorState);

	// polygon modes set whether primitives are rendered filled (default),
	// as wireframe or as points. it's set for front and backside of polygons
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	// depth buffer settings: test function, enable/disable test, write to z-buffer
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	// mask out red, green, blue or alpha values when rendering?
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	// alpha blending settings. disable blending, source and dest factors
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));

	// load an image which will be converted to size 1024x512@24bit depth
	image::VImageServicePtr pImageService;
	image::VImage image(1024, 512, 24);
	pImageService->CreateImage("/data/day.jpg", image);

	// load it into the device
	IVDevice::BufferHandle hTexBuffer = device.CreateBuffer(
		IVDevice::Texture,
		&image.GetData(),
		VBufferBase::CopyData);

	// create a state which references the created texture buffer
	VState textureState = TextureState(
		hTexBuffer,
		image.GetWidth(), image.GetHeight(),
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);

	// add texture coordinate matrix
	VMatrix44f identity;
	Identity(identity);
	textureState.SetParameter("matrix", identity);

	pass.AddState(textureState);
}

/** create the pass for the night planet */
void AddNightPass(
	IVDevice& device,
	VEffectDescription& effect,
	std::string daytimeId)
{
	// add another pass to effect zero
	VRenderPass& pass(effect.ShaderPath(0).AddRenderPass());

	// add color state, and let the alpha value refer to the given property
	// name, which will update it to the properties value each time the
	// material is applied to the device
	VState colorState = DefaultColorState(VColor4f(1, 1, 1, 1));
	colorState.SetParameter("alpha", daytimeId);
	pass.AddState(colorState);

	// setup additive blending
	pass.AddState(BlendingState(BlendEnabled, BlendSourceAlpha, BlendDestColor));
	// render if <= z value, enable depth test, don't write new values
	pass.AddState(DepthBufferState(DepthOnLessEqual, DepthTestEnabled, DepthReadOnly));

	// load image and create texture and state (see AddDayState)
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

/** Adds a rendering pass for the cloud layer */
void AddCloudPass(
	IVDevice& device,
	VEffectDescription& effect, 
	std::string textmatPropName)
{
	// add another pass to the first shader path
	VRenderPass& pass(effect.ShaderPath(0).AddRenderPass());

	// create a color state. notice that a reference to a property is set 
	// using '@' and the property's name
	VState colorState = DefaultColorState(VColor4f(1, 1, 1, .8f));
	colorState.SetParameter("red", "@cloud.alpha");
	colorState.SetParameter("green", "@cloud.alpha");
	colorState.SetParameter("blue", "@cloud.alpha");
	pass.AddState(colorState);

	// see AddNightPass
	pass.AddState(BlendingState(BlendEnabled, BlendSourceAlpha, BlendDestAlpha));
	pass.AddState(DepthBufferState(DepthOnLessEqual, DepthTestEnabled, DepthReadOnly));

	// create texture from image and add state, see AddDayPass
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

	// let the texture matrix for this texture reference the given property
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

/** creates sphere geometry and loads it into the device */
IVDevice::MeshHandle CreateSphereMesh(
	IVDevice& device,
	const VEffectDescription& effect
	)
{
	// create the geometry. note that you need to call the correct Generate..
	// methods depending on your vertex structure. see VPolarSphere's definition
	// for a list of supported generating functions
	VPolarSphereMesh<VTexturedVertex> sphere(40, 40);
	sphere.GenerateCoordinates();
	sphere.GenerateTexCoords();
	// apply the given operation to every vertex of the mesh:
	ForEachVertex(sphere.GetVertexBuffer(), ScaleRandom<VTexturedVertex>(1.975f, 2.0f));
	ForEachVertex(sphere.GetVertexBuffer(), MirrorTexCoordV<VTexturedVertex>);

	// and finally load the mesh into the device
	IVDevice::MeshHandle hSphereMesh = 
		BuildMesh(device, sphere, effect);

	return hSphereMesh;
}

/** Creates the mesh for the background space */
IVDevice::MeshHandle CreateBackgroundMesh(IVDevice& device)
{
	VEffectDescription effect;
	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());

	// setup some default states
	pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));
	
	// create texture from file and load it into the device
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

	// create a sphere mesh (see BuildSphereMesh)
	VPolarSphereMesh<VTexturedVertex> sky(30, 30);
	sky.GenerateCoordinates();
	sky.GenerateTexCoords();
	// scale it by factor 10 by scaling each vertex of the sphere
	// see BuildSphereMesh
	ForEachVertex(sky.GetVertexBuffer(), ScaleVertex<VTexturedVertex>(10, 10, 10));

	// load mesh into the device
	return BuildMesh(device, sky, effect);
}

/** creates a mesh for the moon */
IVDevice::MeshHandle CreateMoonMesh(IVDevice& device)
{
	// see BuildSphereMesh

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

/**
 * A simple function. The value will move between min and max, each time it
 * is update it will change by diff * in_amout
 */
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

/** The main function. Will be called by the kernel when the application starts */
vint VGraphicsDemoApp::Main()
{
	vout << "This is the velox demo application" << vendl;

	// create window
	VServicePtr<window::IVWindowManager> pWindowManager;

	window::IVWindowManager::IVWindowPtr pWindow = 
		pWindowManager->QueryWindow(".v3d graphics demo");
	IVDevice& device(pWindow->QueryGraphicsDevice());

	// create properties. they are needed for animated material states
	// a state of a material can reference a property so the state will
	// be kept in sync with the value of the property. this way, material
	// states can be animated
	property::VProperty<VMatrix44f> skyTexMatrix("skytexmatrix");
	skyTexMatrix.Set(IdentityMatrix());
	VProperty<vfloat32> daytimeProperty("daytime");
	VProperty<vfloat32> nighttimProperty("nighttime");
	VProperty<vfloat32> cloudAlphaProperty("cloud.alpha");

	// create a three pass effect description
	VEffectDescription effect;
	AddDayPass(device, effect, "@daytime");
	AddNightPass(device, effect, "@nighttime");
	AddCloudPass(device, effect, skyTexMatrix.GetRefId());

	PrintEffectDescription(effect);

	// create meshes for the earth, moon and background
	IVDevice::MeshHandle hSphereMesh = CreateSphereMesh(device, effect);
	IVDevice::MeshHandle hSkyMesh = CreateBackgroundMesh(device);
	IVDevice::MeshHandle hMoonMesh = CreateMoonMesh(device);

	// setup camera, and apply it's matrix to the device
	VCamera cam;
	cam.MoveForward(-7);
	device.SetMatrix(IVDevice::ViewMatrix, *cam.GetMatrix());

	// get the escape key
	input::IVButton& escapeKey(pWindow->QueryInputManager().GetStandardKey(KeyEscape));

	// setup some matrices and values used in the render loop
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

	// init system and updater service
	VServicePtr<updater::IVUpdateManager> pUpdater;
	VServicePtr<system::IVSystemManager> pSystem;
	pSystem->SetStatus(true);

	pUpdater->Start();
	while(pSystem->GetStatus())
	{
		// prepare device for rendering (make gl context current etc)
		device.BeginScene();

		// update texture matrix and change property to update the clouds
		// texture matrix (animating the clouds)
		angle += (vfloat32)pUpdater->GetFrameDuration() * 2;
		while(angle >= 360.0f)
			angle -= 360.0f;
		texmat.Set(0, 3, angle / 360.0f);
		skyTexMatrix.Set(texmat);

		// update the daytime function
		daytimeVal.Update((vfloat32)pUpdater->GetFrameDuration());

		// calc daytime by clamping it to [0,1]
		vfloat32 daytime = daytimeVal.GetValue();
		if( daytime < 0 ) daytime = 0;
		if( daytime > 1 ) daytime = 1;
		daytimeProperty.Set(daytime);
		nighttimProperty.Set(1.0f - daytime);
		cloudAlphaProperty.Set(0.1f + .9f*daytime);

		// render the mesh (with 2 passes)
		device.SetMatrix(IVDevice::ModelMatrix, modelmat);
		RenderMesh(device, hSphereMesh);

		// render the sky
		device.SetMatrix(IVDevice::ModelMatrix, skyMatrix);
		RenderMesh(device, hSkyMesh);

		// setup matrix for moon to move it, then render moon
		Identity(	moonMatrix);
		Translate(	moonMatrix, 1.0f, 0.3f, 0.0f);
		RotateX(	moonMatrix, DegreeToRadian(-15));
		RotateZ(	moonMatrix, DegreeToRadian(20));
		RotateY(	moonMatrix, DegreeToRadian(angle * 5));
		Translate(	moonMatrix, 0, 0, 3);
		RotateY(	moonMatrix, DegreeToRadian(-angle * 5));

		device.SetMatrix(IVDevice::ModelMatrix, moonMatrix);

		RenderMesh(device, hMoonMesh);

		// end the scene (flip buffers etc)
		device.EndScene();

		// update object registered at update manager, calc duration of frame etc
		pUpdater->StartNextFrame();

		// exit if escape is pressed
		if( escapeKey.IsDown() )
		{
			pSystem->SetStatus(false);
		}
	}
	pUpdater->Stop();

	// release resources
	device.DeleteMesh(hSphereMesh);
	device.DeleteMesh(hSkyMesh);
	device.DeleteMesh(hMoonMesh);

	vout << "Have a nice day" << vendl;
	return 0;
}

//-----------------------------------------------------------------------------
//TODO: explain module setup. (once it's final :)

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