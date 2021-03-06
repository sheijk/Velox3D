/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VOPENGLDEVICE_H
#define V3D_VOPENGLDEVICE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics/IVRenderContext.h>

#include <V3d/Graphics/VDisplaySettings.h>

#include <V3d/Math/VMatrix.h>
#include <V3d/Math/VRBTransform.h>

#include <V3d/OpenGL.h>

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

	virtual V3D_DEPRECATED MeshHandle CreateMesh(VStringParam in_strResource);
	virtual V3D_DEPRECATED MaterialHandle CreateMaterial(VStringParam in_strResource);

	virtual void DeleteMesh(MeshHandle& in_Mesh);

	virtual void RenderMesh(MeshHandle in_Mesh);

	virtual void ApplyState(const IVRenderState& in_State);

	virtual void BeginScene();
	virtual void EndScene(EndSceneFlags in_Flags);
	virtual void Flip();

	virtual void Clear(ClearFlags in_Flags = ClearAll);	
	virtual void SetViewport(vint left, vint top, vint right, vint bottom);

	virtual void SetClearColor(
		vfloat32 red, vfloat32 green, vfloat32 blue, vfloat32 alpha);

	virtual vbool IsActive() const;

	virtual void SetMatrix(MatrixMode in_Mode, const math::VMatrix44f& in_Matrix);
	virtual const math::VMatrix44f& GetMatrix(MatrixMode in_Mode) const;

	virtual void SetProjectionMatrix(const math::VMatrix44f& in_Matrix);
	virtual const math::VMatrix44f& GetProjectionMatrix() const;
	virtual void SetModelMatrix(const math::VMatrix44f& in_Matrix);
	virtual const math::VMatrix44f& GetModelMatrix() const;
	virtual const math::VRBTransform& GetViewTransform() const;
	virtual void SetViewTransform(const math::VRBTransform& in_Transform);
	virtual const math::VMatrix44f& GetViewMatrix() const;
	
	virtual LightId MaxActiveLight() const;
	void ApplyLight(LightId in_Number, const VLight* in_pLight);
	virtual const VLight* GetLight(LightId in_Number) const;
	//const VPointLight& GetLight(LightId in_Number) const;

	IVRenderContext* CreateOffscreenContext(const graphics::VDisplaySettings* in_pDisplaySettings);

	virtual IVRenderContext* GetRenderContext();
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

	vbool m_bActive;

	// lights
	std::vector<const VLight*> m_Lights;
	//std::vector<VPointLight> m_PointLights;

	VColor4f m_ClearColor;

	// the matrices
	//math::VMatrix44f m_ViewMatrix;
	math::VRBTransform m_ViewTransform;
	math::VMatrix44f m_ViewMatrix;
	math::VMatrix44f m_ModelMatrix;
	math::VMatrix44f m_ProjectionMatrix;
	math::VMatrix44f m_TextureMatrix;

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
V3D_TYPEINFO_WITHPARENT(v3d::graphics::VOpenGLDevice, v3d::graphics::IVDevice);

#endif // V3D_VOPENGLDEVICE_H

