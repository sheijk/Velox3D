#include <V3dLib/Graphics/Renderers/Terrain/VTerrainRenderer.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

VTerrainRenderer::Heightmap& 
	VTerrainRenderer::GetHeightmap(vuint chunkx, vuint chunky)
{
	return m_Chunks(chunkx, chunky)->GetLodHeights(0);
}

VTerrainRenderer::VTerrainRenderer(vuint in_nPatchCount, IVDevice& in_Device)
	:
	m_nPatchCount(in_nPatchCount),
	m_DrawList(in_Device)
{
	//m_Chunks.Resize(in_nPatchCount, in_nPatchCount, ChunkMap::Uninitialized);
	m_Chunks.ResizeUninit(in_nPatchCount, in_nPatchCount);

	// create all terrain chunks
	for(vuint x = 0; x < m_Chunks.GetWidth(); ++x)
	for(vuint y = 0; y < m_Chunks.GetHeight(); ++y)
	{
		m_Chunks(x,y).Assign(new VTerrainLodChunk(LodCount, in_Device));
		//m_Chunks(x,y).Resize(ChunkSize, ChunkSize, HeightField::FillZero);
	}

	VLodHeightmap::Heightmap& lod0(GetHeightmap(0,0));
	m_nChunkSize = lod0.GetWidth();
	V3D_ASSERT(lod0.GetWidth() == lod0.GetHeight());
}

vuint VTerrainRenderer::GetWidth()
{
	return (m_nChunkSize-1) * m_nPatchCount + 1;
}

vuint VTerrainRenderer::GetHeight()
{
	return GetWidth();
}

void VTerrainRenderer::CalculatePatchAndOffset(
	vuint x, vuint y,
	vuint& patchX, vuint& patchY, vuint& offsetX, vuint& offsetY
	)
{
	// calculate patch index
	patchX = x / (m_nChunkSize-1);
	patchY = y / (m_nChunkSize-1);

	// calculate pos inside patch
	offsetX = x % (m_nChunkSize-1);
	offsetY = y % (m_nChunkSize-1);

	if( offsetX == 0 && x > 0 )
	{
		patchX--;
		offsetX = m_nChunkSize-1;
	}

	if( offsetY == 0 && y > 0 )
	{
		patchY--;
		offsetY = m_nChunkSize-1;
	}
}

void VTerrainRenderer::Set(vuint x, vuint y, vfloat32 in_fHeight)
{
	vuint patchX, patchY, offsetX, offsetY;
	CalculatePatchAndOffset(x, y, patchX, patchY, offsetX, offsetY);

	GetHeightmap(patchX, patchY)(offsetX, offsetY) = in_fHeight;
    //m_Chunks(patchX, patchY)(offsetX, offsetY) = in_fHeight;

	// if we have changed an overlapping border, change all [xxx] chunks
	vbool rightBorder = false;
	vbool bottomBorder = false;

    if( offsetX == m_nChunkSize-1 && patchX < m_nPatchCount - 1 )
	{
		rightBorder = true;
	}
	if( offsetY == m_nChunkSize-1 && patchY < m_nPatchCount - 1 )
	{
		bottomBorder = true;
	}

	if( rightBorder )
	{
		GetHeightmap(patchX+1, patchY)(0, offsetY) = in_fHeight;
		//m_Chunks(patchX+1, patchY)(0, offsetY) = in_fHeight;
	}
	if( bottomBorder )
	{
		GetHeightmap(patchX, patchY+1)(offsetX, 0) = in_fHeight;
		//m_Chunks(patchX, patchY+1)(offsetX, 0) = in_fHeight;
	}

	if ( rightBorder && bottomBorder )
	{
		GetHeightmap(patchX+1, patchY+1)(0, 0) = in_fHeight;
		//m_Chunks(patchX+1, patchY+1)(0, 0) = in_fHeight;
	}
}

vfloat32 VTerrainRenderer::Get(vuint x, vuint y)
{
	vuint patchX, patchY, offsetX, offsetY;
	CalculatePatchAndOffset(x, y, patchX, patchY, offsetX, offsetY);

	return GetHeightmap(patchX, patchY).Get(offsetX, offsetY);
}

void VTerrainRenderer::UpdateLods()
{
	for(vuint y = 0; y < m_Chunks.GetHeight(); ++y)
	for(vuint x = 0; x < m_Chunks.GetWidth(); ++x)
	{
		m_Chunks(x,y)->InvalidateLodData();
	}
}

void VTerrainRenderer::CreateMeshes()
{
	// for each chunk
	for(vuint x = 0; x < m_Chunks.GetWidth(); ++x)
	for(vuint y = 0; y < m_Chunks.GetHeight(); ++y)
	{
		// adjust height
		//for(vuint oy = 0; oy < GetHeightmap(x,y).GetHeight(); ++oy)
		//for(vuint ox = 0; ox < GetHeightmap(x,y).GetWidth(); ++ox)
		//{
		//	GetHeightmap(x,y)(ox, oy) = 0.1 * 
		//		(x+GetHeightmap(x,y).GetWidth()*y);
		//}
		//GetHeightmap(x,y)(0,0) = 0.0f;

		// create mesh
		vuint lod = (x == 1 && y == 1)? 1 : 0;
		IVDevice::MeshHandle hMesh = m_Chunks(x,y)->CreateMesh(lod);

		// calculate position
		vfloat32 xpos = x * m_nChunkSize * 2;
		vfloat32 ypos = y * m_nChunkSize * 2;

		VModel::TransformMatrixPtr pTransform(new VModel::TransformMatrix());
		Identity(*pTransform);
		math::SetTranslate(*pTransform, xpos, ypos, 0.0f);

		// add to drawlist
		m_DrawList.Add(VModel(hMesh, pTransform));
	}
}

void VTerrainRenderer::Render()
{
	m_DrawList.Render();
}

vuint VTerrainRenderer::GetLodSteps() const
{
	return LodCount;
}

void VTerrainRenderer::ApplyHeightData(const VArray2d<vfloat32, vuint>& hf)
{
	V3D_ASSERT(hf.GetWidth() == GetWidth());
	V3D_ASSERT(hf.GetHeight() == GetHeight());

	for(vuint y = 0; y < GetHeight(); ++y)
	for(vuint x = 0; x < GetWidth(); ++x)
	{
		Set(x, y, hf.Get(x,y));
	}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
