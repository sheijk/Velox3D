#include <v3d/Core.h>
#include <v3d/Updater.h>
#include <v3d/System.h>
#include <v3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Window.h>
#include <V3dLib/Property.h>
#include <V3dLib/Math.h>
#include <V3d/Input.h>
#include <V3d/Resource.h>

#include "VSwingFunction.h"

using namespace v3d;
using namespace v3d::system;
using namespace v3d::updater;
using namespace v3d::graphics;
using namespace v3d::window;
using namespace v3d::property;
using namespace v3d::math;
using namespace v3d::input;
using namespace v3d::resource;
using namespace v3d::image;

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
 * Note that this sample does not demonstrate the most convient way to write
 * a velox application. See the entity demo to see how to create an application
 * without the need for an extra module class
 * 
 * @author sheijk
 */
class VGraphicsDemoApp : public VVeloxApp
{
public:
	VGraphicsDemoApp();
	virtual ~VGraphicsDemoApp();

	/** The program's entry point */
	virtual vint Main(std::vector<std::string> args);

private:
	static void CreateResources();

	/** Creates a mesh for the moon */
	static IVDevice::MeshHandle CreateMoonMesh(IVDevice& device);

	/** Creates the mesh for the background stars */
	static IVDevice::MeshHandle CreateBackgroundMesh(IVDevice& device);

	/** Creates the mesh for the earth */
	IVDevice::MeshHandle CreateSphereMesh(
		IVDevice& device,
		const VEffectDescription& effect
		);

	/** Adds the day time pass for the earth to the effect description of the earth */
	static void AddDayPass(
		VEffectDescription& effect, 
		std::string daylightId);

	/** Adds a rendering pass for the clounds to the effect description */
	static void AddCloudPass(
		VEffectDescription& effect, 
		std::string textmatPropName);

	/** Adds a rendering pass for the night to the effect description */
	void AddNightPass(
		VEffectDescription& effect,
		std::string daytimeId);
};

namespace {
	VGraphicsDemoApp g_theApp;
}

VGraphicsDemoApp::VGraphicsDemoApp()
{
}

VGraphicsDemoApp::~VGraphicsDemoApp()
{
}

// constants to control the detail level
const int DETAIL_EARTH = 40;
const int DETAIL_BACKGROUND = 10;
const int DETAIL_MOON = 30;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

/** The main function. Will be called by the kernel when the application starts */
vint VGraphicsDemoApp::Main(std::vector<std::string> args)
{
	vout << "This is the velox demo application" << vendl;

	// create window
	VServicePtr<window::IVWindowManager> pWindowManager;

	VDisplaySettings displaySettings;
	displaySettings.SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	window::IVWindowManager::IVWindowPtr pWindow = 
		pWindowManager->QueryWindow(".v3d graphics demo", &displaySettings);
	IVDevice& device(pWindow->QueryGraphicsDevice());

	// create all resources. this step is not necessary in real world
	// applications because resources should be loaded using a resource file
	// (which is not implemented, yet ;))
	CreateResources();

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
	AddDayPass(effect, "@daytime");
	AddNightPass(effect, "@nighttime");
	AddCloudPass(effect, skyTexMatrix.GetRefId());

	PrintEffectDescription(effect);

	VResourceId earthres = VResourceManagerPtr()->GetResourceByName(
		"/data/earth");
	earthres->AddData(new VEffectDescription(effect));

	// create meshes for the earth, moon and background
	//IVDevice::MeshHandle hSphereMesh = CreateSphereMesh(device, effect);
	//IVDevice::MeshHandle hSkyMesh = CreateBackgroundMesh(device);
	//IVDevice::MeshHandle hMoonMesh = CreateMoonMesh(device);
	IVDevice::MeshHandle hSphereMesh = device.CreateMesh("/data/earth");
	IVDevice::MeshHandle hSkyMesh = device.CreateMesh("/data/sky");
	IVDevice::MeshHandle hMoonMesh = device.CreateMesh("/data/moon");

	IVDevice::MeshHandle hTriangle = device.CreateMesh("/test");

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
		//RenderMesh(device, hTriangle);

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

	vout << "Have a nice day" << vendl;
	return 0;
}

void AddFileNameResource(VResourceId in_Parent, 
						 VStringParam in_strResName, 
						 VStringParam in_strFileName)
{
	VResourceId res = in_Parent->AddSubResource(in_strResName);
	res->AddData<VFileName>(new VFileName(in_strFileName));
}

VEffectDescription CreateMoonEffect()
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

	VState textureState = TextureState("/textures/moon");

	pass.AddState(textureState);

	return effect;
}

VEffectDescription CreateBackgroundEffect()
{
	VEffectDescription effect;
	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());

	// setup some default states
	pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));

	pass.AddState(TextureState("/textures/sky"));

	return effect;
}

void VGraphicsDemoApp::CreateResources()
{
	resource::VResourceManagerPtr pResourceManager;

	VResourceId datares = pResourceManager->CreateResource("/data");

	// add clouds, day and night texture for earth
	AddFileNameResource(datares, "sky", "/data/sky.jpg");
	AddFileNameResource(datares, "day", "/data/day.jpg");
	AddFileNameResource(datares, "night", "/data/night.jpg");

	VResourceId textureRes = VResourceManagerPtr()->CreateResource("/textures/sky");
	textureRes->AddData(new VFileName("/data/stars.jpg"));

	// add test triangle resources
	{
		// add a test mesh
		VResourceId testres = pResourceManager->CreateResource("/test");
		
		VMeshDescription* pMD = new VMeshDescription();
		pMD->SetCoordinateResource("/test");
		VDataFormat format;
		format.SetCount(4);
		format.SetFirstIndex(0);
		format.SetStride(3);
		pMD->SetCoordinateFormat(format);

		pMD->SetIndexResource("/test/indices");
		pMD->SetIndexFormat(VDataFormat(0, 3, 0));
		testres->AddData(pMD);

		vfloat32 vertices[12] = {
			.0f, 1.0f, .0f,
			1.0f, -1.0f, .0f,
			.0f, .0f, .0f,
			-1.0f, -1.0f, .0f
		};

		VVertexBuffer* pVB = new VVertexBuffer(
			vertices,
			12,
			*pMD);
		testres->AddData(pVB);

		vuint indices[3] = {
			0, 1, 3
		};

		VVertexFormat indexFormat;
		indexFormat.SetIndexFormat(pMD->GetIndexFormat());
		testres->AddSubResource("indices")->AddData(new VVertexBuffer(indices, 3, indexFormat));

		VEffectDescription* pED = new VEffectDescription();
		VRenderPass& pass(pED->AddShaderPath().AddRenderPass());
		pass.AddState(DefaultColorState(VColor4f(1, 0, 0, 1)));
		pass.AddState(PolygonModeState(PMFilled, PMFilled));
		pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
		pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
		pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));

		testres->AddData(pED);
	}
    
	// create moon mesh and material
	{
		// add moon texture
		VResourceManagerPtr pResMan;
		VResourceId pRes = pResMan->CreateResource("/textures/moon");
		pRes->AddData(new VFileName("/data/moon.jpg"));

		//VResourceId moonres = datares->AddSubResource("moon");
		VPolarSphereMesh<VTexturedVertex> moon(DETAIL_MOON, DETAIL_MOON);
		moon.GenerateCoordinates();
		moon.GenerateTexCoords();
		ForEachVertex(moon.GetVertexBuffer(), ScaleVertex<VTexturedVertex>(0.175f, 0.175f, 0.175f));

		VResourceId moonres = BuildResource("/data/moon", moon);
		moonres->AddData(new VEffectDescription(CreateMoonEffect()));
	}

	// create sky mesh and material
	{
		// create a sphere mesh (see BuildSphereMesh)
		VPolarSphereMesh<VTexturedVertex> sky(DETAIL_BACKGROUND, DETAIL_BACKGROUND);
		sky.GenerateCoordinates();
		sky.GenerateTexCoords();
		// scale it by factor 10 by scaling each vertex of the sphere
		// see BuildSphereMesh
		ForEachVertex(sky.GetVertexBuffer(), ScaleVertex<VTexturedVertex>(10, 10, 10));

		VResourceId skyres = BuildResource("/data/sky", sky);
		skyres->AddData(new VEffectDescription(CreateBackgroundEffect()));

		//// load mesh into the device
		//return BuildMesh(device, sky, effect);
	}

	// create earth mesh and material
	{
		// create the geometry. note that you need to call the correct Generate..
		// methods depending on your vertex structure. see VPolarSphere's definition
		// for a list of supported generating functions
		VPolarSphereMesh<VTexturedVertex> sphere(DETAIL_EARTH, DETAIL_EARTH);
		sphere.GenerateCoordinates();
		sphere.GenerateTexCoords();
		// apply the given operation to every vertex of the mesh:
		ForEachVertex(sphere.GetVertexBuffer(), ScaleRandom<VTexturedVertex>(1.975f, 2.0f));
		ForEachVertex(sphere.GetVertexBuffer(), MirrorTexCoordV<VTexturedVertex>);

		VResourceId earthres = BuildResource("/data/earth", sphere);
		// effect description will be added in the Main function
	}
}

/** Adds the render pass for the daylight earth */
void VGraphicsDemoApp::AddDayPass(
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

	VState textureState = TextureState(
		// just to demonstrate the ".." and "." operators
		"/data/../data/./day",
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);

	// add texture coordinate matrix
	VMatrix44f identity;
	Identity(identity);
	textureState.SetParameter("matrix", identity);

	pass.AddState(textureState);
}

/** create the pass for the night planet */
void VGraphicsDemoApp::AddNightPass(
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

	VState textureState = TextureState(
		"/data/night",
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);
    
	pass.AddState(textureState);
}

/** Adds a rendering pass for the cloud layer */
void VGraphicsDemoApp::AddCloudPass(
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

	// create a texture state refering to the texture's resource name
	VState textureState = TextureState(
		"/data/sky",
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);

	// let the texture matrix for this texture reference the given property
	textureState.SetParameter("matrix", textmatPropName);

	pass.AddState(textureState);
}

///**
// * Returns the layout of the given vertex type. Use this function if you need
// * to resolve the type of a vertex without knowing it (in templates)
// */
//template<typename VertexStructure>
//VVertexDataLayout GetVertexLayout(VertexStructure&)
//{
//	return VertexStructure::layout;
//}
//
//template<typename GeometryProvider>
//VResourceId MakeResource(
//	GeometryProvider& in_Geom, 
//	VStringParam in_strResName,
//	VBufferBase::CopyMode in_CopyMode = VBufferBase::CopyData
//	)
//{
//	const std::string strResName(in_strResName);
//	const std::string vertexResName = strResName + "/vertices";
//	const std::string indexResName = strResName + "/indices";
//
//	// add vertices
//	VResourceId vertexRes = VResourceManagerPtr()->CreateResource(vertexResName);
//	vertexRes->AddData(new VByteBuffer(&in_Geom.GetVertexBuffer(), in_CopyMode));
//
//	// add indices
//	if( in_Geom.GetIndexBuffer().GetSize() > 0 )
//	{
//		VResourceId indexRes = VResourceManagerPtr()->CreateResource(indexResName);
//        indexRes->AddData(new VByteBuffer(&in_Geom.GetIndexBuffer(), in_CopyMode));
//	}
//
//	// create and add mesh description
//	VMeshDescription meshDescr;
//	VVertexDataLayout layout = GetVertexLayout(in_Geom.GetVertexBuffer()[0]);
//	VMeshDescription* io_pMeshDescr = &meshDescr;
//
//	// set vertex coord info
//	VDataFormat coordFormat;
//	coordFormat.SetFirstIndex(vuint(layout.positionOffset));
//	coordFormat.SetCount(cnVertexCount);
//	coordFormat.SetStride(vuint(layout.vertexSize / sizeof(vfloat32)));
//	io_pMeshDescr->SetCoordinateFormat(coordFormat);
//	io_pMeshDescr->SetCoordinateResource(vertexResName);
//
//	// set color info, if contained
//	if( VVertexDataLayout::IsValidOffset(layout.colorOffset) )
//	{
//		VDataFormat colorFormat;
//		colorFormat.SetFirstIndex(vuint(layout.colorOffset));
//		colorFormat.SetCount(cnVertexCount);
//		colorFormat.SetStride(vuint(layout.vertexSize / sizeof(vfloat32)));
//		io_pMeshDescr->SetColorFormat(colorFormat);
//		io_pMeshDescr->SetColorResource(vertexResName);
//	}
//
//	// set tex coord if contained
//	if( VVertexDataLayout::IsValidOffset(layout.texCoordOffset) )
//	{
//		VDataFormat texCoordFormat;
//		texCoordFormat.SetFirstIndex(vuint(layout.texCoordOffset));
//		texCoordFormat.SetCount(cnVertexCount);
//		texCoordFormat.SetStride(vuint(layout.vertexSize / sizeof(vfloat32)));
//		io_pMeshDescr->SetTexCoordFormat(0, texCoordFormat);
//		io_pMeshDescr->SetTexCoordFormat(0, vertexResName);
//	}
//
//	// set index info if contained
//	if( in_Geom.GetIndexBuffer().GetSize() > 0 )
//	{
//		io_pMeshDescr->SetIndexFormat(
//			VDataFormat(0, in_Geom.GetIndexBuffer().GetSize(), 1));
//		io_pMeshDescr->SetIndexResource(indexResName);
//	}
//
//	// add mesh descr to resource
//	VResourceId meshRes = VResourceManagerPtr()->GetResourceByName(strResName);
//	meshRes->AddData(new VMeshDescription(meshDescr));
//
//	return VResourceManagerPtr()->GetResourceByName(strResName);
//}

//-----------------------------------------------------------------------------
//TODO: explain module setup. (once it's final :)

//class VGraphicsDemoModule : public VModuleBase
//{
//	VPointer<VGraphicsDemoApp>::SharedPtr m_pApplication;
//
//public:
//	void Initialize();
//	void Shutdown();
//};
//
//void VGraphicsDemoModule::Initialize()
//{
//	m_pApplication.Assign(new VGraphicsDemoApp());
//}
//
//void VGraphicsDemoModule::Shutdown()
//{
//	m_pApplication.Release();
//}
//
//const char* v3d::GetModuleName()
//{
//	return "GraphicsDemoApp";
//}
//
//namespace {
//	VGraphicsDemoModule g_AppModule;
//}
