#include <v3d/Graphics/VOpenGLDevice.h>
#include <v3d/Core/VIOStream.h>
#include <v3d/Graphics/OpenGL/VOpenGLVertexMesh.h>
#include <v3d/Core/Wrappers/VIterator.h>
//-----------------------------------------------------------------------------
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
}
//-----------------------------------------------------------------------------

VOpenGLDevice::~VOpenGLDevice()
{
	DestroyContext();
}
//-----------------------------------------------------------------------------

void VOpenGLDevice::ApplyMaterial(IVMaterial* in_pMaterial)
{
}
//-----------------------------------------------------------------------------

IVMaterial* VOpenGLDevice::CreateMaterial()
{
	return NULL;
}
//-----------------------------------------------------------------------------

IVMesh* VOpenGLDevice::CreateMesh(IVMeshDescription* in_pMeshDesc)
{
	typedef VBidirectionalIterator<const VTriangle> TriangleIterator;
    
	
	VOpenGLVertexMesh* Mesh = new VOpenGLVertexMesh;
	
	for(TriangleIterator iter = in_pMeshDesc->TriangleBegin();
		iter != in_pMeshDesc->TriangleEnd(); iter++)
	{
		for(vuint i = 0; i < 3; i++)
		{
			Mesh->m_VertexList.push_back(iter->GetVertex(i));
		}
	}

	return Mesh;
}
//-----------------------------------------------------------------------------

void VOpenGLDevice::RenderMesh(IVMesh* in_pMesh)
{
	VOpenGLMesh* Mesh = reinterpret_cast<VOpenGLMesh*>(in_pMesh);

	if(Mesh->m_Type == Mesh->VertexMode)
	{
		VOpenGLVertexMesh* vmesh = reinterpret_cast<VOpenGLVertexMesh*>(Mesh);
		
		/*static vfloat32 rotZ = 0;
		rotZ += 0.1f;
		glRotatef(rotZ,0.0f,0.0f,1.0f);*/

		glTranslatef(-0.0f,0.0f,-2.0f);	

		glBegin(GL_TRIANGLES);
		for (vuint i = 0; i < vmesh->m_VertexList.size(); i++)
		{
			glVertex3f(vmesh->m_VertexList[i].Get(0),
					   vmesh->m_VertexList[i].Get(1),
					   vmesh->m_VertexList[i].Get(2));
		}		
		glEnd();
	}
	
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
	vuint Length = strlen(Extensions);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity();
	
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
