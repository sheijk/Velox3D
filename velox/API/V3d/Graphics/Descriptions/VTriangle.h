#ifndef VTRIANGLE_H
#define VTRIANGLE_H
//-------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Math/VVector.h>

//-------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-------------------------------------------------------------------------

/**
 * A simple Triangle representation class. Simply consists of 3 Vertices
 *
 * @author sheijk
 */
class VTriangle
{
public:
	typedef VVector<float, 3> Vertex;
	typedef Vertex VertexTriple[3];

	inline VTriangle();

	inline VTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
	inline VTriangle(const VertexTriple& vertices);

	inline void SetVertex(vuint in_VertexIndex, const Vertex& in_Value);

	inline Vertex GetVertex(vuint in_nIndex) const;

	/**
	 * Always returns 3
	 */
	inline vuint VertexCount();

private:
	VertexTriple m_Vertices;
};

//-------------------------------------------------------------------------
#include "VTriangle.inl"
//-------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-------------------------------------------------------------------------
#endif // VTRIANGLE_H