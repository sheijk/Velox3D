#ifndef V3D_VGEOMETRYDATA_H
#define V3D_VGEOMETRYDATA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/VMeshDescription.h>
#include <v3d/Graphics/VBuffer.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // beware of evil indenting!

/**
 * A simple mesh structure
 *
 * //TODO: make type, vertices and indices private
 */
template<typename VertexStructure>
class VGeometryData
{
public:
	typedef v3d::graphics::VMeshDescription::GeometryType GeometryType;
	typedef v3d::graphics::VBuffer<VertexStructure> VertexBuffer;
	typedef v3d::graphics::VBuffer<vuint> IndexBuffer;

	VGeometryData(
		GeometryType in_GeometryType,
		vuint in_nVertexCount,
		vuint in_nIndexCount = 0
		);

	GeometryType GetGeometryType() const
	{
		return type;
	}

	VertexBuffer& GetVertexBuffer()
	{
		return vertices;
	}

	const VertexBuffer& GetVertexBuffer() const
	{
		return vertices;
	}

	IndexBuffer& GetIndexBuffer()
	{
		return indices;
	}

	const IndexBuffer& GetIndexBuffer() const
	{
		return indices;
	}

private:
	const GeometryType type;
	v3d::graphics::VBuffer<VertexStructure> vertices;
	v3d::graphics::VBuffer<vuint> indices;
};

//-----------------------------------------------------------------------------
#include "VGeometryData.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGEOMETRYDATA_H
