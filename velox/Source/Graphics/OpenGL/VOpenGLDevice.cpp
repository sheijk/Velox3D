#include "VOpenGLDevice.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/Wrappers/VIterator.h>

#include "VOpenGLVertexMesh.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics;
//-----------------------------------------------------------------------------
VOpenGLDevice::VOpenGLDevice(VDisplaySettings* in_pSettings, HWND in_hWnd)
{
	m_DisplaySettings = in_pSettings;
	hWnd = in_hWnd;
	SetDisplay();

	m_RenderMethods.RegisterRenderMethod(m_PlainRenderMethod);
	m_RenderMethods.RegisterRenderMethod(m_VBORenderMethod);

}
//-----------------------------------------------------------------------------

VOpenGLDevice::~VOpenGLDevice()
{
	DestroyContext();
}
//-----------------------------------------------------------------------------

//void VOpenGLDevice::ApplyMaterial(IVMaterial* in_pMaterial)
//{
//}
//-----------------------------------------------------------------------------

//IVMaterial* VOpenGLDevice::CreateMaterial()
//{
//	return NULL;
//}
//-----------------------------------------------------------------------------

IVDevice::FloatBufferHandle VOpenGLDevice::CreateBuffer(
	VFloatBuffer* in_pBuffer,
	BufferCopyMode in_CopyMode
	)
{
	VFloatBuffer* pBuffer = in_pBuffer->CreateCopy(in_CopyMode);
	m_FloatBuffer.Add(pBuffer);

	return FloatBufferHandle(pBuffer);
}

void VOpenGLDevice::DeleteBuffer(BufferHandle& in_Buffer)
{
	VFloatBuffer* t = reinterpret_cast<VFloatBuffer*>(in_Buffer);
	m_FloatBuffer.Delete(t);
	in_Buffer = t;
}

IVDevice::MeshHandle VOpenGLDevice::CreateMesh(VMeshDescription& in_pMeshDesc)
{
	IVMesh* pMesh = m_RenderMethods.CreateMesh(in_pMeshDesc, 0);

	m_Meshes.push_back(pMesh);

	return *pMesh;
}

void VOpenGLDevice::DeleteMesh(MeshHandle in_Mesh)
{
	IVMesh* pMesh = &in_Mesh;

	m_Meshes.remove(pMesh);

	delete pMesh;
}

//-----------------------------------------------------------------------------

void VOpenGLDevice::RenderMesh(MeshHandle in_pMesh)
{
	VBaseMesh* pMesh = reinterpret_cast<VBaseMesh*>(&in_pMesh);

	pMesh->Render();
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

	// fuer sowas solltes noch fkten geben
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity();
	
	//TODO for testing purpose -ins
	static vfloat32 rotZ = 0;
	glTranslatef(0.0f, 0.0f, -5.0f);
	rotZ += 0.3f;
	glRotatef(rotZ,0.0f,1.0f,0.0f);

}

//-----------------------------------------------------------------------------
void VOpenGLDevice::EndScene()
{
	wglMakeCurrent(hDC, hRC);
	SwapBuffers(hDC);
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
