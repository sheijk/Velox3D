#ifndef V3D_IVDEVICE_H
#define V3D_IVDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VBuffer.h>
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

/**
 * A graphical device. Abstraction of DirectGraphics/OpenGL/..
 * Unsuitable for children 3 years or younger ;)
 *
 * @author sheijk / ins
 */
class IVDevice
{
public:
	//typedef IVBuffer<vbyte>* BufferHandle;
	//typedef VBufferBase::CopyMode BufferCopyMode;
	//typedef VBuffer<vbyte> Buffer;
	typedef const IVMesh* MeshHandle;
	typedef const IVMaterial* MaterialHandle;

	//enum BufferType
	//{
	//	VertexBuffer,
	//	Texture
	//};

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
	virtual void DeleteMesh(MeshHandle& in_Mesh) = 0;


//weg
	//virtual MeshHandle CreateMesh(
	//	const VMeshDescription& in_MeshDescr,
	//	const VEffectDescription& in_EffectDescr
	//	) = 0;

	/** sends the vertices of a mesh to the device */
	virtual void RenderMesh(MeshHandle in_Mesh) = 0;

	/** applys a render state */
	virtual void ApplyState(const IVRenderState& in_State) = 0;

	/** set the projection, view, model and texture matrices */
	virtual void SetMatrix(MatrixMode in_Mode, const VMatrix44f& in_Matrix) = 0;

	virtual const VMatrix44f& GetMatrix(MatrixMode in_Mode) = 0;

	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;

	virtual ~IVDevice() {};
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDEVICE_H
