#ifndef V3D_VTERRAINLODCHUNK_2004_05_10_H_H
#define V3D_VTERRAINLODCHUNK_2004_05_10_H_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Graphics/Renderers/Terrain/VLodHeightmap.h>
#include <V3dLib/Graphics/Generators/VHeightmapMesh.h>
#include <V3dLib/Graphics/Geometry.h>

#include <algorithm>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Applies the height values of a 2d array to a VHeightmapMesh
 */
template<typename Array2d, typename VertexStructure>
void ApplyHeightValues(
	VHeightmapMesh<VertexStructure>& io_Heightmap, 
	const Array2d& in_Heights
	);

/**
 * Creates meshes from a heightmap and manages the meshes, and geometry data
 */
class VTerrainLodChunk
{
	typedef VColoredVertex MyVertexType;
public:
	typedef IVDevice::MeshHandle MeshHandle;

	VTerrainLodChunk(vuint in_nLodCount, IVDevice& in_Device);
	
	vbool IsMeshLoaded(vuint in_nLod) const;
	MeshHandle CreateMesh(vuint in_nLod);
	VLodHeightmap::Heightmap& GetLodHeights(vuint in_nLod);
	vuint LodCount() const;
	void InvalidateLodData();

private:
	struct LevelOfDetailInfo
	{
		LevelOfDetailInfo() : hMesh(0) {}

		MeshHandle hMesh;
	};

	const vuint m_nLodCount;

	IVDevice& m_Device;
	VLodHeightmap m_LodHeightmap;
	std::vector<LevelOfDetailInfo> m_LodInfos;
};

//-----------------------------------------------------------------------------
template<typename Array2d, typename VertexStructure>
void ApplyHeightValues(
	VHeightmapMesh<VertexStructure>& io_Heightmap, 
	const Array2d& in_Heights
	)
{
	V3D_ASSERT(in_Heights.GetWidth() == io_Heightmap.GetWidth());
	V3D_ASSERT(in_Heights.GetHeight() == io_Heightmap.GetHeight());

	vfloat32 maxH = -1000;
	vfloat32 minH = 1000;

	for(vuint y = 0; y < io_Heightmap.GetHeight(); ++y)
	for(vuint x = 0; x < io_Heightmap.GetWidth(); ++x)
	{
		vfloat32 h = in_Heights.Get(x, y);
		io_Heightmap.GetVertex(x, y).position.z = in_Heights.Get(x,y);

		if( h < minH )
			minH = h;

		if( h > maxH )
			maxH = h;
	}

	minH *= .8f;
	maxH *= .8f;

	for(vuint y = 0; y < io_Heightmap.GetHeight(); ++y)
	for(vuint x = 0; x < io_Heightmap.GetWidth(); ++x)
	{
		vfloat32 h = in_Heights.Get(x, y);

		vfloat32 percentage = (h - minH)/(maxH - minH);

		io_Heightmap.GetVertex(x, y).color.green = percentage/3;
	}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAINLODCHUNK_2004_05_10_H_H
