#ifndef V3D_IVDEVICE_H
#define V3D_IVDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVMesh.h>
#include <v3d/Graphics/IVMaterial.h>
#include <v3d/Graphics/VBuffer.h>
#include <v3d/Graphics/VMeshDescription.h>
#include <v3d/Graphics/VMaterialDescription.h>
#include <v3d/Graphics/IVRenderState.h>

#include <v3d/Graphics/VCamera.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A graphical device. Abstraction of DirectGraphics/OpenGL/..
 * Unsuitable for children 3 years or younger ;)
 *
 * @author sheijk / ins
 */
class IVDevice
{
public:
	/** a handle to a device buffer */
	typedef VMeshDescription::ByteBufferHandle BufferHandle;

	typedef VBufferBase::CopyMode BufferCopyMode;

	typedef VBuffer<vbyte> Buffer;

	typedef IVMesh* MeshHandle;

	typedef IVMaterial* MaterialHandle;

	enum BufferType
	{
		VertexBuffer,
		Texture
	};

	/** 
	 * creates a buffer inside the device which can be referred to using
	 * the given handle
	 *
	 * @param in_Type the type of data the buffer contains (buffer may only
	 * be used for the given usage
	 * @param in_pBuffer the address of the data
	 * @param in_CopyMode copy the data or transfer ownership to device
	 */
	virtual BufferHandle CreateBuffer(
		BufferType in_Type,
        Buffer* in_Buffer,
		BufferCopyMode in_CopyMode = VBufferBase::CopyData
		) = 0;

	/** deletes the buffer and sets the handle to 0 */
	virtual void DeleteBuffer(BufferHandle& in_Buffer) = 0;

	/** create a mesh ins the device */
	//virtual MeshHandle CreateMesh(VMeshDescription& in_pMeshDesc) = 0;
	virtual MeshHandle CreateMesh(
		const VMeshDescription& in_pMeshDesc,
		const VMaterialDescription& in_pMaterialDesc
		) = 0;

	virtual void DeleteMesh(MeshHandle& in_Mesh) = 0;

	//virtual MaterialHandle CreateMaterial(
	//	const VMaterialDescription& in_MatDesc) = 0;

	virtual void DeleteMaterial(MaterialHandle& in_Material) = 0;

	/** sends the vertices of a mesh to the device */
	virtual void RenderMesh(MeshHandle in_Mesh) = 0;

	/** applys a render state */
	virtual void ApplyState(const IVRenderState& in_State) = 0;

	// evil hack :)
	virtual void SetCamera(VCamera* in_pCamera) = 0;

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
