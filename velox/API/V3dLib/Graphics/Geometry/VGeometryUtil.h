#ifndef V3D_VGEOMETRYUTIL_H
#define V3D_VGEOMETRYUTIL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Graphics/Geometry/VVector3f.h>
#include <V3dLib/Graphics/Geometry/VColor4f.h>
#include <V3dLib/Graphics/Geometry/VVertexDataLayout.h>

#include <v3d/Graphics.h>
#include <v3d/Image/VImage.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

inline VMeshDescription BuildMeshDescription(
	IVBuffer<vbyte>* in_Buffer,
	VVertexDataLayout in_Layout,
	vuint in_cnVertexCount
	);

/**
 * Takes an array of vertices and builds a mesh description of it.
 * Loads the data of the mesh into the device
 *
 * @author sheijk
 */
template<typename VertexStructure>
v3d::graphics::VMeshDescription BuildMeshDescription(
	v3d::graphics::IVDevice& in_Device,
	VertexStructure pVertices[],
	const vuint in_cnVertexCount
	);

/**
 * Takes some vertices and indices and creates a mesh from them
 * Uses non indexed mesh if indeces are NULL
 *
 * @author sheijk
 */
template<typename VertexStructure>
v3d::graphics::VMeshDescription BuildMeshDescription(
	v3d::graphics::IVDevice& in_Device,
	VertexStructure in_pVertices[],
	vuint in_nVertexCount,
	vuint in_pIndices[],
	vuint in_nIndexCount
	);

/**
 * Builds a mesh from a geometry provider. Creates the needed buffers
 *
 * @author sheijk
 */
template<typename GeometryProvider>
v3d::graphics::IVDevice::MeshHandle BuildMesh(
	v3d::graphics::IVDevice& device,
	GeometryProvider& provider, 
	v3d::graphics::VMaterialDescription& mat);

template<typename GeometryProvider>
v3d::graphics::IVDevice::MeshHandle BuildMesh(
	v3d::graphics::IVDevice& device,
	GeometryProvider& provider, 
	v3d::graphics::VEffectDescription& effect);

/**
 * Creates a texture reference from a loaded image. Creates a texture
 * buffer inside the mesh
 *
 * @author sheijk
 */
v3d::graphics::VMaterialDescription::TextureRef* CreateTextureRef(
	v3d::graphics::IVDevice& device, 
	v3d::image::VImage& image);

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

//-----------------------------------------------------------------------------
#include "VGeometryUtil.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGEOMETRYUTIL_H
