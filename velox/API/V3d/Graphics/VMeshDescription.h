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
		LineStrip
	};

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

		Buffer hBuffer;
		vuint nStart;
		vuint nCount;
        vuint nStride;
	};

	typedef DataRef<ByteBufferHandle> ByteDataRef;

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
