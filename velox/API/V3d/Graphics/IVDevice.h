#ifndef V3D_IVDEVICE_H
#define V3D_IVDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVMesh.h>
#include <v3d/Graphics/IVMaterial.h>
#include <v3d/Graphics/VBuffer.h>
#include <v3d/Graphics/VMeshDescription.h>

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
	// deprecated, beeing removed -- sheijk
	typedef VMeshDescription::FloatBufferHandle FloatBufferHandle;
	typedef VMeshDescription::IntBufferHandle IntBufferHandle;
	typedef VFloatBuffer::CopyMode FloatBufferCopyMode;
	typedef VIntBuffer::CopyMode  IntBufferCopyMode;

	/** a handle to a device buffer */
	typedef VMeshDescription::ByteBufferHandle BufferHandle;

	typedef VBufferBase::CopyMode BufferCopyMode;

	typedef VBuffer<vbyte> Buffer;

	typedef IVMesh* MeshHandle;

	enum BufferType
	{
		VertexBuffer,
		IndexBuffer
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

	/** creates an internal buffer in the device */
	//virtual FloatBufferHandle CreateBuffer(
	//	VFloatBuffer* in_pBuffer,
	//	FloatBufferCopyMode in_CopyMode = VFloatBuffer::CopyData
	//	) = 0;

	//virtual IntBufferHandle CreateBuffer(
	//	VIntBuffer* in_pBuffer,
	//	IntBufferCopyMode in_CopyMode = VIntBuffer::CopyData
	//	) = 0;

	/** deletes the buffer and sets the handle to 0 */
	virtual void DeleteBuffer(BufferHandle& in_Buffer) = 0;

	/** create a mesh ins the device */
	virtual MeshHandle CreateMesh(VMeshDescription& in_pMeshDesc) = 0;
	virtual void DeleteMesh(MeshHandle in_Mesh) = 0;

	//virtual IVMaterial* CreateMaterial() = 0;
	//virtual void ApplyMaterial(IVMaterial* in_pMatrial) = 0;

	/** sends the vertices of a mesh to the device */
	virtual void RenderMesh(MeshHandle in_Mesh) = 0;

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
