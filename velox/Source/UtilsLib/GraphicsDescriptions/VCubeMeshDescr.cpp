#include <v3d/Utils/Graphics/VCubeMeshDescr.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/Wrappers/VSTLIteratorPol.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

namespace
{
	VTriangle::Vertex vert(float x, float y, float z)
	{
		VTriangle::Vertex v;
		v.Set(0, x);
		v.Set(1, y);
		v.Set(2, z);

		return v;
	}
}

/**
 */
VCubeMeshDescr::VCubeMeshDescr(float in_fSize)
{
	//TODO: richtig machen

	// build triangles
	typedef VTriangle::Vertex Vertex;
	VTriangle tris(vert(1, 0, 0), vert(0, 1, 0), vert(-1, 0, 0));
	
	m_Triangles.push_back(tris);

}

/**
 * d'tor
 */
VCubeMeshDescr::~VCubeMeshDescr()
{
}

IVMeshDescription::TriangleIterator VCubeMeshDescr::TriangleBegin() const
{
	typedef VSTLIteratorPol<TriangleContainer::const_iterator, const VTriangle>
		IterPol;

	return TriangleIterator(new IterPol(m_Triangles.begin()));
}

IVMeshDescription::TriangleIterator VCubeMeshDescr::TriangleEnd() const
{
	typedef VSTLIteratorPol<TriangleContainer::const_iterator, const VTriangle>
		IterPol;

	return TriangleIterator(new IterPol(m_Triangles.end()));
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
