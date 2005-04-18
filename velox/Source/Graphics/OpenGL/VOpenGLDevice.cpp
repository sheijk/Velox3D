#include "VOpenGLDevice.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/VLogging.h>
#include <V3d/Graphics/VMeshDescription.h>
#include <V3d/Graphics/VEffectDescription.h>

#include <V3dLib/Graphics/Materials/EffectUtils.h>

#include <v3d/Graphics/VDeviceMatrix.h>
#include <v3d/Math/VMatrixOps.h>

#include "IVOpenGLRenderState.h"

#include <v3d/Graphics/GraphicsExceptions.h>
#include <V3dLib/Graphics/Misc/MiscUtils.h>

#include "VMeshHandle.h"
#include "VStreamMesh.h"

#include <V3d/Resource.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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
	VMeshBase* MakeMeshPointer(IVDevice::MeshHandle handle)
	{
		return static_cast<VMeshBase*>(handle);
	}
}

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

	DestroyContext();
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

	return MakeMeshHandle(pMesh);
}

IVDevice::MaterialHandle VOpenGLDevice::CreateMaterial(VStringParam in_strResource)
{
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
		return pMaterial;
	}
	else
	{
		return 0;
	}
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
	VMeshBase* pMesh = reinterpret_cast<VMeshBase*>(MakeMeshPointer(in_pMesh));

	pMesh->Render();
}

//-----------------------------------------------------------------------------

void VOpenGLDevice::ApplyState(const IVRenderState& in_State)
{
	const IVOpenGLRenderState* pState = reinterpret_cast<const IVOpenGLRenderState*>
		(&in_State);

	pState->Apply();
}

//-----------------------------------------------------------------------------

void VOpenGLDevice::SetDisplay()
{
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
		*/
	}

	SetPixFormat();
	CreateContext();
	InitializeExtensions();
	SetScreenSize();
	SetBackgroundColor();

	glClearDepth(1.0f);
	//glClearDepth(m_DisplaySettings.m_fClearDepth);
	glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);
}
//-----------------------------------------------------------------------------

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
//-----------------------------------------------------------------------------

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
//-----------------------------------------------------------------------------

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
					900000.0f);
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

	vchar* Extensions = (vchar*)glGetString(GL_EXTENSIONS);
	vchar  ExtensionName[64];
	vuint Length =(vuint) strlen(Extensions);
	vuint y = 0;

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

	if(extgl_Initialize() != 0)
		vout << "Initializing extensions failed!" << vendl;
	else
		vout << "Initializing extensions done..." << vendl;

}

//-----------------------------------------------------------------------------

void VOpenGLDevice::BeginScene()
{
	wglMakeCurrent(hDC, hRC);

	ApplyMaterial(*this, &m_StateCategories.GetDefaultMaterial());

	// fuer sowas solltes noch fkten geben -ins
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	RecalcModelViewMatrix();
}

//-----------------------------------------------------------------------------
void VOpenGLDevice::EndScene()
{
	wglMakeCurrent(hDC, hRC);
	SwapBuffers(hDC);
}

//-----------------------------------------------------------------------------
//TODO: move to a graphics exception header
V3D_DECLARE_EXCEPTION(VInvalidMatrixTypeException, VException);

namespace
{
	void SetGLMatrix(int mode, const VMatrix44f& mat, IVDevice* pDevice)
	{
		VDeviceMatrix devMat;
		VDeviceMatrix::ConvertFromTransform(&devMat, mat, *pDevice);

		glMatrixMode(mode);
		glLoadMatrixf(devMat.GetElements());	
	}
}

void VOpenGLDevice::SetMatrix(MatrixMode in_Mode, const VMatrix44f& in_Matrix)
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

	case ViewMatrix:
		m_ViewMatrix = in_Matrix;
		RecalcModelViewMatrix();
		break;

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

//-----------------------------------------------------------------------------

const VMatrix44f& VOpenGLDevice::GetMatrix(MatrixMode in_Mode)
{
	switch(in_Mode)
	{
		case ModelMatrix:
			return m_ModelMatrix;
			break;
		case TextureMatrix:
			return m_TextureMatrix;
			break;
		case ViewMatrix:
			return m_ViewMatrix;
			break;
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
	VMatrix44f modelView;
	Mult(modelView, m_ViewMatrix, m_ModelMatrix);
	//Mult(modelView, m_ModelMatrix, m_ViewMatrix);

	SetGLMatrix(GL_MODELVIEW, modelView, this);
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
