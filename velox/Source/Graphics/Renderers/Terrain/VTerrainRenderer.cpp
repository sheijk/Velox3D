#include <V3dLib/Graphics/Renderers/Terrain/VTerrainRenderer.h>
//-----------------------------------------------------------------------------
#include <algorithm>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

VTerrainRenderer::Heightmap& 
	VTerrainRenderer::GetHeightmap(vuint chunkx, vuint chunky)
{
	return m_Chunks(chunkx, chunky).pChunk->GetLodHeights(0);
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
		m_Chunks(x,y).pChunk.Assign(new VTerrainLodChunk(LodCount, in_Device));
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
	}
	if( bottomBorder )
	{
		GetHeightmap(patchX, patchY+1)(offsetX, 0) = in_fHeight;
	}

	if ( rightBorder && bottomBorder )
	{
		GetHeightmap(patchX+1, patchY+1)(0, 0) = in_fHeight;
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
		m_Chunks(x,y).pChunk->InvalidateLodData();
	}
}

void VTerrainRenderer::CreateMeshes()
{
	// for each chunk
	for(vuint x = 0; x < m_Chunks.GetWidth(); ++x)
	for(vuint y = 0; y < m_Chunks.GetHeight(); ++y)
	{
		//// adjust height
		//for(vuint oy = 0; oy < GetHeightmap(x,y).GetHeight(); ++oy)
		//for(vuint ox = 0; ox < GetHeightmap(x,y).GetWidth(); ++ox)
		//{
		//	GetHeightmap(x,y)(ox, oy) = 0.1 * 
		//		(x+GetHeightmap(x,y).GetWidth()*y);
		//}
		//GetHeightmap(x,y)(0,0) = 0.0f;

		// create mesh
		vuint lod = (x == 1 && y == 1)? 1 : 0;
		m_Chunks(x,y).lod = lod;
		IVDevice::MeshHandle hMesh = m_Chunks(x,y).pChunk->CreateMesh(lod);

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
	V3D_ASSERT(hf.GetWidth() >= GetWidth());
	V3D_ASSERT(hf.GetHeight() >= GetHeight());

	for(vuint y = 0; y < GetHeight(); ++y)
	for(vuint x = 0; x < GetWidth(); ++x)
	{
		Set(x, y, hf.Get(x,y));
	}
}

void VTerrainRenderer::Update(const IVCamera& in_Camera)
{
	typedef VVector<vfloat32, 3> Position;

	// for each chunk
	for(vuint x = 0; x < m_Chunks.GetWidth(); ++x)
	for(vuint y = 0; y < m_Chunks.GetHeight(); ++y)
	{
		// calculate distance from camera
		Position chunkPos;
		chunkPos.Set(0, x * GetChunkUnitWidth());
		chunkPos.Set(1, y * GetChunkUnitHeight());
		chunkPos.Set(2, 0.0f);
		
		// calculate appropriate lod
		chunkPos -= in_Camera.GetPosition();
		const vfloat32 distance = Length(chunkPos);
		const vuint detail = CalcDetail(distance);

		// apply it

		// remove old model
		m_DrawList.Remove(VModel(
			m_Chunks(x,y).pChunk->CreateMesh(m_Chunks(x,y).lod), 
			math::IdentityPtr()));

		// add new model
		m_Chunks(x,y).lod = detail;
		IVDevice::MeshHandle hMesh = m_Chunks(x,y).pChunk->CreateMesh(detail);
		vfloat32 xpos = 2 * x * GetChunkUnitWidth();
		vfloat32 ypos = 2 * y * GetChunkUnitHeight();

		VModel::TransformMatrixPtr pTransform(new VModel::TransformMatrix());
		Identity(*pTransform);
		math::SetTranslate(*pTransform, xpos, ypos, 0.0f);

		m_DrawList.Add(VModel(hMesh, pTransform));
	}
}

vfloat32 VTerrainRenderer::GetChunkUnitWidth() const
{
	return m_nChunkSize;
}

vfloat32 VTerrainRenderer::GetChunkUnitHeight() const
{
	return m_nChunkSize;
}

vuint VTerrainRenderer::CalcDetail(vfloat32 in_fDistance) const
{
	V3D_ASSERT(in_fDistance >= 0.0f);

	// smallest detail >= maxdist distance, greatest detail at <= 10 distance,
	// linear interpolation in between

	vuint lod = 0;
	const vfloat32 maxdist = 30.0f;

	if( in_fDistance > 10.0f )
	{
		in_fDistance -= 10.0f;
	
		lod = in_fDistance / maxdist * GetLodSteps();

		lod = std::min(lod, GetLodSteps()-1);
	}

	return lod;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
