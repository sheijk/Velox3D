#ifndef V3D_VCUBEMESHDESC_H
#define V3D_VCUBEMESHDESC_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/Descriptions/IVMeshDescription.h>

#include <vector>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A simple cube mesh
 *
 * @author sheijk
 */
class VCubeMeshDescr : public IVMeshDescription
{
	typedef std::vector<VTriangle> TriangleContainer;
	
	TriangleContainer m_Triangles;

public:
	VCubeMeshDescr(float in_fSize);
	virtual ~VCubeMeshDescr();

	virtual TriangleIterator TriangleBegin() const;
	virtual TriangleIterator TriangleEnd() const;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCUBEMESHDESC_H
