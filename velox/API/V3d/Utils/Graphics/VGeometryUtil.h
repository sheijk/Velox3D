#ifndef V3D_VGEOMETRYUTIL_H
#define V3D_VGEOMETRYUTIL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Utils/Graphics/VVertex3f.h>
#include <v3d/Utils/Graphics/VColor4f.h>
#include <v3d/Utils/Graphics/VVertexDataLayout.h>

#include <v3d/Graphics/IVDevice.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace util {
//-----------------------------------------------------------------------------

/**
 * Takes an array of vertices and builds a mesh description of it
 */
template<typename VertexStructure>
v3d::graphics::VMeshDescription BuildMeshDescription(
	v3d::graphics::IVDevice& in_Device,
	VertexStructure pVertices[],
	const vuint in_cnVertexCount
	);

//-----------------------------------------------------------------------------
#include "VGeometryUtil.inl"
//-----------------------------------------------------------------------------
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGEOMETRYUTIL_H
