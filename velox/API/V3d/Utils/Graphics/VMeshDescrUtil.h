#ifndef V3D_/*filename*/_H
#define V3D_/*filename*/_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VMeshDescription.h>
#include <v3d/Graphics/IVDevice.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VMeshDescription BuildMeshDescription(
	IVDevice::FloatBufferHandle in_hHandle,
	VVertexDataLayout in_Layout
	)
{
	VMeshDescription descr;

	descr.triangleVertices.hBuffer = in_hHandle;
	descr.triangleVertices.nStride = in_Layout.vertexOffset;
TODO:
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_/*filename*/_H
