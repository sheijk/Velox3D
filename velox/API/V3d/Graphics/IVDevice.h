/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVDEVICE_H
#define V3D_IVDEVICE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/VBuffer.h>
#include <V3d/Graphics/IVRenderContext.h>
#include <V3d/Resource/VResourceDataPtr.h>
#include <V3d/Math/VMatrix.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
class VMeshDescription;
class VEffectDescription;
struct VMaterialDescription;
class IVRenderState;
class IVMesh;
class IVMaterial;
class VLight;

/**
 * A graphical device. Abstraction of DirectGraphics/OpenGL/..
 * Unsuitable for children 3 years or younger ;)
 *
 * @author sheijk / ins
 */
class IVDevice
{
public:
	typedef const IVMesh* MeshHandle;
	typedef const IVMaterial* MaterialHandle;

	enum MatrixMode
	{
		ProjectionMatrix,
		TextureMatrix,
		ModelMatrix,
		ViewMatrix
	};

	/**
	 * Use GetResourceData<IVMesh>(in_strResource) instead
	 *
	 * Returns a mesh handle to render the given geometry using the effect
	 * description's materials. Mesh must be deleted using DeleteMesh
	 * before end of program
	 *
	 * @param in_strResource Name and path of the resource containing a
	 *		VEffectDescription and a VMeshDescription
	 * @return A handle which can be used to render the mesh
	 */
	virtual V3D_DEPRECATED MeshHandle CreateMesh(
		VStringParam in_strResource
		) = 0;

	/** Use GetResourceData<IVMaterial>(in_strResource) instead */
	virtual V3D_DEPRECATED MaterialHandle CreateMaterial(VStringParam in_strResource) = 0;

	/**
	 * Deletes a previously created mesh
	 */
	virtual V3D_DEPRECATED void DeleteMesh(MeshHandle& in_Mesh) = 0;

	virtual void RenderMesh(MeshHandle in_Mesh) = 0;

	/** sends the vertices of a mesh to the device */
	//virtual void SendGeometry(MeshHandle in_Mesh) = 0;

	/** applys a render state */
	virtual void ApplyState(const IVRenderState& in_State) = 0;

	/** set the projection, view, model and texture matrices */
	virtual void SetMatrix(MatrixMode in_Mode, const math::VMatrix44f& in_Matrix) = 0;

	/** Returns the current matrix */
	virtual const math::VMatrix44f& GetMatrix(MatrixMode in_Mode) = 0;

	/**
	 * Begin rendering to the render target. All render calls and state settings
	 * must occur between BeginScene and EndScene
	 */
	virtual void BeginScene() = 0;

	enum EndSceneFlags
	{
		NoFlip,
		FlipScene
	};

	/**
	 * End rendering to the render target and flip buffer. Other render targets
	 * may not begin their scene before EndScene has been called
	 */
	virtual void EndScene(EndSceneFlags in_Flags = FlipScene) = 0;

	virtual void Flip() = 0;

	enum ClearFlags
	{
		ClearColor = 1,
		ClearZ = 2,
		ClearAll = 3
	};

	virtual void Clear(ClearFlags in_Flags = ClearAll) = 0;


	virtual void SetClearColor(
		vfloat32 red, vfloat32 green, vfloat32 blue, vfloat32 alpha) = 0;

	virtual void SetViewport(vint left, vint top, vint right, vint bottom) = 0;


	/** Returns true if and only if between calls to BeginScene and EndScene */
	virtual vbool IsActive() const = 0;

	typedef vuint LightId;

	/** 
	 * Id of the maximum active light. Note: some lights with 
	 * id < MaxActiveLight() might be disabled
	 */
	virtual LightId MaxActiveLight() const = 0;

	/** Set a point light. Pass a zero pointer to disable light */
	virtual void ApplyLight(LightId in_Number, const VLight* in_pLight) = 0;

	/** Get active light. Might return 0 if the given light id is not active */
	virtual const VLight* GetLight(LightId in_Number) const = 0;

	virtual IVRenderContext* CreateOffscreenContext(const graphics::VDisplaySettings* in_pDisplaySettings) = 0;

	virtual IVRenderContext* GetRenderContext() = 0;

	virtual ~IVDevice() {};

	static resource::VResourceDataPtr<const IVMaterial> GetDefaultMaterial();
};
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
V3D_TYPEINFO(v3d::graphics::IVDevice);

#endif // V3D_IVDEVICE_H

