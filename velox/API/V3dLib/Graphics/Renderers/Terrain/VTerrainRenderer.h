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
namespace vfs { class IVStream; } // forward declaration for v3d::vfs::IVStream //das haet ich jetzt nicht gedacht btw: forward dec. OF ...:)))
namespace graphics {
//-----------------------------------------------------------------------------

V3D_DECLARE_EXCEPTION(VTerrainException, VException);
V3D_DECLARE_EXCEPTION(VTerrainGenException, VTerrainException);

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
	IVDevice& m_Device;
	VSimpleDrawList m_DrawList;
	VSimpleDrawList m_DetailDrawList;

	vbool m_bShowWireFrame;

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
	VMaterialDescription m_DetailTextureMat;

public:
	VTerrainRenderer(
		vuint in_nPatchCount, 
		IVDevice& in_Device,
		VStringParam in_strTextureFile
		);

	virtual ~VTerrainRenderer();

	typedef VPointer<VTerrainRenderer>::SharedPtr TerrainRendererPtr;
	
	static TerrainRendererPtr CreateFromRawFile(
		VStringParam in_strFileName, 
		IVDevice& in_Device,
		VStringParam in_strTextureFile = 0
		);

	static TerrainRendererPtr CreateFromStream(
		vfs::IVStream& in_Stream,
		vuint in_nSize,
		IVDevice& in_Device,
		VStringParam in_strTextureFile
		);

	static vuint SizeWithNChunks(vuint in_nChunkCount);

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
