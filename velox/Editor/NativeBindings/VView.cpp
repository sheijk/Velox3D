#include "VView.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3dLib/Math.h>
#include <V3d/Resource.h>
#include <V3d/Core/VException.h>
#include "../../Source/Graphics/OpenGL/Context/VWin32WindowContext.h"
#include "../../Source/Graphics/OpenGL/VOpenGLDevice.h"

#include <iostream>
#include <functional>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d::graphics;
using namespace v3d::resource;
using namespace v3d::math;
using namespace v3d::scene;
using namespace v3d::entity;
using namespace std;

VSharedPtr<VView> VView::s_pInstance;

VView::VView()
{
	m_Thread = 0;
	
	cout << "Creating view for hwnd... " << endl;

	// start rendering
	try {		
		m_Thread = glfwCreateThread(VView::FrameUpdateLoop, this);	
				
		cout << "done" << endl;	
	} catch(VException& e) {
		cout << endl
			<< "Error: "
			<< e.GetErrorString() << endl
			<< e.GetErrorFile() << ":" << e.GetErrorLine() << endl;
	} catch(...) {
		cout << "Unknown exception occured" << endl;
	}
}

VView::~VView()
{
}

void VView::FrameUpdateLoop(void* arg)
{
	VView* pView = reinterpret_cast<VView*>(arg);
	
	pView->FrameUpdateLoop();
}

void VView::FrameUpdateLoop()
{
	using std::for_each;
	using std::mem_fun;
	
	vfloat32 delay = 1.0f;
	
	// initialize
	for_each(m_FrameActions.begin(), m_FrameActions.end(),
		mem_fun<void, IVFrameAction>(&IVFrameAction::Init));
		
	while( IsRunning() )
	{
		// add all new actions
		for(FrameActions::iterator newAction = m_NewFrameActions.begin();
			newAction != m_NewFrameActions.end(); ++newAction)
		{
			(*newAction)->Init();
			
			m_FrameActions.push_back(*newAction);
		}
		
		for_each(m_FrameActions.begin(), m_FrameActions.end(), mem_fun<void, IVFrameAction>(&IVFrameAction::UpdateFrame));
			
		// tell all frame actions to execute
		FrameActions::iterator actionIter = m_FrameActions.begin();
		
		try
		{
			delay = 1.0 / property::GetProperty<double>("editor.fps");
		}
		catch(VException&) 
		{
			property::SetProperty<double>("editor.fps", 20.0);
			delay = 1.0 / 20.0;
		}
		
		// sleep for n seconds
		glfwSleep(delay);
	}
	
	// tell actions that the main loop ended
	for_each(m_FrameActions.begin(), m_FrameActions.end(), 
		mem_fun<void, IVFrameAction>(&IVFrameAction::Shutdown));
	
	cout << "Finished rendering" << endl;	
}

void VView::Start()
{
	m_bIsRunning = true;
}

void VView::Stop()
{
	m_bIsRunning = false;
}

VView* VView::GetInstance()
{
	if( s_pInstance.Get() == 0 )
	{
		s_pInstance.Assign(new VView());
	}
	
	return s_pInstance.Get();
}

void VView::Add(IVFrameAction* in_pTestAction)
{
	m_NewFrameActions.push_back(in_pTestAction);
}

//-----------------------------------------------------------------------------

void VTestFrameAction::Init()
{
	cout << "VTestFrameAction::Init()" << endl;
}

void VTestFrameAction::Shutdown()
{
	cout << "VTestFrameAction::Shutdown()" << endl;
}

void VTestFrameAction::UpdateFrame()
{
	++m_nCount;
	
	if( m_nCount > 100 )
	{
		cout << "VTestFrameAction::UpdateFrame: VView updating working" << endl;
		
		m_nCount = 0;
	}
}

//-----------------------------------------------------------------------------

VRenderFrameAction::VRenderFrameAction(VNativeWindowHandle in_Hwnd)
{
	m_pShooting = 0;
	m_HWND = HWND(in_Hwnd);		

	cout << "\tCreating display settings" << endl;
	VDisplaySettings settings;
	settings.SetWidth(200);
	settings.SetHeight(200);
	settings.SetPosition(0, 0);
	
	cout << "\tCreating context" << endl;
	IVRenderContext* pContext(new VWin32WindowContext(m_HWND, &settings));
	
	cout << "\tCreating device" << endl;
	m_pDevice.Assign(new VOpenGLDevice(settings, pContext));
}

void VRenderFrameAction::Init()
{
}

void VRenderFrameAction::Shutdown()
{
}

#include <V3d/OpenGL.h>

void VRenderFrameAction::UpdateFrame()
{
	m_pDevice->BeginScene();
	
//	glMatrixMode(GL_MODELVIEW);
//	glPushMatrix();
//	glTranslatef(.0f, .0f, -1.0f);
//	glBegin(GL_TRIANGLES);
//	glColor3f(1.0f, 1.0f, .0f);
//	glVertex2f(1.0f, .0f);
//	glVertex2f(-1.0f, .0f);
//	glVertex2f(.0f, 1.0f);
//	glEnd();
//	glPopMatrix();
	
	if( m_pShooting != 0 )
	{
		m_pShooting->Cull();
		m_pShooting->Render();
	}
	
	m_pDevice->EndScene();
}

void VRenderFrameAction::SetShooting(v3d::scene::IVShooting* in_pShooting)
{
	m_pShooting = in_pShooting;
}

v3d::graphics::IVDevice* VRenderFrameAction::GetDevice()
{
	return m_pDevice.Get();
}

//-----------------------------------------------------------------------------

/*
void DeHomogenize(VVector3f* out_Vec3f, const VVector4f& in_Vec4f)
{
	float w = in_Vec4f.Get(3);

	if( w != 1.0f )
	{
		for(int i = 0; i < 3; ++i)
			out_Vec3f->Set(i, in_Vec4f.Get(i) / w);
	}
	else
	{
		for(int i = 0; i < 3; ++i)
			out_Vec3f->Set(i, in_Vec4f.Get(i));
	}
}

template<typename T>
class scope_ptr
{
	T* ptr;

	void release()
	{
		if( ptr != 0 )
			delete ptr;
		ptr = 0;
	}

public:
	scope_ptr(T* t) : ptr(t) {}
	~scope_ptr() { release(); }

	void operator=(T* t)
	{
		Release();
		ptr = t;
	}

	T* operator->() { return ptr; }
	const T* operator->() const { return ptr; }
	T& operator*() { return *ptr; }
	const T& operator*() const { return *ptr; }

	T* drop() {
		T* t = ptr;
		ptr = 0;
		return t;
	}
};


/*
VMeshDescription* CreateMeshDescription(
	VMeshDescription::GeometryType in_Primitives,
	VVertexBuffer& in_VertexBuffer,
	const std::string& in_strVBResource,
	const std::string& in_strIndexResource)
{
	VVertexFormat format(in_VertexBuffer.GetFormat());

	scope_ptr<VMeshDescription> pMeshDescription(new VMeshDescription(format));

	pMeshDescription->SetGeometryType(in_Primitives);

	if( format.GetColorFormat().GetCount() > 0 )
	{
        pMeshDescription->SetColorResource(in_strVBResource);
	}

	if( format.GetCoordinateFormat().GetCount() > 0 )
	{
		pMeshDescription->SetCoordinateResource(in_strVBResource);
	}

	if( format.GetIndexFormat().GetCount() > 0 )
	{
		pMeshDescription->SetIndexResource(in_strIndexResource);
	}

	if( format.GetNormalFormat().GetCount() > 0 )
	{
		pMeshDescription->SetNormalResource(in_strVBResource);
	}

	for( int texcoord = 0; texcoord < format.GetTexCoordCount(); ++texcoord)
	{
		if( format.GetTexCoordFormat(texcoord).GetCount() > 0 )
		{
			pMeshDescription->SetTexCoordResource(texcoord, in_strVBResource);
		}
	}

	return pMeshDescription.drop();
}

VMeshDescription* CreateMeshDescription(
	VMeshDescription::GeometryType in_Primitives,
	VVertexBuffer& in_VertexBuffer,
	const std::string& in_strVBResource)
{
	return CreateMeshDescription(
		in_Primitives,
		in_VertexBuffer,
		in_strVBResource,
		in_strVBResource);
}

VVertexBuffer* CreateTorus(
	VVertexFormat::DataTypes in_Types,
	float in_fPipeRadius, 
	int in_nRings, int in_nSegments)
{
	// enable an index buffer
	in_Types = in_Types | VVertexFormat::Indices;

	// calculate number of vertices
	const int vertexCount = in_nRings * in_nSegments;
	const int indexCount = 2 * vertexCount;

	scope_ptr<VVertexBuffer> pVB(new VVertexBuffer(VVertexFormat(in_Types, vertexCount, indexCount)));

	for(int i = 0; i < vertexCount; ++i)
	{
		pVB->SetCoordinate(VVector3f(0, 0, 0), i);
	}

	std::vector<VVector4f> ringPos;
	ringPos.resize(in_nSegments);
	std::vector<VVector4f> ringNormals;
	ringNormals.resize(in_nSegments);

	// calculate first ring and normals
	for(int segment = 0; segment < in_nSegments; ++segment)
	{
		float angle = Pi() * 2.0f * float(segment) / float(in_nSegments);

		ringPos[segment].Set(0, sin(angle) * in_fPipeRadius);
		ringPos[segment].Set(1, cos(angle) * in_fPipeRadius);
		ringPos[segment].Set(2, 0.0f);
		ringPos[segment].Set(3, 1.0f);

		ringPos[segment].Set(0, ringPos[segment].Get(0) + 1.0f - in_fPipeRadius);

		ringNormals[segment].Set(0, sin(angle));
		ringNormals[segment].Set(1, cos(angle));
		ringNormals[segment].Set(2, 0.0f);
		ringNormals[segment].Set(3, 1.0f);
	}

	VMatrix44f rotation;

	// for each ring
	for(int ring = 0; ring < in_nRings; ++ring)
	{
		float angle = Pi() * 2.0f * float(ring) / float(in_nRings);
		math::SetRotationY(rotation, angle);
		//Identity(rotation);
		VVector4f coord;
		VVector3f coord3f;

		// for each sector
		for(int segment = 0; segment < in_nSegments; ++segment)
		{
			const int vertexNum = segment + (ring*in_nSegments);
			Mult(coord, rotation, ringPos[segment]);
			DeHomogenize(&coord3f, coord);
			pVB->SetCoordinate(coord3f, vertexNum);

			if( in_Types & VVertexFormat::Normals )
			{
				Mult(coord, rotation, ringNormals[segment]);
				DeHomogenize(&coord3f, coord);
				pVB->SetNormal(VNormal3f(coord3f), vertexNum);
			}
		}
	}

	// create indices
	for(int i = 0; i < indexCount; ++i)
	{
		pVB->SetIndex(0, i);
	}

	int indexPos = 0;
	for(int ring = 0; ring < in_nRings; ++ring)
	{
		for(int segment = 0; segment < in_nSegments; ++segment)
		{
			const int nextRing = (ring + 1) % (in_nRings);
			pVB->SetIndex((ring * in_nSegments) + segment, indexPos);
			++indexPos;
			pVB->SetIndex((nextRing * in_nSegments)+segment, indexPos);
			++indexPos;
		}
	}
	V3D_ASSERT(indexPos == indexCount);

	return pVB.drop();
}

const std::string MESH_RESNAME = "/meshes/test";
const std::string MAT_RESNAME = "/mat/tst";

VResourceId GetResource(const std::string& in_Name)
{
	static VServicePtr<IVResourceManager> pResMngr;
	
	return pResMngr->GetResourceByName(in_Name.c_str());
}

template<typename T>
VResourceDataPtr<const T> GetResourceData(const std::string& in_strResourceName)
{
	return GetResource(in_strResourceName)->GetData<T>();
}

void GLFWCALL VView::FrameUpdateLoop(void* arg)
{
	VView* pView = reinterpret_cast<VView*>(arg);

	// initialize
	HWND hwnd = pView->GetHWND();
	
	cout << "\tCreating display settings" << endl;
	VDisplaySettings settings;
	settings.SetWidth(200);
	settings.SetHeight(200);
	settings.SetPosition(0, 0);
	
	cout << "\tCreating context" << endl;
	IVRenderContext* pContext(new VWin32WindowContext(hwnd, &settings));
	
	cout << "\tCreating device" << endl;
	pView->m_pDevice.Assign(new VOpenGLDevice(settings, pContext));

	cout << "\tCreating test resources" << endl;
	VResourceId res = VResourceManagerPtr()->CreateResource(MESH_RESNAME.c_str());
	VVertexBuffer* pTorus = CreateTorus(
		VVertexFormat::DataTypes(VVertexFormat::Coordinates | VVertexFormat::Normals),
		0.3f, 100, 100);
	
	res->AddData<VVertexBuffer>(pTorus);
	res->AddData<VMeshDescription>(CreateMeshDescription(
		VMeshDescription::TriangleStrip,
		*pTorus,
		res->GetQualifiedName()));
	
	VResourceId matres = VResourceManagerPtr()->CreateResource(MAT_RESNAME.c_str());
	matres->AddData(new VEffectDescription(ColorEffect(VColor4f(1, 1, 1, 1))));
	
	pView->m_hMesh = pView->m_pDevice->CreateMesh(MESH_RESNAME.c_str());
	pView->m_hMaterial = pView->m_pDevice->CreateMaterial(MAT_RESNAME.c_str());

	
	// creating shooting entity part
	VDefaultRenderAlgorithm renderAlgorithm;
	pView->m_pShooting.Assign(new VShooting(pView->m_pDevice.Get(), &renderAlgorithm));
	
	pView->m_SceneRoot.AddPart(
		utils::VFourCC("shot"), 
		pView->m_pShooting);
	pView->m_SceneRoot.AddPart(
		utils::VFourCC("gfxm"), 
		VSharedPtr<IVScene>(new VSimpleScene()));
		
	VSharedPtr<v3d::entity::VEntity> pChild(new v3d::entity::VEntity());
	pView->m_SceneRoot.AddChild(pChild);
	VModel model(VModelMesh(
		GetResourceData<IVMesh>(MESH_RESNAME),
		GetResourceData<IVMaterial>(MAT_RESNAME)));
	pChild->AddPart(
		v3d::utils::VFourCC("gfxm"), 
		VSharedPtr<IVPart>(new VSceneModelPart(model)));
	
	
	pView->m_SceneRoot.Activate();
	
//	cout << "Creating mesh and material" << endl;
//	pView->m_hMesh = pView->m_pDevice->CreateMesh(MESH_RESNAME.c_str());
//	pView->m_hMaterial = pView->m_pDevice->CreateMaterial(MAT_RESNAME.c_str());

	// render
	double delay;

	float angle = 0;
	VCamera cam;
	cam.MoveForward(-7);
	VMatrix44f modelMat;
	math::Identity(modelMat);
		
	while( pView->IsRunning() ) 
	{
		if( pView->IsRendering() )
		{
			pView->m_pDevice->BeginScene();
			
			if( pView->m_SceneRoot.IsActive() )
			{
				VPointLight light;
				light.SetAmbient(VColor4f(.0f, .0f, .0f, 1.0f));
				light.SetDiffuse(VColor4f(.0f, 1.0f, .0f, 1.0f));
				light.SetSpecular(VColor4f(.8f, .8f, 1.0f, 1.0f));
				light.SetPosition(VVector3f(.0f, .0f, .0f));
				
				VPointLight light2;
				light2.SetAmbient(VColor4f(.2f, .0f, .0f, 1.0f));
				light2.SetDiffuse(VColor4f(1.0f, .0f, .0f, 1.0f));
				light2.SetSpecular(VColor4f(1.0f, .4f, .4f, 1.0f));
				light2.SetPosition(VVector3f(.0f, -.5f, 3.0f));	

				pView->m_pDevice->ApplyLight(IVDevice::Light0, &light);
				pView->m_pDevice->ApplyLight(IVDevice::Light1, &light2);

				pView->m_pDevice->SetMatrix(IVDevice::ViewMatrix, cam.TransformMatrix());
				math::SetRotationX(modelMat, angle);

				pView->m_pDevice->SetMatrix(IVDevice::ModelMatrix, modelMat);
				
//				RenderMesh(*pView->m_pDevice, pView->m_hMesh, pView->m_hMaterial);
				pView->m_pShooting->Cull();
				pView->m_pShooting->Render();
			}
			
			pView->m_pDevice->EndScene();		
			
//			VPointLight light;
//			light.SetAmbient(VColor4f(.0f, .0f, .0f, 1.0f));
//			light.SetDiffuse(VColor4f(.0f, 1.0f, .0f, 1.0f));
//			light.SetSpecular(VColor4f(.8f, .8f, 1.0f, 1.0f));
//			light.SetPosition(VVector3f(.0f, .0f, .0f));
//			
//			VPointLight light2;
//			light2.SetAmbient(VColor4f(.2f, .0f, .0f, 1.0f));
//			light2.SetDiffuse(VColor4f(1.0f, .0f, .0f, 1.0f));
//			light2.SetSpecular(VColor4f(1.0f, .4f, .4f, 1.0f));
//			light2.SetPosition(VVector3f(.0f, -.5f, 3.0f));	
//			
//			pView->m_pDevice->BeginScene();
//				pView->m_pDevice->ApplyLight(IVDevice::Light0, &light);
//				pView->m_pDevice->ApplyLight(IVDevice::Light1, &light2);
//				
//				pView->m_pDevice->SetMatrix(IVDevice::ViewMatrix, cam.TransformMatrix());
//				
//				math::SetRotationX(modelMat, angle);
//				pView->m_pDevice->SetMatrix(IVDevice::ModelMatrix, modelMat);
//				
//				RenderMesh(*pView->m_pDevice, pView->m_hMesh, pView->m_hMaterial);
//			pView->m_pDevice->EndScene();
			
			try
			{			
				delay = 1.0 / property::GetProperty<double>("editor.fps");
			}
			catch(VException&) 
			{
				property::SetProperty<double>("editor.fps", 20.0);
				delay = 1.0 / 20.0;
			}
			
			// sleep for n seconds
			glfwSleep(delay);
			angle += float(delay);
		}
		else
		{
			glfwSleep(1.0);
		}
	}
	
	cout << "Finished rendering" << endl;	
}

VView::VView(VNativeWindowHandle in_WindowHandle)
{
	m_Thread = 0;
	m_bIsRendering = 0;
//	m_hMesh = 0;
//	m_hMaterial = 0;
	
	cout << "Creating view for hwnd... " << endl;

	// start rendering
	try {		
		m_HWND = HWND(in_WindowHandle);
		
		m_Thread = glfwCreateThread(VView::RenderLoop, this);	
				
		cout << "done" << endl;	
	} catch(VException& e) {
		cout << endl
			<< "Error: "
			<< e.GetErrorString() << endl
			<< e.GetErrorFile() << ":" << e.GetErrorLine() << endl;
	} catch(...) {
		cout << "Unknown exception occured" << endl;
	}
}

VView::~VView()
{
	StopRendering();
	
	m_bIsRunning = false;
	glfwWaitThread(m_Thread, GLFW_WAIT);
}

v3d::entity::VEntity& VView::GetSceneRoot()
{
	return m_SceneRoot;
}

HWND VView::GetHWND() const 
{
	return m_HWND;
}

vbool VView::IsRendering() const {
	return m_bIsRendering;
}

void VView::Render()
{
//					VPointLight light;
//					light.SetAmbient(VColor4f(.0f, .0f, .0f, 1.0f));
//					light.SetDiffuse(VColor4f(.0f, 1.0f, .0f, 1.0f));
//					light.SetSpecular(VColor4f(.8f, .8f, 1.0f, 1.0f));
//					light.SetPosition(VVector3f(.0f, .0f, .0f));
//				
//					VPointLight light2;
//					light2.SetAmbient(VColor4f(.2f, .0f, .0f, 1.0f));
//					light2.SetDiffuse(VColor4f(1.0f, .0f, .0f, 1.0f));
//					light2.SetSpecular(VColor4f(1.0f, .4f, .4f, 1.0f));
//					light2.SetPosition(VVector3f(.0f, -.5f, 3.0f));
//				
//					VCamera cam;
//					cam.MoveForward(-7);
//					
//					m_pDevice->BeginScene();
//						m_pDevice->ApplyLight(IVDevice::Light0, &light);
//						m_pDevice->ApplyLight(IVDevice::Light1, &light2);
//						
//						m_pDevice->SetMatrix(IVDevice::ViewMatrix, cam.TransformMatrix());
//						
//						RenderMesh(*m_pDevice, m_hMesh, m_hMaterial);
//					m_pDevice->EndScene();
}

void VView::StartRendering()
{
	cout << "Starting rendering... ";

	m_bIsRendering = true;
	
	cout << "done." << endl;
}

void VView::StopRendering()
{
	m_bIsRendering = false;
	
	cout << "Stopped rendering" << endl;
}
*/

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------

