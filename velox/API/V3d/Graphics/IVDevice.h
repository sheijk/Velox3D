#ifndef V3D_IVDEVICE_H
#define V3D_IVDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VBuffer.h>
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
class VPointLight;

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
	 * Returns a mesh handle to render the given geometry using the effect
	 * description's materials. Mesh must be deleted using DeleteMesh
	 * before end of program
	 *
	 * @param in_strResource Name and path of the resource containing a
	 *		VEffectDescription and a VMeshDescription
	 * @return A handle which can be used to render the mesh
	 */
	virtual MeshHandle CreateMesh(
		VStringParam in_strResource
		) = 0;

	virtual MaterialHandle CreateMaterial(VStringParam in_strResource) = 0;

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
	virtual void SetMatrix(MatrixMode in_Mode, const VMatrix44f& in_Matrix) = 0;

	/** Returns the current matrix */
	virtual const VMatrix44f& GetMatrix(MatrixMode in_Mode) = 0;

	/**
	 * Begin rendering to the render target. All render calls and state settings
	 * must occur between BeginScene and EndScene
	 */
	virtual void BeginScene() = 0;

	/**
	 * End rendering to the render target and flip buffer. Other render targets
	 * may not begin their scene before EndScene has been called
	 */
	virtual void EndScene() = 0;

	/** Id's of the lights */
	enum LightId
	{
		Light0, Light1, Light2, Light3, Light4, Light5, Light6, Light7, LightMaxCount
	};

	/**
	 * Set a point light. Pass a zero pointer to disable light
	 */
	virtual void ApplyLight(LightId in_Number, const VPointLight* in_pLight) = 0;

	virtual IVRenderContext* CreateOffscreenContext(const graphics::VDisplaySettings* in_pDisplaySettings) = 0;

	virtual ~IVDevice() {};
};
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
V3D_TYPEINFO(v3d::graphics::IVDevice);

#endif // V3D_IVDEVICE_H
