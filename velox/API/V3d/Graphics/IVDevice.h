#ifndef V3D_IVDEVICE_H
#define V3D_IVDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVMesh.h>
#include <v3d/Graphics/IVMaterial.h>
#include <v3d/Graphics/VBuffer.h>
#include <v3d/Graphics/VMeshDescription.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A graphical device. Abstraction of DirectGraphics/OpenGL/..
 *
 * @author sheijk / ins
 */
class IVDevice
{
public:
	typedef VMeshDescription::BufferHandle BufferHandle;
	typedef VMeshDescription::FloatBufferHandle FloatBufferHandle;
	typedef VMeshDescription::IntBufferHandle IntBufferHandle;

	typedef IVMesh* MeshHandle;

	virtual ~IVDevice() {};

	//changed - ins
	typedef VFloatBuffer::CopyMode FloatBufferCopyMode;
	typedef VIntBuffer::CopyMode  IntBufferCopyMode;

	/** creates an internal buffer in the device */
	virtual FloatBufferHandle CreateBuffer(
		VFloatBuffer* in_pBuffer,
		FloatBufferCopyMode in_CopyMode = VFloatBuffer::CopyData) = 0;

	virtual IntBufferHandle CreateBuffer(
		VIntBuffer* in_pBuffer,
		IntBufferCopyMode in_CopyMode = VIntBuffer::CopyData) = 0;

	/** deletes the buffer and sets the handle to 0 */
	virtual void DeleteBuffer(BufferHandle& in_Buffer) = 0;

	/** create a mesh ins the device */
	virtual MeshHandle CreateMesh(VMeshDescription& in_pMeshDesc) = 0;
	virtual void DeleteMesh(MeshHandle in_Mesh) = 0;

	//virtual IVMaterial* CreateMaterial() = 0;
	//virtual void ApplyMaterial(IVMaterial* in_pMatrial) = 0;
	virtual void RenderMesh(MeshHandle in_Mesh) = 0;

	/**
	* This is only implemented to show anything by now
	* TODO: build the damn renderer ;)
	*/
	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDEVICE_H
