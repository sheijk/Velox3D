#ifndef V3D_VGEOMETRYUTIL_H
#define V3D_VGEOMETRYUTIL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Utils/Graphics/VVector3f.h>
#include <v3d/Utils/Graphics/VColor4f.h>
#include <v3d/Utils/Graphics/VVertexDataLayout.h>
#include <v3d/Graphics/VMeshDescription.h>

#include <v3d/Graphics/IVDevice.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
namespace graphics {
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
} // namespace graphics
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGEOMETRYUTIL_H
