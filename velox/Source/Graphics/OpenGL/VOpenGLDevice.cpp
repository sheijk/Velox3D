#include "VOpenGLDevice.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/Wrappers/VIterator.h>
#include <v3d/Core/VLogging.h>

#include <v3d/Graphics/VDeviceMatrix.h>
#include <v3d/Math/VMatrixOps.h>

#include "IVOpenGLRenderState.h"

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
	IVMesh* MakeMeshPointer(IVDevice::MeshHandle handle)
	{
		return handle;
	}
}

VOpenGLDevice::VOpenGLDevice(const VDisplaySettings* in_pSettings, HWND in_hWnd)
{
	m_DisplaySettings = new VDisplaySettings(*in_pSettings);
	hWnd = in_hWnd;

	SetDisplay();


	m_RenderMethods.RegisterRenderMethod(m_ImmediateRenderMethod);
	//m_RenderMethods.RegisterRenderMethod(m_VBORenderMethod);

	m_StateCategories.RegisterCategory(m_TextureStateCategory);
	m_StateCategories.RegisterCategory(m_MiscStateCategory);
	//m_StateCategories.RegisterCategory(m_BlendingStateCategory);

	Identity(m_ModelMatrix);
	Identity(m_ViewMatrix);
	Identity(m_ProjectionMatrix);
	Identity(m_TextureMatrix);
}
//-----------------------------------------------------------------------------

VOpenGLDevice::~VOpenGLDevice()
{
	// output warnings for unreleased resources
	const vuint nUnreleasedBufferCount = m_Buffers.GetBufferCount();

	if( nUnreleasedBufferCount > 0 )
	{
		std::stringstream message;
		message << "Warning: ";
		message << nUnreleasedBufferCount;
		message << " gfx device buffers have not been released\n";

		V3D_DEBUGMSG(message.str().c_str());
		vout << message.str();
	}

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

	delete m_DisplaySettings;
}

IVDevice::BufferHandle VOpenGLDevice::CreateBuffer(
	BufferType in_Type,
	Buffer* in_pBuffer,
	BufferCopyMode in_CopyMode
	)
{
	// DropData will cause crashes when deleting the buffer..
	//in_CopyMode = VBufferBase::CopyData;

	//Buffer* pBuffer = new VByteBuffer(in_pBuffer, in_CopyMode);
	Buffer* pBuffer = in_pBuffer->CreateCopy(in_CopyMode);

	switch(in_Type)
	{
	case VertexBuffer:
		{
			m_Buffers.Add(pBuffer);
		} break;

	case Texture:
		{
			m_TextureBuffers.Add(pBuffer);
		} break;

	default:
		V3D_THROW(VException, "tried to create illegal buffer type");
	}

	return BufferHandle(pBuffer);
}

//-----------------------------------------------------------------------------

//TODO lacks for int support -ins ; lacks for any support ;) -- sheijk
void VOpenGLDevice::DeleteBuffer(BufferHandle& in_hBuffer)
{
	//vout << "VOpenGLDevice.DeleteBuffer tut grad nix" << vendl;

	VByteBuffer* pByteBuffer = reinterpret_cast<VByteBuffer*>(in_hBuffer);

	// remove from vertex and texture buffers
	m_TextureBuffers.Delete(pByteBuffer);
	m_Buffers.Delete(pByteBuffer);

	in_hBuffer = pByteBuffer;
}

void VOpenGLDevice::OverwriteBuffer(
	BufferHandle& in_hBuffer,
	vuint in_nFirstElement,
	vuint in_nCount,
	const vbyte* in_pData
	)
{
	// get buffer
	// write data
	memcpy(
		in_hBuffer->GetDataAddress() + in_nFirstElement, 
		in_pData,
		in_nCount
		);
}


IVDevice::MeshHandle VOpenGLDevice::CreateMesh(
	const VMeshDescription& in_MeshDesc,
	const VMaterialDescription& in_MaterialDesc
	)
{
	IVMaterial* pMaterial = CreateMaterial(in_MaterialDesc);

	VMeshDescription descr = in_MeshDesc;

	// add buffers to device, if they are external
	InternalizeBuffers(descr);
	
	//TODO
	// increase reference count for all used buffers

	IVMesh* pMesh = m_RenderMethods.CreateMesh(descr, 0, pMaterial);

	m_Meshes.push_back(pMesh);

	return MakeMeshHandle(pMesh);
}

IVDevice::MeshHandle VOpenGLDevice::CreateMesh(
	const VMeshDescription& in_MeshDescr,
	const VEffectDescription& in_EffectDescr
	)
{
	std::vector<VRenderStateList*> materials
		= m_StateCategories.CreateMaterialList(in_EffectDescr);

	if( materials.size() > 0 )
	{
		V3D_ASSERT(materials.size() == 1);

		VMeshDescription descr = in_MeshDescr;

		InternalizeBuffers(descr);

		IVMesh* pMesh = m_RenderMethods.CreateMesh(descr, 0, materials[0]);

		m_Meshes.push_back(pMesh);

		return MakeMeshHandle(pMesh);
	}
	else
		return 0;
}

VOpenGLDevice::MaterialHandle VOpenGLDevice::CreateMaterial(
	const VMaterialDescription& in_MatDesc)
{
	return m_StateCategories.CreateRenderStateList(in_MatDesc);
}

void VOpenGLDevice::DeleteMaterial(MaterialHandle& in_Material)
{
	delete in_Material;
	in_Material = 0;
}

void VOpenGLDevice::DeleteMesh(MeshHandle& in_Mesh)
{
	//TODO
	// decrease reference count for all used buffers
	// maybe: delete buffers not needed anymore

	IVMesh* pMesh = MakeMeshPointer(in_Mesh);

	m_Meshes.remove(pMesh);

	delete pMesh;
	in_Mesh = 0;
}

//-----------------------------------------------------------------------------

void VOpenGLDevice::RenderMesh(MeshHandle in_pMesh)
{
	VMeshBase* pMesh = reinterpret_cast<VMeshBase*>(MakeMeshPointer(in_pMesh));

	pMesh->Render();
}

void VOpenGLDevice::RenderImmediate(
	VMeshDescription in_Mesh,
	VMaterialDescription in_Material
	)
{
	MaterialHandle pMaterial = CreateMaterial(in_Material);
	MeshHandle pMesh = m_ImmediateRenderMethod.CreateMesh(
		in_Mesh, 0, pMaterial);

	RenderMesh(pMesh);

	DeleteMesh(pMesh);
	DeleteMaterial(pMaterial);
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

    if (!(hDC=GetDC(hWnd)))

	if(m_DisplaySettings->m_bFullscreen)
	{
		DEVMODE DisplayFormat;

		DisplayFormat.dmSize		= sizeof(DEVMODE);
		DisplayFormat.dmPelsWidth	= m_DisplaySettings->m_iWidth;
		DisplayFormat.dmPelsHeight	= m_DisplaySettings->m_iHeight;
		DisplayFormat.dmBitsPerPel	= m_DisplaySettings->m_iBitsPerPixel;
		DisplayFormat.dmFields	    = DM_PELSWIDTH | DM_PELSHEIGHT |
													 DM_BITSPERPEL;

		if (ChangeDisplaySettings(&DisplayFormat, CDS_FULLSCREEN) !=
									DISP_CHANGE_SUCCESSFUL)
		{
			vout << "requesting fullscreen mode failed!" << vendl;
			m_DisplaySettings->m_bFullscreen = false;
		}
	}
	SetPixFormat();
	CreateContext();
	InitializeExtensions();
	SetScreenSize();
	SetBackgroundColor();

	glClearDepth(m_DisplaySettings->m_fClearDepth);
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

	PixelFormatDesc.cAccumBits		= m_DisplaySettings->m_iAccumulationBuffer;
	PixelFormatDesc.cDepthBits		= m_DisplaySettings->m_iDepthBits;
	PixelFormatDesc.cStencilBits	= m_DisplaySettings->m_iStencilBits;
	PixelFormatDesc.cColorBits		= m_DisplaySettings->m_iBitsPerPixel;

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
	if(m_DisplaySettings->m_iHeight <= 0) m_DisplaySettings->m_iHeight = 1;
	glViewport(0, 0, m_DisplaySettings->m_iWidth, m_DisplaySettings->m_iHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(m_DisplaySettings->m_fFieldOfView,
					((vfloat32)m_DisplaySettings->m_iWidth /
					m_DisplaySettings->m_iHeight),
					m_DisplaySettings->m_fNearClippingPlane,
					m_DisplaySettings->m_fFarClippingPlane);
	glMatrixMode(GL_MODELVIEW);
}
//-----------------------------------------------------------------------------

void VOpenGLDevice::SetBackgroundColor()
{
	glClearColor(m_DisplaySettings->m_fBackgroundRed,
				 m_DisplaySettings->m_fBackgroundGreen,
				 m_DisplaySettings->m_fBackgroundBlue,
				 m_DisplaySettings->m_fBackgroundAlpha);
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

	// fuer sowas solltes noch fkten geben - wir brauchen eine komplette state engine -ins
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

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

IVDevice::BufferHandle VOpenGLDevice::GetInternalVertexBuffer(
	BufferHandle in_hBuffer)
{
	BufferHandle hBuffer = 0;
	VByteBuffer* const buffer = static_cast<VByteBuffer*>(in_hBuffer);

	if( m_Buffers.Contains( buffer ) )
	{
		hBuffer = in_hBuffer;
	}
	else if( buffer != 0 )
	{
		hBuffer = CreateBuffer(VertexBuffer, buffer, VBufferBase::CopyData);
	}

	return hBuffer;
}

void VOpenGLDevice::InternalizeBuffers(VMeshDescription& io_MeshDescr)
{
	std::vector<BufferHandle> buffers = io_MeshDescr.GetAllBuffers();

    // for each buffer
	for(vuint bufId = 0; bufId < buffers.size(); ++bufId)
	{
		// get internal version
		BufferHandle hInternalBuffer = GetInternalVertexBuffer(buffers[bufId]);

		// replace all buffers in md which are equal to replaced buffer
		// by internal version
		io_MeshDescr.ReplaceBuffer(buffers[bufId], hInternalBuffer);
	}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
