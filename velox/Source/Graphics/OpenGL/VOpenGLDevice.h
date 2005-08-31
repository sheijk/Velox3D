#ifndef V3D_VOPENGLDEVICE_H
#define V3D_VOPENGLDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VTypeInfo.h>
#include <v3d/Graphics/IVDevice.h>
#include <V3d/Graphics/IVRenderContext.h>

#include <v3d/Graphics/VDisplaySettings.h>
#include <V3d/Math/VMatrix.h>

#include <V3d/OpenGL.h>

//#include "../DeviceBase/VBufferManager.h"

#include "../DeviceBase/VMaterial.h"
#include "../DeviceBase/VStateCategoryList.h"
#include "VTextureStateCategory.h"
#include "VMiscStateCategory.h"
#include "VVertexShaderCategory.h"
#include "../DeviceBase/VMeshBase.h"

#include <V3d/Resource/VResourceDataPtr.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // using no auto indent

/**
 * A graphic device on top of OpenGL
 *
 * @author sheijk/insane
 */
class VOpenGLDevice : public IVDevice
{
public:
	/** Contructor for adding a window */
	VOpenGLDevice(
		const graphics::VDisplaySettings& in_Settings,
		IVRenderContext* in_pContext);
	virtual ~VOpenGLDevice();

	virtual MeshHandle CreateMesh(VStringParam in_strResource);
	virtual MaterialHandle CreateMaterial(VStringParam in_strResource);

	virtual void DeleteMesh(MeshHandle& in_Mesh);

	virtual void RenderMesh(MeshHandle in_Mesh);

	virtual void ApplyState(const IVRenderState& in_State);

	virtual void BeginScene();
	virtual void EndScene();

	virtual void SetMatrix(MatrixMode in_Mode, const VMatrix44f& in_Matrix);

	virtual const VMatrix44f& GetMatrix(MatrixMode in_Mode);
	
	void ApplyLight(LightId in_Number, const VPointLight* in_pLight);
	const VPointLight& GetLight(LightId in_Number) const;

	IVRenderContext* CreateOffscreenContext(const graphics::VDisplaySettings* in_pDisplaySettings);

private:
	void RecalcModelViewMatrix();

	resource::VResourceDataPtr<const IVMaterial> m_pDefaultMaterial;

	//// render state categories
	//VStateCategoryList m_StateCategories;
	//VTextureStateCategory m_TextureStateCategory;
	//VMiscStateCategory m_MiscStateCategory;
	//VVertexShaderCategory m_VertexShaderCategory;
	//VPixelShaderCategory m_PixelShaderCategory;

	typedef std::list<VMeshBase*> MeshList;
	MeshList m_Meshes;

	// lights
	std::vector<VPointLight> m_PointLights;

	// the matrices
	VMatrix44f m_ViewMatrix;
	VMatrix44f m_ModelMatrix;
	VMatrix44f m_ProjectionMatrix;
	VMatrix44f m_TextureMatrix;

	void SetDisplay();
	//void SetPixFormat();
	//void CreateContext();
	//void DestroyContext();
	void SetScreenSize();
	void SetBackgroundColor();
	void InitializeExtensions(); // using extgl

	/**
	 * Device dependant variables:
	 */
	graphics::VDisplaySettings m_DisplaySettings;

	IVRenderContext* m_pContext;

	//HWND hWnd;
	//HDC hDC;
	//HGLRC hRC;

	vchar* m_pVendor;
	vchar* m_pRenderer;
	vchar* m_pVersion;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
V3D_TYPEINFO(v3d::graphics::IVDevice);
V3D_TYPEINFO_WITHPARENT(v3d::graphics::VOpenGLDevice, v3d::graphics::IVDevice);

#endif // V3D_VOPENGLDEVICE_H
