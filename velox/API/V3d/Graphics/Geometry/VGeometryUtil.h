#ifndef V3D_VGEOMETRYUTIL_H
#define V3D_VGEOMETRYUTIL_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <V3d/Graphics/Geometry/VVertexDataLayout.h>
#include <V3d/Graphics/VMeshDescription.h>
#include <V3d/Resource/IVResourceManager.h>
#include <V3d/Graphics.h>
#include <V3d/Image/VImage.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Builds a vertex format from which a mesh description or a vertex buffer
 * (VVertexBuffer) can be created
 *
 * @author sheijk
 */
template<typename GeometryProvider>
	VVertexFormat BuildFormat(GeometryProvider& in_Geometry);

/**
 * Creates a resources, generates a vertex buffer, index buffer and mesh
 * description from the geometry provider and puts it inside the resource
 * Indices will be put in a resource called in_strResourceName/indices
 *
 * @param in_strResourceName Name of the resource where all data is put
 * @param in_Geometry A geometry provider whose data will be used
 * @return The created resource's id
 * @author sheijk
 */
template<typename GeometryProvider>
resource::VResourceId BuildResource(
	const std::string& in_strResourceName,
	const GeometryProvider& in_Geometry
	);

/**
 * Generates interpolated texture coordinates. Splits the plane into
 * width x height sectors
 *
 * @author sheijk
 */
template<typename VertexStructure>
void GenerateInterpolatedTexCoords(
	v3d::graphics::VBuffer<VertexStructure>& buffer,
	vuint width,
	vuint height
	);

/**
 * Creates a mesh description for the given vertex buffer. The vertex and
 * index buffers must be located in the resource with the given name
 *
 * @author sheijk
 */
VMeshDescription* CreateMeshDescription(
	VMeshDescription::GeometryType in_Primitives,
	const VVertexBuffer& in_VertexBuffer,
	const std::string& in_strVBResource,
	const std::string& in_strIndexResource);

/**
 * Calls CreateMeshDescription(in_Primitives, in_VertexBuffer, 
 * in_strVBResource, in_strVBResource
 */
VMeshDescription* CreateMeshDescription(
	VMeshDescription::GeometryType in_Primitives,
	const VVertexBuffer& in_VertexBuffer,
	const std::string& in_strVBResource);

//-----------------------------------------------------------------------------
#include "VGeometryUtil.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGEOMETRYUTIL_H
