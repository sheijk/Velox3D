#ifndef V3D_VTERRAIN_CHUNK_2004_04_10_H
#define V3D_VTERRAIN_CHUNK_2004_04_10_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Image/IVImageFactory.h>
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
class VTerrainChunk : public VDynamicGeometryData<VTexturedVertex>
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
	VertexStructure& GetVertex(vuint x, vuint y);
	
	vfloat32 GetHeight(vuint x, vuint y);

	void GenerateCoordinates();
	void GenerateTexCoords();
	void GenerateIndices();

public:
	VTerrainChunk(
		VStringParam in_strHeighmapFile,
		VStringParam in_strTexture
		);

	VMaterialDescription GetMaterialDescription(IVDevice& device);
};

//-----------------------------------------------------------------------------
#include "VTerrainChunk.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAIN_CHUNK_2004_04_10_H
