#ifndef V3D_VPOLARSPHERE_H
#define V3D_VPOLARSPHERE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/Geometry/VGeometryData.h>
#include <V3d/Graphics/IVDevice.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti indent task force was here ;)

/**
 * Creates a sphere with poles, like a globe.
 *
 * @author sheijk
 */
template<typename VertexStructure>
class VPolarSphereMesh
{
	const vfloat32 m_cfTop;
	const vfloat32 m_cfBottom;
	const vuint m_nRings;
	const vuint m_nSectors;
	const vuint m_nVertexCount;

	VGeometryData<VertexStructure> geometry;

	vuint GetVertexNum(vuint sector, vuint ring);
	vuint CalculateVertexCount();
	vuint CalculateIndexCount();
	void GenerateIndices();

public:
	typedef v3d::graphics::VBuffer<VertexStructure> VertexBuffer;
	typedef v3d::graphics::VBuffer<vuint> IndexBuffer;

	VPolarSphereMesh(vuint in_nRings, vuint in_nSectors);
	VPolarSphereMesh(
		vuint in_nRings, vuint in_nSectors, 
		vfloat32 in_fBottom, vfloat32 in_fTop
		);

	void GenerateCoordinates();
	void GenerateTexCoords();

	v3d::graphics::VMeshDescription::GeometryType GetGeometryType() const;
	const VertexBuffer& GetVertexBuffer() const;
	VertexBuffer& GetVertexBuffer();
	const IndexBuffer& GetIndexBuffer() const;
	IndexBuffer& GetIndexBuffer();
};

//-----------------------------------------------------------------------------
#include "VPolarSphereMesh.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPOLARSPHERE_H
