#ifndef V3D_VTERRAINRENDERER_2004_05_10_H_H
#define V3D_VTERRAINRENDERER_2004_05_10_H_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Graphics/Misc/VSimpleDrawList.h>
#include <V3dLib/Graphics/Renderers/Terrain/VTerrainLodChunk.h>
#include <V3dLib/Math.h>
#include <vector>
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
		LodCount = 7
	};

	enum VBorder
	{
		AdjustLeftBorder, 
		AdjustRightBorder
	};

	Heightmap& GetHeightmap(vuint chunkx, vuint chunky);
	void CalculatePatchAndOffset(
		vuint x, vuint y,
		vuint& patchX, vuint& patchY, vuint& offsetX, vuint& offsetY
		);

	void VTerrainRenderer::AdjustVerticalBorder(
		VTerrainLodChunk& io_HighChunk,
		const VTerrainLodChunk& in_LowChunk,
		VBorder in_Border,
		vuint x, vuint y
		);

	vfloat32 GetChunkUnitWidth() const;
	vfloat32 GetChunkUnitHeight() const;

	vuint LodForChunk(vuint x, vuint y, const IVCamera& in_Camera);
	vuint CalcDetail(vfloat32 in_fDistance) const;
	VTerrainLodChunk& GetChunk(vuint x, vuint y);
	void MarkLodSwitch(vuint x, vuint y, vuint lod);
	void UpdateChunkMesh(vuint x, vuint y);

	const vuint m_nPatchCount;
	const vfloat32 m_fChunkModelSize;
	/** the terrain chunks */
	ChunkMap m_Chunks;
	vuint m_nChunkSize;
	VSimpleDrawList m_DrawList;

	struct LodChangeItem
	{
		vuint m_nX, m_nY, m_nLod;

		bool m_bFree;

		LodChangeItem() : m_bFree(true)
		{
		}

		LodChangeItem(vuint x, vuint y, vuint lod) :
			m_nX(x), m_nY(y), m_nLod(lod), m_bFree(false)
		{
		}
	};

	typedef std::vector<LodChangeItem> LodChangeList;
	LodChangeList m_LodChanges;

	VMaterialDescription m_TextureMat;

public:
	VTerrainRenderer(vuint in_nPatchCount, IVDevice& in_Device);
	virtual ~VTerrainRenderer();

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
