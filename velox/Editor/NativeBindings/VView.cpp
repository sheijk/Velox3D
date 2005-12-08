#include "VView.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Math.h>
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
	m_bInitCalled = false;
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
		m_NewFrameActions.clear();
		
		// remove all old actions
		for(FrameActions::iterator oldAction = m_OldFrameActions.begin();
			oldAction != m_OldFrameActions.end(); ++oldAction)
		{
			(*oldAction)->Shutdown();
			FrameActions::iterator newEnd = std::remove(
				m_FrameActions.begin(), m_FrameActions.end(), *oldAction);
			m_FrameActions.erase(newEnd, m_FrameActions.end());
		}
		m_OldFrameActions.clear();
		
		m_bInitCalled = true;
		
		// tell all frame actions to execute
		for_each(m_FrameActions.begin(), m_FrameActions.end(), mem_fun<void, IVFrameAction>(&IVFrameAction::UpdateFrame));
		
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
	
	m_bInitCalled = false;

	vfloat32 secondsWaiting = .0f;
	
	while( ! m_bInitCalled )
		glfwSleep(.01f);
}

void VView::Remove(IVFrameAction* in_pAction)
{
	m_OldFrameActions.push_back(in_pAction);
}

//-----------------------------------------------------------------------------

//void VTestFrameAction::Init()
//{
//	cout << "VTestFrameAction::Init()" << endl;
//}
//
//void VTestFrameAction::Shutdown()
//{
//	cout << "VTestFrameAction::Shutdown()" << endl;
//}
//
//void VTestFrameAction::UpdateFrame()
//{
//	++m_nCount;
//	
//	if( m_nCount > 100 )
//	{
//		cout << "VTestFrameAction::UpdateFrame: VView updating working" << endl;
//		
//		m_nCount = 0;
//	}
//}

//-----------------------------------------------------------------------------

namespace {
	const std::string g_strGridPropertyName = "v3d.graphics.showGrid";
	const std::string g_strRenderPropertyName = "v3d.graphics.render";
}

VRenderFrameAction::VRenderFrameAction(VNativeWindowHandle in_Hwnd)
{
	m_pShooting = 0;
	m_HWND = HWND(in_Hwnd);		
	m_nWidth = 0;
	m_nHeight = 0;
	m_bResized = false;
}

//void CreateTestModel(const std::string& resname);

//VModel model;

//const IVMesh* pmesh = 0;
//const IVMaterial* pmat = 0;

class VGLFWContext : public IVRenderContext
{
public:
	VGLFWContext()
	{
		int result = glfwOpenWindow(400, 300, 8, 8, 8, 8, 24, 0, GLFW_WINDOW);
		glfwSetWindowTitle("test render window");
	}
	
	virtual void MakeCurrent()
	{
	}
	
	virtual void SwapBuffers()
	{
		glfwSwapBuffers();
	}
	
	virtual IVRenderContext* CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings)
	{
		V3D_THROW(VException, "not supported, yet");
	}
};

void VRenderFrameAction::Init()
{
	cout << "\tCreating display settings" << endl;
	VDisplaySettings settings;
	settings.SetWidth(200);
	settings.SetHeight(200);
	settings.SetPosition(0, 0);
	
	cout << "\tCreating context" << endl;
	IVRenderContext* pContext(new VWin32WindowContext(m_HWND, &settings));
//	IVRenderContext* pContext(new VGLFWContext());
	
	cout << "\tCreating device" << endl;
	m_pDevice.Assign(new VOpenGLDevice(settings, pContext));

	if( ! property::ExistsProperty(g_strGridPropertyName.c_str()) )
	{
		property::SetProperty(g_strGridPropertyName.c_str(), true);	
	}

	if( ! property::ExistsProperty(g_strRenderPropertyName.c_str()) )
	{
		property::SetProperty(g_strRenderPropertyName.c_str(), true);	
	}
	
	//CreateTestModel("/editor-test");
//	model = *GetResourceData<VModel>("/editor-test");

	//pmesh = &*GetResourceData<IVMesh>("/editor-test");
	//pmat = &*GetResourceData<IVMaterial>("/editor-test");
}

void VRenderFrameAction::Shutdown()
{
}

void VRenderFrameAction::setSize(vuint width, vuint height)
{
	m_nWidth = width;
	m_nHeight = height;
	m_bResized = true;
	
	if( m_pDevice.Get() != 0 )
	{
		m_pDevice->SetViewport(0, 0, m_nWidth, m_nHeight);
	}
}

#include <V3d/OpenGL.h>

/*
void sendParallelLineVertices(int min, int max, float distance) {
	glBegin(GL_LINES);
	for(int i = min; i < max; ++i) {
		glVertex2f(-1.0f, i * distance);
		glVertex2f(1.0f, i * distance);
	}
	glEnd();
}

void showOrientationGrid() {
	const int stripeCount = 10;
	const float stripeLength = 10.0f;
	const float stripeDistance = .1f;
	
	glPushMatrix();
	glPushAttrib(GL_LINE_WIDTH);
	glLineWidth(.2f);
	
	glScalef(stripeLength, stripeLength, stripeLength);
	
	// show z = 0 plane
	glColor3f(.0f, .0f, 1.0f);
	sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
	glRotatef(90.0f, .0f, .0f, 1.0f);
	sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
	
	// show y = 0 plane
	glColor3f(.0f, 1.0f, .0f);
	glRotatef(90, 0, 1, 0);
	sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
	glRotatef(90.0f, .0f, .0f, 1.0f);
	sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
	
	// show x = 0 plane
	glColor3f(1.0f, .0f, .0f);
	glRotatef(90, 0, 1, 0);
	sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
	glRotatef(90.0f, .0f, .0f, 1.0f);
	sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
	
	glPushAttrib(GL_POINT_SIZE);
	glPointSize(3.0f);
	
	glBegin(GL_POINTS);
	for(int i = -stripeCount; i < stripeCount; ++i) {
		glColor3f(0, 1, 1);
		glVertex3f(i * stripeDistance, 0, 0);
		
		glColor3f(1, 0, 1);
		glVertex3f(0, i * stripeDistance, 0);
		
		glColor3f(1, 1, 0);
		glVertex3f(0, 0, i * stripeDistance);
	}
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glEnd();
	
	glPopAttrib();
	
	glPopAttrib();
	glPopMatrix();
}
*/

void VRenderFrameAction::UpdateFrame()
{
	m_pDevice->BeginScene();
	
//	if( m_bResized )
	{
//		glViewport(0, 0, m_nWidth, m_nHeight);
		m_bResized = false;
	}

//	if( property::GetProperty<vbool>(g_strGridPropertyName.c_str()) )
//	{
//		VMatrix44f identity;
//		math::Identity(identity);
//		
//		m_pDevice->SetMatrix(IVDevice::ModelMatrix, identity);
//		showOrientationGrid();
//	}
	
//	if( property::GetProperty<vbool>(g_strRenderPropertyName.c_str()) )
//	if( m_pDevice.Get() != 0 && pmesh != 0 && pmat != 0 )
//	{	
//		VPointLight light;
//		light.SetAmbient(VColor4f(.0f, .0f, .0f, 1.0f));
//		light.SetDiffuse(VColor4f(.0f, 1.0f, .0f, 1.0f));
//		light.SetSpecular(VColor4f(.8f, .8f, 1.0f, 1.0f));
//		light.SetPosition(VVector3f(.0f, .0f, .0f));
//		
//		VPointLight light2;
//		light2.SetAmbient(VColor4f(.2f, .0f, .0f, 1.0f));
//		light2.SetDiffuse(VColor4f(1.0f, .0f, .0f, 1.0f));
//		light2.SetSpecular(VColor4f(1.0f, .4f, .4f, 1.0f));
//		light2.SetPosition(VVector3f(.0f, -.5f, 3.0f));	
//
////		m_pDevice->ApplyLight(IVDevice::Light0, &light);
////		m_pDevice->ApplyLight(IVDevice::Light1, &light2);
//
////		RenderModel(*m_pDevice, *GetResourceData<VModel>("/data/afighter.3ds"));
//
////		RenderMesh(*m_pDevice, pmesh, pmat);
//	}

	if( m_pShooting != 0 && m_pShooting->IsActive() )
	{
//		vout << "culling ";
		
		m_pShooting->UpdateAndCull();
		
//		vout << " rendering ";
		
		m_pShooting->Render();
		
//		vout << " done" << vendl;
	}

	if( m_pShooting == 0 )
	{
		static vuint count = 100;
		
		if( count >= 100 )
		{
			vout << "alert! no shooting" << vendl;
			count = 0;
		}
		
		++count;
	}

	m_pDevice->EndScene(IVDevice::FlipScene);
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

//void DeHomogenize(VVector3f* out_Vec3f, const VVector4f& in_Vec4f)
//{
//	float w = in_Vec4f.Get(3);
//
//	if( w != 1.0f )
//	{
//		for(int i = 0; i < 3; ++i)
//			out_Vec3f->Set(i, in_Vec4f.Get(i) / w);
//	}
//	else
//	{
//		for(int i = 0; i < 3; ++i)
//			out_Vec3f->Set(i, in_Vec4f.Get(i));
//	}
//}
//
//template<typename T>
//class scope_ptr
//{
//	T* ptr;
//
//	void release()
//	{
//		if( ptr != 0 )
//			delete ptr;
//		ptr = 0;
//	}
//
//public:
//	scope_ptr(T* t) : ptr(t) {}
//	~scope_ptr() { release(); }
//
//	void operator=(T* t)
//	{
//		Release();
//		ptr = t;
//	}
//
//	T* operator->() { return ptr; }
//	const T* operator->() const { return ptr; }
//	T& operator*() { return *ptr; }
//	const T& operator*() const { return *ptr; }
//
//	T* drop() {
//		T* t = ptr;
//		ptr = 0;
//		return t;
//	}
//};
//
//
//VMeshDescription* CreateMeshDescription(
//	VMeshDescription::GeometryType in_Primitives,
//	VVertexBuffer& in_VertexBuffer,
//	const std::string& in_strVBResource,
//	const std::string& in_strIndexResource)
//{
//	VVertexFormat format(in_VertexBuffer.GetFormat());
//
//	scope_ptr<VMeshDescription> pMeshDescription(new VMeshDescription(format));
//
//	pMeshDescription->SetGeometryType(in_Primitives);
//
//	if( format.GetColorFormat().GetCount() > 0 )
//	{
//        pMeshDescription->SetColorResource(in_strVBResource);
//	}
//
//	if( format.GetCoordinateFormat().GetCount() > 0 )
//	{
//		pMeshDescription->SetCoordinateResource(in_strVBResource);
//	}
//
//	if( format.GetIndexFormat().GetCount() > 0 )
//	{
//		pMeshDescription->SetIndexResource(in_strIndexResource);
//	}
//
//	if( format.GetNormalFormat().GetCount() > 0 )
//	{
//		pMeshDescription->SetNormalResource(in_strVBResource);
//	}
//
//	for( int texcoord = 0; texcoord < format.GetTexCoordCount(); ++texcoord)
//	{
//		if( format.GetTexCoordFormat(texcoord).GetCount() > 0 )
//		{
//			pMeshDescription->SetTexCoordResource(texcoord, in_strVBResource);
//		}
//	}
//
//	return pMeshDescription.drop();
//}
//
//VMeshDescription* CreateMeshDescription(
//	VMeshDescription::GeometryType in_Primitives,
//	VVertexBuffer& in_VertexBuffer,
//	const std::string& in_strVBResource)
//{
//	return CreateMeshDescription(
//		in_Primitives,
//		in_VertexBuffer,
//		in_strVBResource,
//		in_strVBResource);
//}
//
//VVertexBuffer* CreateTorus(
//	VVertexFormat::DataTypes in_Types,
//	float in_fPipeRadius, 
//	int in_nRings, int in_nSegments)
//{
//	// enable an index buffer
//	in_Types = in_Types | VVertexFormat::Indices;
//
//	// calculate number of vertices
//	const int vertexCount = in_nRings * in_nSegments;
//	const int indexCount = 2 * vertexCount;
//
//	scope_ptr<VVertexBuffer> pVB(new VVertexBuffer(VVertexFormat(in_Types, vertexCount, indexCount)));
//
//	for(int i = 0; i < vertexCount; ++i)
//	{
//		pVB->SetCoordinate(VVector3f(0, 0, 0), i);
//	}
//
//	std::vector<VVector4f> ringPos;
//	ringPos.resize(in_nSegments);
//	std::vector<VVector4f> ringNormals;
//	ringNormals.resize(in_nSegments);
//
//	// calculate first ring and normals
//	for(int segment = 0; segment < in_nSegments; ++segment)
//	{
//		float angle = Pi() * 2.0f * float(segment) / float(in_nSegments);
//
//		ringPos[segment].Set(0, sin(angle) * in_fPipeRadius);
//		ringPos[segment].Set(1, cos(angle) * in_fPipeRadius);
//		ringPos[segment].Set(2, 0.0f);
//		ringPos[segment].Set(3, 1.0f);
//
//		ringPos[segment].Set(0, ringPos[segment].Get(0) + 1.0f - in_fPipeRadius);
//
//		ringNormals[segment].Set(0, sin(angle));
//		ringNormals[segment].Set(1, cos(angle));
//		ringNormals[segment].Set(2, 0.0f);
//		ringNormals[segment].Set(3, 1.0f);
//	}
//
//	VMatrix44f rotation;
//
//	// for each ring
//	for(int ring = 0; ring < in_nRings; ++ring)
//	{
//		float angle = Pi() * 2.0f * float(ring) / float(in_nRings);
//		math::SetRotationY(rotation, angle);
//		//Identity(rotation);
//		VVector4f coord;
//		VVector3f coord3f;
//
//		// for each sector
//		for(int segment = 0; segment < in_nSegments; ++segment)
//		{
//			const int vertexNum = segment + (ring*in_nSegments);
//			Mult(coord, rotation, ringPos[segment]);
//			DeHomogenize(&coord3f, coord);
//			pVB->SetCoordinate(coord3f, vertexNum);
//
//			if( in_Types & VVertexFormat::Normals )
//			{
//				Mult(coord, rotation, ringNormals[segment]);
//				DeHomogenize(&coord3f, coord);
//				pVB->SetNormal(VNormal3f(coord3f), vertexNum);
//			}
//		}
//	}
//
//	// create indices
//	for(int i = 0; i < indexCount; ++i)
//	{
//		pVB->SetIndex(0, i);
//	}
//
//	int indexPos = 0;
//	for(int ring = 0; ring < in_nRings; ++ring)
//	{
//		for(int segment = 0; segment < in_nSegments; ++segment)
//		{
//			const int nextRing = (ring + 1) % (in_nRings);
//			pVB->SetIndex((ring * in_nSegments) + segment, indexPos);
//			++indexPos;
//			pVB->SetIndex((nextRing * in_nSegments)+segment, indexPos);
//			++indexPos;
//		}
//	}
//	V3D_ASSERT(indexPos == indexCount);
//
//	return pVB.drop();
//}

//const std::string MESH_RESNAME = "/meshes/test";
//const std::string MAT_RESNAME = "/mat/tst";
//
//void CreateTestModel(const std::string& resname)
//{
//	VResourceId res = VResourceManagerPtr()->CreateResource(resname.c_str());
//
//	res->AddData(new VEffectDescription(ColorEffect(VColor4f(1, 0, 0, 1))));
//	
//	VVertexBuffer* pVertexBuffer = new VVertexBuffer(
//		VVertexFormat(VVertexFormat::Coordinates, 3, 0));
//	pVertexBuffer->SetCoordinate(VVertex3f(1, 0, -1), 0);
//	pVertexBuffer->SetCoordinate(VVertex3f(-1, 0, -1), 1);
//	pVertexBuffer->SetCoordinate(VVertex3f(0, 1, -1), 2);
//	res->AddData(pVertexBuffer);
//	
//	res->AddData(CreateMeshDescription(
//		VMeshDescription::Triangles,
//		*pVertexBuffer,
//		res->GetQualifiedName()));
//}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------

