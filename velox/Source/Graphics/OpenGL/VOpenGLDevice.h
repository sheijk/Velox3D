#ifndef V3D_VOPENGLDEVICE_H
#define V3D_VOPENGLDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Graphics/VDisplaySettings.h>

#include <windows.h>
#include <extgl/extgl.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "../DeviceBase/VBufferManager.h"
#include "../DeviceBase/VRenderMethodRegistry.h"
#include "VImmediateRenderMethod.h"
#include "VOpenGLVBORenderMethod.h"

#include "../DeviceBase/VRenderStateList.h"
#include "../DeviceBase/VStateCategoryList.h"
#include "VTextureStateCategory.h"
#include "VMiscStateCategory.h"
#include "VBlendingStateCategory.h"
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
	VOpenGLDevice(const graphics::VDisplaySettings* in_pSettings, HWND in_hWnd);
	virtual ~VOpenGLDevice();

	virtual BufferHandle CreateBuffer(
		BufferType in_Type,
		Buffer* in_Buffer,
		BufferCopyMode in_CopyMode = VBufferBase::CopyData
		);

	virtual void DeleteBuffer(BufferHandle& in_Buffer);

	virtual void OverwriteBuffer(
		BufferHandle& in_hBuffer,
		vuint in_nFirstElement,
		vuint in_nCount,
		const vbyte* in_pBuffer
		);

	virtual MeshHandle CreateMesh(
		const VMeshDescription& in_pMeshDesc,
		const VMaterialDescription& in_pMaterialDesc
		) ;

	virtual void DeleteMesh(MeshHandle& in_Mesh);

	virtual MaterialHandle CreateMaterial(const VMaterialDescription& in_MatDesc);
	virtual void DeleteMaterial(MaterialHandle& in_Material);

	virtual void RenderMesh(MeshHandle in_Mesh);

	virtual void RenderImmediate(
		VMeshDescription in_Mesh,
		VMaterialDescription in_Material
		);

	virtual void ApplyState(const IVRenderState& in_State);

	virtual void BeginScene();
	virtual void EndScene();

	virtual void SetMatrix(MatrixMode in_Mode, const VMatrix44f& in_Matrix);

	virtual const VMatrix44f& GetMatrix(MatrixMode in_Mode);
	
private:
	void RecalcModelViewMatrix();

	/** vertex buffers */
	VBufferManager<Buffer> m_Buffers;

	/** texture buffers */
	VBufferManager<Buffer> m_TextureBuffers;

	/** store all render methods here */
	VRenderMethodRegistry m_RenderMethods;

	VImmediateRenderMethod m_ImmediateRenderMethod;
	VOpenGLVBORenderMethod m_VBORenderMethod;

	VStateCategoryList m_StateCategories;
	VTextureStateCategory m_TextureStateCategory;
	VMiscStateCategory m_MiscStateCategory;
	VBlendingStateCategory m_BlendingStateCategory;
	

	typedef std::list<IVMesh*> MeshList;
	MeshList m_Meshes;

	// the matrices
	VMatrix44f m_ViewMatrix;
	VMatrix44f m_ModelMatrix;
	VMatrix44f m_ProjectionMatrix;
	VMatrix44f m_TextureMatrix;

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
