#ifndef V3D_TRIANGLE_04_04_11_H
#define V3D_TRIANGLE_04_04_11_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace graphics{
//-----------------------------------------------------------------------------

/**
* triangle template generator. does not use indices
* @author: ins
*/

template<typename VertexStructure>
class VTriangleMesh : public v3d::graphics::VGeometryData<VertexStructure>
{
public:

	VTriangleMesh() : VGeometryData<VertexStructure>(VMeshDescription::Triangles, 3,0)
	{
		GetVertexBuffer()[0].position.x = -1.0f;
		GetVertexBuffer()[0].position.y = 0.0f;
		GetVertexBuffer()[0].position.z  = -1.0f;

		GetVertexBuffer()[1].position.x = +1.0f;
		GetVertexBuffer()[1].position.y = 0.0f;
		GetVertexBuffer()[1].position.z = -1.0f;

		GetVertexBuffer()[2].position.x = 0.0f;
		GetVertexBuffer()[2].position.y = 1.0f;
		GetVertexBuffer()[2].position.z = -1.0f;

	}

	VTriangleMesh(VVertex3f a, VVertex3f b, VVertex3f c) :VGeometryData<VertexStructure>(VMeshDescription::Triangles, 3, 0)
	{
		// point a
		GetVertexBuffer()[0].position.x = a.x;
		GetVertexBuffer()[0].position.y = a.y;
		GetVertexBuffer()[0].position.z = a.z;

		// point b
		GetVertexBuffer()[1].position.x = b.x;
		GetVertexBuffer()[1].position.y = b.y;
		GetVertexBuffer()[1].position.z = b.z;

		// point c
		GetVertexBuffer()[2].position.x = c.x;
		GetVertexBuffer()[2].position.y = c.y;
		GetVertexBuffer()[2].position.z = c.z;

	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_TRIANGLE_04_04_11_H