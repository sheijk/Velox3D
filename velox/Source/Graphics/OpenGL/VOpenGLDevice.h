#ifndef V3D_VOPENGLDEVICE_H
#define V3D_VOPENGLDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Graphics/VDisplaySettings.h>

#include "../DeviceBase/VBufferManager.h"
#include "../DeviceBase/VRenderMethodRegistry.h"
//#include "VOpenGLVertexMesh.h"
#include "VOpenGLPlainRenderMethod.h"
#include "VOpenGLVBORenderMethod.h"

#include <windows.h>
#include <extgl/extgl.h>
#include <gl/gl.h>
#include <gl/glu.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A graphic device on top of OpenGL
 *
 * @author sheijk/insane
 */
class VOpenGLDevice : public IVDevice
{
public:
	/** Contructor for adding a window */
	VOpenGLDevice(graphics::VDisplaySettings* in_pSettings, HWND in_hWnd);
	virtual ~VOpenGLDevice();

	virtual FloatBufferHandle CreateBuffer(
		VFloatBuffer* in_pBuffer, 
		BufferCopyMode in_CopyMode = VFloatBuffer::CopyData
		);

	virtual void DeleteBuffer(BufferHandle& in_Buffer);

	virtual MeshHandle CreateMesh(VMeshDescription& in_pMeshDesc);
	virtual void DeleteMesh(MeshHandle in_Mesh);

	virtual void RenderMesh(MeshHandle in_Mesh);

	virtual void BeginScene();
	virtual void EndScene();
	
private:
	/** the float buffers */
	VBufferManager<VFloatBuffer> m_FloatBuffer;

	/** store all render methods here */
	VRenderMethodRegistry m_RenderMethods;
	VOpenGLPlainRenderMethod m_PlainRenderMethod;
	VOpenGLVBORenderMethod m_VBORenderMethod;

	typedef std::list<IVMesh*> MeshList;
	MeshList m_Meshes;

	/**
	 * All gl internal calling methods
	 */
	
	void SetDisplay();
	void SetPixFormat();
	void CreateContext();
	void DestroyContext();
	void SetScreenSize();
	void SetBackgroundColor();
	void InitializeExtensions(); // using extgl

	/**
	 * Device dependant variables:
	 */
	graphics::VDisplaySettings* m_DisplaySettings;
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;

	vchar		*m_pVendor;
	vchar		*m_pRenderer;
	vchar		*m_pVersion;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VOPENGLDEVICE_H
