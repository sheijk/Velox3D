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
	typedef IVBuffer<vbyte>* BufferHandle;
	typedef VBufferBase::CopyMode BufferCopyMode;
	typedef VBuffer<vbyte> Buffer;
	typedef IVMesh* MeshHandle;
	typedef IVMaterial* MaterialHandle;

	enum BufferType
	{
		VertexBuffer,
		Texture
	};

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
	 */
	virtual MeshHandle CreateMesh(
		VStringParam in_strMeshDescrResName,
		VStringParam in_strEffectDescrResName
		) = 0;

	/**
	 * Deletes a previously created mesh
	 */
	virtual void DeleteMesh(MeshHandle& in_Mesh) = 0;

	/**
	 * creates a buffer inside the device which can be referred to using
	 * the given handle
	 *
	 * @param in_Type the type of data the buffer contains (buffer may only
	 * be used for the given usage
	 * @param in_pBuffer the address of the data
	 * @param in_CopyMode copy the data or transfer ownership to device
	 */
//weg
	virtual BufferHandle CreateBuffer(
		BufferType in_Type,
        const Buffer* in_Buffer,
		BufferCopyMode in_CopyMode = VBufferBase::CopyData
		) = 0;

	/** deletes the buffer and sets the handle to 0 */
//weg
	virtual void DeleteBuffer(BufferHandle& in_Buffer) = 0;

	/**
	 * Overwrites a part of a buffer with new data. Only overwrites existing
	 * data. Can not change the buffers size. Take care not to write over the
	 * end of the buffer
	 */
//weg
	virtual void OverwriteBuffer(
		BufferHandle& in_hBuffer,
		vuint in_nFirstElement,
		vuint in_nCount,
		const vbyte* in_pBuffer
		) = 0;

//weg
	/** create a mesh ins the device */
	//virtual MeshHandle CreateMesh(VMeshDescription& in_pMeshDesc) = 0;
	virtual MeshHandle CreateMesh(
		const VMeshDescription& in_pMeshDesc,
		const VMaterialDescription& in_pMaterialDesc
		) = 0;

//weg
	virtual MeshHandle CreateMesh(
		const VMeshDescription& in_MeshDescr,
		const VEffectDescription& in_EffectDescr
		) = 0;

	//virtual MaterialHandle CreateMaterial(
	//	const VMaterialDescription& in_MatDesc) = 0;

//weg
	virtual void DeleteMaterial(MaterialHandle& in_Material) = 0;

	/** sends the vertices of a mesh to the device */
	virtual void RenderMesh(MeshHandle in_Mesh) = 0;

	/**
	 * creates mesh and material on the fly and renders them. mesh and
	 * material will only be created temporarily
	 */
	virtual void RenderImmediate(
		VMeshDescription in_Mesh,
		VMaterialDescription in_Material
		) = 0;

	/** applys a render state */
	virtual void ApplyState(const IVRenderState& in_State) = 0;

	/** set the projection, view, model and texture matrices */
	virtual void SetMatrix(MatrixMode in_Mode, const VMatrix44f& in_Matrix) = 0;

	virtual const VMatrix44f& GetMatrix(MatrixMode in_Mode) = 0;

	/**
	* This is only implemented to show anything by now
	* TODO: build the damn renderer ;)
	*/
	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;

	virtual ~IVDevice() {};
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDEVICE_H
