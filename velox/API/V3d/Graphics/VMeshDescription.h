#ifndef V3D_VMESHDESCRIPTION_H
#define V3D_VMESHDESCRIPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VBuffer.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Describes which data to use for a mesh and how to interprete it
 * Requires that all used data is already loaded into the mesh
 *
 * @author sheijk
 */
struct VMeshDescription
{
	typedef IVBuffer<vbyte>* ByteBufferHandle;

	enum GeometryType
	{
		Triangles,
		TriangleStrip,
		TriangleFan,
		Quads,
		QuadStrip,
		Lines,
		LineStrip,
		Points
	};

	/**
	 * References which buffer to be used and how data is aligned in buffer
	 */
	template<typename Buffer>
	struct DataRef
	{
		DataRef();

		DataRef(
			Buffer in_hBuffer,
			vuint in_nStart,
			vuint in_nCount,
			vuint in_nStride
			);

		/** The device's buffer handle of the loaded buffer */
		Buffer hBuffer;
		/** index of first element of buffer to be used */
		vuint nStart;
		/** number of elements to be used */
		vuint nCount;
		/** number of floats(!) between the beginning of two structs */
        vuint nStride;
	};

	/** references data inside a buffer of bytes */
	typedef DataRef<ByteBufferHandle> ByteDataRef;

	/** 
	 * The type of primitives to be used for rendering
	 */
	GeometryType geometryType;

	ByteDataRef triangleVertices;
	ByteDataRef triangleColors;
	ByteDataRef triangleTexCoords;
	ByteDataRef triangleIndices;

	VMeshDescription() : geometryType(Triangles) {}
};

//-----------------------------------------------------------------------------
template<typename Buffer>
VMeshDescription::DataRef<Buffer>::DataRef()
{
	hBuffer = 0;
	nStart = nCount = nStride = 0;
}


template<typename Buffer>
VMeshDescription::DataRef<Buffer>::DataRef(
		Buffer in_hBuffer,
		vuint in_nStart,
		vuint in_nCount,
		vuint in_nStride
		)
{
	hBuffer = in_hBuffer;
	nStart = in_nStart;
	nCount = in_nCount;
	nStride = in_nStride;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMESHDESCRIPTION_H
