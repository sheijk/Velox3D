#ifndef V3D_VGEOMETRYDATA_H
#define V3D_VGEOMETRYDATA_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/VMeshDescription.h>
#include <v3d/Graphics/VBuffer.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // beware of evil indenting!

/**
 * A simple mesh structure
 */
template<typename VertexStructure>
class VGeometryData
{
public:
	typedef v3d::graphics::VMeshDescription::GeometryType GeometryType;

	VGeometryData(
		GeometryType in_GeometryType,
		vuint in_nVertexCount, 
		int in_nIndexCount = 0
		);

	GeometryType type;
	v3d::graphics::VBuffer<VertexStructure> vertices;
	v3d::graphics::VBuffer<vuint> indices;
};

//-----------------------------------------------------------------------------
#include "VGeometryData.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGEOMETRYDATA_H
