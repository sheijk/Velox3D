#ifndef V3D_VHEIGHTMAP_H
#define V3D_VHEIGHTMAP_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Graphics/Geometry/VVector3f.h>
#include <V3dLib/Graphics/Geometry/VTexCoord2f.h>
#include <V3dLib/Graphics/Geometry/VColor4f.h>
#include <v3d/Graphics/VBuffer.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------

/**
 * A heightmap generation geometry provider
 *
 * @author sheijk
 */
template <typename VertexStructure>
class VHeightmap : public VDynamicGeometryData<VertexStructure>
{
	vuint m_nWidth;
	vuint m_nHeight;

	vuint GetVertexCount() const;
	vuint GetIndexCount() const;

	vuint GetVertexNum(vuint x, vuint y) const;
	vfloat32 GetHeight(vuint x, vuint y) const;

public:
	VHeightmap(vuint in_nWidth, vuint in_nHeight);
	VHeightmap();

	void ResetSize(vuint in_nWidth, vuint in_nHeight);

	void GenerateCoordinatesAtZ(vfloat32 in_nZ);
	//void GenerateCoordinates();
	void GenerateTexCoords();
	void GenerateIndices();

	vuint GetWidth() const;
	vuint GetHeight() const;
	VertexStructure& GetVertex(vuint x, vuint y);
	const VertexStructure& GetVertex(vuint x, vuint y) const;
};

//-----------------------------------------------------------------------------
#include "VHeightmap.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VHEIGHTMAP_H
