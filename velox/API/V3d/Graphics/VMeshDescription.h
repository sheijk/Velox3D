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
 * Describes in which device buffers the data for a mesh is
 *
 * @author sheijk
 */
struct VMeshDescription
{
	typedef VBufferBase* BufferHandle;
	typedef IVBuffer<vfloat32>* FloatBufferHandle;
	typedef IVBuffer<vint32>* IntBufferHandle;

	template<typename Buffer>
		struct DataRef
	{
		DataRef()
		{
			hBuffer = 0;
			nStart = nCount = nStride = 0;
		}

		DataRef(
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

		Buffer hBuffer;
		vuint nStart;
		vuint nCount;
        vuint nStride;
	};

	typedef DataRef<FloatBufferHandle> FloatDataRef;
	typedef DataRef<IntBufferHandle> IntDataRef;

	FloatDataRef triangleVertices; // extra felder fuer tris, fans + strips? -wozu?
	//vertex array hat nichts mit rendering mode zu tun. sollte evtl in IndexBuffer stehen
	FloatDataRef triangleColors;
	FloatDataRef triangleCoords;
	IntDataRef triangleIndices;

};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMESHDESCRIPTION_H
