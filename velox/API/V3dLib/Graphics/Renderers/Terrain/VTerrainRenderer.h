#ifndef V3D_VTERRAINRENDERER_2004_05_10_H_H
#define V3D_VTERRAINRENDERER_2004_05_10_H_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Graphics/Misc/VSimpleDrawList.h>
#include <V3dLib/Graphics/Renderers/Terrain/VTerrainLodChunk.h>
#include <V3dLib/Math.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

class VTerrainRenderer
{
	typedef VLodHeightmap::Heightmap Heightmap;
	typedef VPointer<VTerrainLodChunk>::AutoPtr TerrainLodChunkPtr;

	struct ChunkInfo
	{
		TerrainLodChunkPtr pChunk;
		vuint lod;
	};

	typedef VArray2d<ChunkInfo, vuint> ChunkMap;

	enum Constants
	{
		LodCount = 3
	};

	Heightmap& GetHeightmap(vuint chunkx, vuint chunky);
	void CalculatePatchAndOffset(
		vuint x, vuint y,
		vuint& patchX, vuint& patchY, vuint& offsetX, vuint& offsetY
		);

	vfloat32 GetChunkUnitWidth() const;
	vfloat32 GetChunkUnitHeight() const;

	vuint CalcDetail(vfloat32 in_fDistance) const;

	const vuint m_nPatchCount;
	/** the terrain chunks */
	ChunkMap m_Chunks;
	vuint m_nChunkSize;
	VSimpleDrawList m_DrawList;

public:
	VTerrainRenderer(vuint in_nPatchCount, IVDevice& in_Device);

	vuint GetWidth();
	vuint GetHeight();

	void Set(vuint x, vuint y, vfloat32 in_fHeight);
	vfloat32 Get(vuint x, vuint y);

	/**
	 * Recalculates all low level of detail data. Needs to be called after
	 * a change to the heightmap data has been made
	 */
	void UpdateLods();

	/**
	 * Changes lods of chunks depending on distance to camera 
	 * [todo]and culls away invisible chunks [/todo]
	 */
	void Update(const IVCamera& in_Camera);

	void CreateMeshes();

	void Render();

	vuint GetLodSteps() const;

	void ApplyHeightData(const VArray2d<vfloat32, vuint>& hf);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAINRENDERER_2004_05_10_H_H
