/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VOpenGLDevice.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>
#include <V3d/Core/VLogging.h>
#include <V3d/Graphics/VMeshDescription.h>
#include <V3d/Graphics/VEffectDescription.h>

#include <V3d/Graphics/Materials/EffectUtils.h>

#include <V3d/Graphics/VDeviceMatrix.h>
#include <V3d/Math/VMatrixOps.h>

#include "IVOpenGLRenderState.h"

#include <V3d/Graphics/GraphicsExceptions.h>
#include <V3d/Graphics/Misc/MiscUtils.h>
#include <V3d/Graphics/VLight.h>

#include "VMeshHandle.h"
#include "VStreamMesh.h"

#include <V3d/Resource.h>

#include <V3d/Graphics/VDeviceCaps.h>

#include <V3d/Graphics/IVGraphicsService.h>

#include <V3d/OpenGL.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics;
//-----------------------------------------------------------------------------

namespace {
	/**
	 * Converts a pointer to a mesh to a mesh handle
	 * Use this to enable changing the exact type of MeshHandle
	 */
	IVDevice::MeshHandle MakeMeshHandle(IVMesh* pMesh)
	{
		return pMesh;
	}

	/**
	 * Converts a MeshHandle to a pointer to a mesh
	 * Use this to enable changing the exact type of MeshHandle
	 */
	const VMeshBase* MakeMeshPointer(IVDevice::MeshHandle handle)
	{
		return static_cast<const VMeshBase*>(handle);
	}

	void SetGLMatrix(int mode, const math::VMatrix44f& mat, IVDevice* pDevice)
	{
		VDeviceMatrix devMat;
		VDeviceMatrix::ConvertFromTransform(&devMat, mat, *pDevice);

		glMatrixMode(mode);
		glLoadMatrixf(devMat.GetElements());	
	}

	/** 
	 * Call with GL_(PROJECTION|MODELVIEW|TEXTURE)_MATRIX to get the OpenGL
	 * matrices 
	 */
	void GetGLMatrix(int in_Matrix, math::VMatrix44f* out_pMatrix)
	{
		vfloat32 matrix[16];
		glGetFloatv(in_Matrix, matrix);

		vuint index = 0;
		for(vuint column = 0; column < 4; ++column)
		for(vuint row = 0; row < 4; ++row)
		{
			out_pMatrix->Set(row, column, matrix[index]);
			++index;
		}
	}

	template<typename T>
		vbool BitsSet(T value, T bits)
	{
		return (value & bits) == bits;
	}
}

/*
VOpenGLDevice::VOpenGLDevice(const VDisplaySettings* in_pSettings, HWND in_hWnd)
	:
	m_DisplaySettings(*in_pSettings)
{
	hWnd = in_hWnd;

	SetDisplay();

	m_StateCategories.RegisterCategory(m_TextureStateCategory);
	m_StateCategories.RegisterCategory(m_MiscStateCategory);
	m_StateCategories.RegisterCategory(m_VertexShaderCategory);
	m_StateCategories.RegisterCategory(m_PixelShaderCategory);

	Identity(m_ModelMatrix);
	Identity(m_ViewMatrix);
	Identity(m_ProjectionMatrix);
	Identity(m_TextureMatrix);

	RecalcModelViewMatrix();
}
*/

VOpenGLDevice::VOpenGLDevice(
	const graphics::VDisplaySettings& in_Settings,
	IVRenderContext* in_pContext)
	:
	m_pContext(in_pContext),
	m_DisplaySettings(in_Settings)
{
	//m_StateCategories.RegisterCategory(m_TextureStateCategory);
	//m_StateCategories.RegisterCategory(m_MiscStateCategory);
	//m_StateCategories.RegisterCategory(m_VertexShaderCategory);
	//m_StateCategories.RegisterCategory(m_PixelShaderCategory);

	Identity(m_ModelMatrix);
	//Identity(m_ViewMatrix);
	Identity(m_ProjectionMatrix);
	Identity(m_TextureMatrix);

	// create default material if it does not exist, yet
	m_pDefaultMaterial = IVDevice::GetDefaultMaterial();


	SetDisplay();

	RecalcModelViewMatrix();

	VGraphicsServicePtr pGfxService;
	if( pGfxService->GetMainDevice() == 0 )
	{
		pGfxService->SetMainDevice(this);
	}

	m_bActive = false;
}

//-----------------------------------------------------------------------------
VOpenGLDevice::~VOpenGLDevice()
{
	//// output warnings for unreleased resources
	//const vuint nUnreleasedBufferCount = m_Buffers.GetBufferCount();

	//if( nUnreleasedBufferCount > 0 )
	//{
	//	std::stringstream message;
	//	message << "Warning: ";
	//	message << nUnreleasedBufferCount;
	//	message << " gfx device buffers have not been released\n";

	//	V3D_DEBUGMSG(message.str().c_str());
	//	vout << message.str();

	//	for(vuint bufid = 0; bufid < m_Buffers.GetBufferCount(); ++bufid)
	//	{
	//		std::stringstream msg;
	//		msg << "\tBuffer with " 
	//			<< m_Buffers.GetReferenceCount(m_Buffers.GetBuffer(bufid)) 
	//			<< " references at address 0x"
	//			<< m_Buffers.GetBuffer(bufid)
	//			<< "\n";

	//		V3D_DEBUGMSG(msg.str().c_str());
	//		vout << msg.str();
	//	}
	//}

	const vuint nUnreleasedMeshes = vuint(m_Meshes.size());
	if( nUnreleasedMeshes > 0 )
	{
		std::stringstream message;
		message << "Warning: " 
				<< nUnreleasedMeshes 
				<< " gfx device meshes have not been released\n";

		V3D_DEBUGMSG(message.str().c_str());
		vout << message.str();
	}

	//DestroyContext();
}

//std::string GenerateBufferName()
//{
//	static vuint lastBufferId = 0;
//
//	++lastBufferId;
//
//	std::stringstream name;
//	name << "device/buffers/internal" << lastBufferId;
//
//	return name.str();
//}

//-----------------------------------------------------------------------------

/* old 2005-04-17
IVDevice::MeshHandle VOpenGLDevice::CreateMesh(VStringParam in_strResource)
{
	using namespace resource;
	resource::VResourceManagerPtr pResManager;

	VResourceId mdRes = pResManager->GetResourceByName(in_strResource);
	resource::VResourceDataPtr<const VMeshDescription> in_pMeshDescription
		= mdRes->GetData<VMeshDescription>();

	VResourceId edRes = pResManager->GetResourceByName(in_strResource);
	resource::VResourceDataPtr<const VEffectDescription> in_pEffectDescription
		= mdRes->GetData<VEffectDescription>();

	// create materials
	std::vector<VRenderStateList*> statelists
		= m_StateCategories.CreateMaterialList(*in_pEffectDescription);

	std::vector<IVMaterial*> materials(statelists.begin(), statelists.end());

	if( materials.size() > 0 )
	{
		// create mesh
		VMeshDescription descr = *in_pMeshDescription;

		VMeshBase* pMesh = new VStreamMesh(materials, *in_pMeshDescription);

		m_Meshes.push_back(pMesh);

		return MakeMeshHandle(pMesh);
	}
	else
	{
		return 0;
	}
}
*/

IVDevice::MeshHandle VOpenGLDevice::CreateMesh(VStringParam in_strResource)
{
	using namespace resource;
	resource::VResourceManagerPtr pResManager;

	VResourceId mdRes = pResManager->GetResourceByName(in_strResource);
	resource::VResourceDataPtr<const VMeshDescription> in_pMeshDescription
		= mdRes->GetData<VMeshDescription>();

	// create mesh
	VMeshDescription descr = *in_pMeshDescription;

	VMeshBase* pMesh = new VStreamMesh(*in_pMeshDescription);

	mdRes->AddData<IVMesh>(pMesh);

	return MakeMeshHandle(pMesh);
}

IVDevice::MaterialHandle VOpenGLDevice::CreateMaterial(VStringParam in_strResource)
{
	using namespace resource;

	VResourceDataPtr<const IVMaterial> hMaterial 
		= GetResourceData<IVMaterial>(in_strResource);

	return &*hMaterial;
/*
	using namespace resource;
	resource::VResourceManagerPtr pResManager;

	VResourceId edRes = pResManager->GetResourceByName(in_strResource);
	resource::VResourceDataPtr<const VEffectDescription> in_pEffectDescription
		= edRes->GetData<VEffectDescription>();

	// create materials
	std::vector<VRenderStateList*> statelists
		= m_StateCategories.CreateMaterialList(*in_pEffectDescription);

	std::vector<VRenderStateList> sl;

	for(vuint i = 0; i < statelists.size(); ++i)
	{
		sl.push_back(VRenderStateList(*statelists[i]));
		delete statelists[i];
		statelists[i] = 0;
	}

	VMaterial* pMaterial = new VMaterial(sl);

	if( statelists.size() > 0 )
	{
		edRes->AddData<IVMaterial>(pMaterial);
		return pMaterial;
	}
	else
	{
		return 0;
	}
*/
}

//IVDevice::MeshHandle VOpenGLDevice::CreateMesh(
//	const VMeshDescription& in_MeshDescr,
//	const VEffectDescription& in_EffectDescr
//	)
//{
//	V3D_THROW(VException, "Warning: using deprecated function v3d::graphics"
//		"::IVDevice::CreateMesh(VMeshDescription&, VEffectDescription&). "
//		"Use the resource manager instead (-> CreateMesh(string))");
//}

void VOpenGLDevice::DeleteMesh(MeshHandle& in_Mesh)
{
	V3D_THROW(VException, "Warning: used deprecated method v3d::graphics::"
		"IVDevice::DeleteMesh(MeshHandle&)");
	//VMeshBase* pMesh = MakeMeshPointer(in_Mesh);

	//if( pMesh != 0 )
	//{
	//	// release buffers
	//	std::vector<VMeshDescription::BufferHandle> buffers = pMesh->GetBuffers();

	//	for(vuint bufid = 0; bufid < buffers.size(); ++bufid)
	//	{
	//		VByteBuffer* pByteBuffer = static_cast<VByteBuffer*>(buffers[bufid]);
	//		m_Buffers.Delete(pByteBuffer);
	//	}

	//	m_Meshes.remove(pMesh);

	//	delete pMesh;
	//	in_Mesh = 0;
	//}
}

//-----------------------------------------------------------------------------

void VOpenGLDevice::RenderMesh(MeshHandle in_pMesh)
{
	const VMeshBase* pMesh = reinterpret_cast<const VMeshBase*>(MakeMeshPointer(in_pMesh));

	pMesh->Render();
}

//-----------------------------------------------------------------------------

void VOpenGLDevice::ApplyState(const IVRenderState& in_State)
{
	const IVOpenGLRenderState* pState = reinterpret_cast<const IVOpenGLRenderState*>
		(&in_State);

	pState->Apply(this);
}

//-----------------------------------------------------------------------------

void VOpenGLDevice::SetDisplay()
{
	/*
	// setup fullscreen if needed
    if( !(hDC=GetDC(hWnd)) )
	if(m_DisplaySettings.IsFullscreen())
	{
		V3D_THROW(VIllegalDisplayException, "Fullscreen mode currently not supported");

		/*
		DEVMODE displayFormat;

		displayFormat.dmSize		= sizeof(DEVMODE);
		displayFormat.dmPelsWidth	= m_DisplaySettings.m_iWidth;
		displayFormat.dmPelsHeight	= m_DisplaySettings.m_iHeight;
		displayFormat.dmBitsPerPel	= m_DisplaySettings.m_iBitsPerPixel;
		displayFormat.dmFields	    = DM_PELSWIDTH | DM_PELSHEIGHT |
													 DM_BITSPERPEL;

		if (ChangeDisplaySettings(&displayFormat, CDS_FULLSCREEN) !=
									DISP_CHANGE_SUCCESSFUL)
		{
			vout << "requesting fullscreen mode failed!" << vendl;
			m_DisplaySettings.m_bFullscreen = false;
		}
		* /
	}

	SetPixFormat();
	CreateContext();
	*/

	m_pContext->MakeCurrent();
	InitializeExtensions();
	SetScreenSize();
	SetBackgroundColor();

	glClearDepth(1.0f);
	//glClearDepth(m_DisplaySettings.m_fClearDepth);
	glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);
}
//-----------------------------------------------------------------------------
/*
void VOpenGLDevice::SetPixFormat()
{
	GLuint PixelFormat = 0;

	PIXELFORMATDESCRIPTOR PixelFormatDesc =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		0,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		0,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	//PixelFormatDesc.cAccumBits		= m_DisplaySettings.m_iAccumulationBuffer;
	PixelFormatDesc.cAccumBits		= m_DisplaySettings.GetAccumulationBits();
	PixelFormatDesc.cDepthBits		= m_DisplaySettings.GetDepthBits();
	PixelFormatDesc.cStencilBits	= m_DisplaySettings.GetStencilBits();
	PixelFormatDesc.cColorBits		= m_DisplaySettings.GetBitsPerPixel();

	if (!(PixelFormat=ChoosePixelFormat(hDC,&PixelFormatDesc)))
	{
		//TODO: error checking
		vout << "finding suitable pixelformat failed!" << vendl;
	}


	if(!SetPixelFormat(hDC,PixelFormat,&PixelFormatDesc))
	{
		//TODO: error checking
		vout << "requesting pixelformat failed!" << vendl;
	}
}
*/
//-----------------------------------------------------------------------------
/*
void VOpenGLDevice::CreateContext()
{
	if(!(hRC = wglCreateContext(hDC)))
	{
		vout << "creating rendering contexts failed!" << vendl;
	}

	if(!wglMakeCurrent(hDC,hRC))
	{
		vout << "activating rendering context failed!" << vendl;
	}
}
*/
//-----------------------------------------------------------------------------
/*
void VOpenGLDevice::DestroyContext()
{
	if(hDC)
	{
		if(!(wglMakeCurrent(hDC,hRC)))
			vout << "destroying rendering contexts faild!" << vendl;

		hDC = NULL;
	}

	if(hRC)
	{

		if(!(wglDeleteContext(hRC)))
		{
			vout <<"releasing rendering context faild!" << vendl;
		}

		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd,hDC))
	{
		vout << "releasing device context failed!" << vendl;
	}
}
*/
//-----------------------------------------------------------------------------

void VOpenGLDevice::SetScreenSize()
{
	V3D_ASSERT(m_DisplaySettings.GetHeight() > 0);
	//if(m_DisplaySettings.m_iHeight <= 0) m_DisplaySettings.m_iHeight = 1;
	glViewport(0, 0, m_DisplaySettings.GetWidth(), m_DisplaySettings.GetHeight());
	//glViewport(0, 0, m_DisplaySettings.m_iWidth, m_DisplaySettings.m_iHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, 
					((vfloat32)m_DisplaySettings.GetWidth() /
					m_DisplaySettings.GetHeight()),
					1.0f,
					1000.0f);
	GetGLMatrix(GL_PROJECTION_MATRIX, &m_ProjectionMatrix);
	//gluPerspective(m_DisplaySettings.m_fFieldOfView,
	//				((vfloat32)m_DisplaySettings.m_iWidth /
	//				m_DisplaySettings.m_iHeight),
	//				m_DisplaySettings.m_fNearClippingPlane,
	//				m_DisplaySettings.m_fFarClippingPlane);
	glMatrixMode(GL_MODELVIEW);
}
//-----------------------------------------------------------------------------

void VOpenGLDevice::SetBackgroundColor()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClearColor(m_DisplaySettings.m_fBackgroundRed,
	//			 m_DisplaySettings.m_fBackgroundGreen,
	//			 m_DisplaySettings.m_fBackgroundBlue,
	//			 m_DisplaySettings.m_fBackgroundAlpha);
}
//-----------------------------------------------------------------------------

void VOpenGLDevice::InitializeExtensions()
{
	m_pVendor	= (vchar *)glGetString(GL_VENDOR);
	m_pRenderer	= (vchar *)glGetString(GL_RENDERER);
	m_pVersion	= (vchar *)glGetString(GL_VERSION);

	//vchar* Extensions = (vchar*)glGetString(GL_EXTENSIONS);
	//vchar  ExtensionName[64];
	//vuint Length =(vuint) strlen(Extensions);
	//vuint y = 0;

/*
    vout << "-------------------------------------------------------" << vendl;
	vout << "OpenGL vendor: " << m_pVendor << vendl;
	vout << "OpenGL renderer: " << m_pRenderer << vendl;
	vout << "OpenGL version: " << m_pVersion << vendl;

	vout << "OpenGL extensions: " << vendl;

	for (vuint i=0; i<Length; i++)
	{

		ExtensionName[y] = Extensions[i];
		y++;
		if (Extensions[i]==' ')
		{
			ExtensionName[y-1] = '\0';
			y=0;
			vout << ExtensionName << vendl;
		}

	}
*/

	GLenum result = glewInit();
	if( result != GLEW_OK )
	{
		vout << "glew init failed: " << glewGetErrorString(result) << vendl;
	}
	else
	{
		vout << "[VOpenGLDevice.cpp] glewInit() succeeded" << vendl;

		VDeviceCaps caps;
		caps.GatherInfoFromCurrentContext();
		caps.PrintInfo();
	}
}

//-----------------------------------------------------------------------------

void VOpenGLDevice::BeginScene()
{
	m_bActive = true;

	m_pContext->MakeCurrent();

	glViewport(0, 0,
		m_DisplaySettings.GetWidth(), m_DisplaySettings.GetHeight());

	ApplyMaterial(*this, &m_pDefaultMaterial->GetPass(0));

	glClearColor(m_ClearColor.red, m_ClearColor.green, m_ClearColor.blue, 
		m_ClearColor.alpha);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static vfloat32 ambient[4] = { .5f, .5f, .5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	RecalcModelViewMatrix();
	SetGLMatrix(GL_PROJECTION, m_ProjectionMatrix, this);
	SetGLMatrix(GL_TEXTURE, m_TextureMatrix, this);
}

//-----------------------------------------------------------------------------
void VOpenGLDevice::EndScene(EndSceneFlags in_Flags)
{
	m_bActive = false;

	m_pContext->MakeCurrent();

	if( (in_Flags & NoFlip) == NoFlip )
		m_pContext->SwapBuffers();

	ApplyMaterial(*this, &m_pDefaultMaterial->GetPass(0));
}

void VOpenGLDevice::Flip()
{
	m_pContext->SwapBuffers();
}

void VOpenGLDevice::Clear(ClearFlags in_Flags)
{
    GLbitfield bitfield = 0;

	if( BitsSet(in_Flags, ClearColor) )
		bitfield |= GL_COLOR_BUFFER_BIT;

	if( BitsSet(in_Flags, ClearZ) )
		bitfield |= GL_DEPTH_BUFFER_BIT;

	glClear(bitfield);
}

void VOpenGLDevice::SetViewport(vint left, vint top, vint right, vint bottom)
{
	V3D_ASSERT(left < right);
	V3D_ASSERT(top < bottom);

	m_DisplaySettings.SetPosition(left, top);
	m_DisplaySettings.SetSize(right - left, bottom - top);
}

void VOpenGLDevice::SetClearColor(
	vfloat32 red, vfloat32 green, vfloat32 blue, vfloat32 alpha)
{
	m_ClearColor.red = red;
	m_ClearColor.green = green;
	m_ClearColor.blue = blue;
	m_ClearColor.alpha = alpha;
}

vbool VOpenGLDevice::IsActive() const
{
	return m_bActive;
}

void VOpenGLDevice::SetMatrix(MatrixMode in_Mode, const math::VMatrix44f& in_Matrix)
{
	switch(in_Mode)
	{
	case ProjectionMatrix:
		m_ProjectionMatrix = in_Matrix;
		SetGLMatrix(GL_PROJECTION, in_Matrix, this);
		break;

	case ModelMatrix:
		m_ModelMatrix = in_Matrix;
		RecalcModelViewMatrix();
		break;

	//case ViewMatrix:
	//	m_ViewMatrix = in_Matrix;
	//	RecalcModelViewMatrix();
	//	break;
	case TextureMatrix:
		m_TextureMatrix = in_Matrix;
		SetGLMatrix(GL_TEXTURE, m_TextureMatrix, this);
		break;

	default:
		V3D_THROW(
			VInvalidMatrixTypeException, 
			"invalid matrix type specified");
	}
}

void VOpenGLDevice::SetProjectionMatrix(const math::VMatrix44f& in_Matrix)
{
	SetMatrix( ProjectionMatrix, in_Matrix );
}

const math::VMatrix44f& VOpenGLDevice::GetProjectionMatrix() const
{
	return GetMatrix( ProjectionMatrix );
}

void VOpenGLDevice::SetModelMatrix(const math::VMatrix44f& in_Matrix)
{
	SetMatrix( ModelMatrix, in_Matrix );
}

const math::VMatrix44f& VOpenGLDevice::GetModelMatrix() const
{
	return GetMatrix( ModelMatrix );
}

const math::VMatrix44f& VOpenGLDevice::GetViewMatrix() const
{
	return m_ViewMatrix;
}

const math::VRBTransform& VOpenGLDevice::GetViewTransform() const
{
	return m_ViewTransform;
}

void VOpenGLDevice::SetViewTransform(const math::VRBTransform& in_Transform)
{
	m_ViewTransform = in_Transform;
	RecalcModelViewMatrix();
}

//-----------------------------------------------------------------------------

const math::VMatrix44f& VOpenGLDevice::GetMatrix(MatrixMode in_Mode) const
{
	switch(in_Mode)
	{
		case ModelMatrix:
			return m_ModelMatrix;
			break;
		case TextureMatrix:
			return m_TextureMatrix;
			break;
		//case ViewMatrix:
		//	return m_ViewMatrix;
		//	break;
		case ProjectionMatrix:
			return m_ProjectionMatrix;
			break;
		default:
			V3D_THROW(
				VInvalidMatrixTypeException, 
				"invalid matrix type specified");
	}
}

void VOpenGLDevice::RecalcModelViewMatrix()
{
	using namespace math;

	//TODO: this code is copied from VCamera.
	// it should be investigated + documented...
	VVector3f f = - m_ViewTransform.GetZAxis();
	Normalize(f);

	VVector3f up = m_ViewTransform.GetYAxis();
	Normalize(up);

	VVector3f s;

	s = Cross(f,up);

	VVector3f u;

	u = Cross(s,f);

	VMatrix44f m;
	Identity(m);
	m.Set(0, 0, s.Get(0));
	m.Set(0, 1, s.Get(1));
	m.Set(0, 2, s.Get(2));

	m.Set(1, 0, u.Get(0));
	m.Set(1, 1, u.Get(1));
	m.Set(1, 2, u.Get(2));

	m.Set(2, 0, -f.Get(0));
	m.Set(2, 1, -f.Get(1));
	m.Set(2, 2, -f.Get(2));

	VMatrix44f t;
	Identity(t);
	const VVector3f pos = m_ViewTransform.GetPosition();
	t.SetTransform(-pos[0], -pos[1], -pos[2]);

	VMatrix44f r;
	Identity(r);
	Mult(r, m, t);

	m_ViewMatrix = r;
	VMatrix44f modelView = m_ViewMatrix;

	Mult(modelView, modelView, m_ModelMatrix);

	SetGLMatrix(GL_MODELVIEW, modelView, this);
}

//-----------------------------------------------------------------------------

void VOpenGLDevice::ApplyLight(LightId in_Number, const VLight* in_pLight)
{
    if( m_Lights.size() <= in_Number )
		m_Lights.resize(in_Number+1);

	m_Lights[in_Number] = in_pLight;

	if( in_pLight == 0 )
	{
		vuint lastNonZero = -1;
		for(vuint pos = 0; pos < m_Lights.size(); ++pos)
		{
			if( m_Lights[pos] != 0 )
				lastNonZero = pos;
		}

		if( m_Lights.size() != (lastNonZero+1) )
			m_Lights.resize(lastNonZero+1);
	}

	//if( int(in_Number) > int(LightMaxCount)-1 )
	//{
	//	V3D_THROWMSG(VGraphicException, 
	//		"Tried to set invalid light "
	//		<< in_Number 
	//		<< " (only 0-8 are allowed");
	//}

	//GLenum lightnum = GL_LIGHT0 + int(in_Number);

	//m_PointLights[int(in_Number)] = *in_pLight;

	//if( in_pLight != 0 ) 
	//{
	//	static float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//	static float black[] = { .0f, .0f, .0f, 1.0f };

	//	glMaterialfv(GL_FRONT, GL_AMBIENT, white);
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	//	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

	//	glMaterialfv(GL_BACK, GL_AMBIENT, black);
	//	glMaterialfv(GL_BACK, GL_SPECULAR, black);
	//	glMaterialfv(GL_BACK, GL_DIFFUSE, black);

	//	glLightfv(lightnum, GL_AMBIENT, (float*)&(in_pLight->GetAmbient()));
	//	glLightfv(lightnum, GL_SPECULAR, (float*)&(in_pLight->GetSpecular()));
	//	glLightfv(lightnum, GL_DIFFUSE, (float*)&(in_pLight->GetDiffuse()));

	//	VVector3f& lpos(in_pLight->GetPosition());
	//	float pos[] = { lpos.GetX(), lpos.GetY(), lpos.GetZ(), 1.0f };
	//	glLightfv(lightnum, GL_POSITION, pos);

	//	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	//	glEnable(GL_LIGHTING);
	//	glEnable(lightnum);
	//}
	//else
	//{
	//	glDisable(lightnum);
	//}
}

IVDevice::LightId VOpenGLDevice::MaxActiveLight() const
{
	return LightId( m_Lights.size() );
}

const VLight* VOpenGLDevice::GetLight(LightId in_Number) const
{
	V3D_ASSERT(in_Number < MaxActiveLight());
	if( in_Number >= 0 && in_Number < m_Lights.size() )
		return m_Lights[in_Number];
	else
		return 0;
}

//const VPointLight& VOpenGLDevice::GetLight(LightId in_Number) const
//{
//	if( int(in_Number) <= int(Light7) )
//	{
//		return m_PointLights[int(in_Number)];
//	}
//	else
//	{
//		V3D_THROWMSG(VGraphicException, "Tried to get invalid light nr. "
//			<< int(in_Number) << " (max. " << int(LightMaxCount) << ")");
//	}
//}

IVRenderContext* VOpenGLDevice::CreateOffscreenContext(const graphics::VDisplaySettings* in_pDisplaySettings)
{
	return m_pContext->CreateOffscreenContext(in_pDisplaySettings);
}

IVRenderContext* VOpenGLDevice::GetRenderContext()
{
	return m_pContext;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------

