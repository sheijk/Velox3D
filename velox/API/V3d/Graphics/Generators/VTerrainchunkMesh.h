#ifndef V3D_VTERRAIN_CHUNK_2004_04_10_H
#define V3D_VTERRAIN_CHUNK_2004_04_10_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Image.h>
#include <V3d/Graphics/Misc/MiscUtils.h>
#include <V3d/Graphics/Geometry.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * A chunk for a terrain engine
 *
 * @author sheijk
 */
class VTerrainChunkMesh : public VDynamicGeometryData<VTexturedVertex>
{
	typedef VTexturedVertex VertexStructure;

	vuint m_nWidth;
	vuint m_nHeight;

	v3d::image::IVImageFactory::ImagePtr m_pHeightmap;
	v3d::image::IVImageFactory::ImagePtr m_pTexture;

	std::string m_strTextureFileName;

	v3d::image::IVImageFactory& ImageService();

	vuint GetVertexCount();
	vuint GetIndexCount();

	vuint GetVertexNum(vuint x, vuint y);
	
	vfloat32 GetHeight(vuint x, vuint y);

	void GenerateCoordinates();
	void GenerateTexCoords();
	void GenerateIndices();

public:
	VTerrainChunkMesh(
		VStringParam in_strHeighmapFile,
		VStringParam in_strTexture
		);

	VMaterialDescription GetMaterialDescription(IVDevice& device);

	vuint GetWidth() const;
	vuint GetHeight() const;
	VertexStructure& GetVertex(vuint x, vuint y);
	const VertexStructure& GetVertex(vuint x, vuint y) const;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAIN_CHUNK_2004_04_10_H
