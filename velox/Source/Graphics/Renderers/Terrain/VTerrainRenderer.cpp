#include <V3dLib/Graphics/Renderers/Terrain/VTerrainRenderer.h>
//-----------------------------------------------------------------------------
#include <algorithm>
#include <V3d/Core/VIOStream.h>
#include <V3dLib/Graphics/Misc/MiscUtils.h>
#include <V3d/Vfs.h>
#include <cmath>

extern vuint highDetail;
extern vuint lowDetail;

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

VTerrainRenderer::Heightmap& 
	VTerrainRenderer::GetHeightmap(vuint chunkx, vuint chunky)
{
	return m_Chunks(chunkx, chunky).pChunk->GetLodHeights(0);
}

VTerrainRenderer::VTerrainRenderer(
	vuint in_nPatchCount, 
	IVDevice& in_Device,
	VStringParam in_strTextureFile
	)
	:
	m_nPatchCount(in_nPatchCount),
	m_fChunkModelSize(10.0f),
	m_DrawList(in_Device),
	m_bShowWireFrame(false)
{
	// load texture
	m_TextureMat = BuildTextureMaterial(&in_Device, in_strTextureFile);
	//m_TextureMat.frontPolyMode = VMaterialDescription::Line;
	//m_TextureMat.backPolyMode = VMaterialDescription::Line;

	//m_Chunks.Resize(in_nPatchCount, in_nPatchCount, ChunkMap::Uninitialized);
	m_Chunks.ResizeUninit(in_nPatchCount, in_nPatchCount);

	vfloat32 left = 1.0f;
	vfloat32 top = 0;
	vfloat32 right = 0;
	vfloat32 bottom = 0;
	const vfloat32 dx = 1.0f / m_Chunks.GetWidth();
	const vfloat32 dy = -1.0f / m_Chunks.GetHeight();

	// create all terrain chunks
	for(vuint x = 0; x < m_Chunks.GetWidth(); ++x)
	{
		left = right;
		right = left + dx;

		for(vuint y = 0; y < m_Chunks.GetHeight(); ++y)
		{
			top = bottom;
			bottom = top + dy;

			m_Chunks(x,y).pChunk.Assign(new VTerrainLodChunk(
				LodCount, 
				m_fChunkModelSize, 
				VRectangle<vfloat32>(left, top, right, bottom),
				in_Device 
				//m_TextureMat
				));
		}
	}

	VLodHeightmap::Heightmap& lod0(GetHeightmap(0,0));
	m_nChunkSize = lod0.GetWidth();
	V3D_ASSERT(lod0.GetWidth() == lod0.GetHeight());
}

VTerrainRenderer::TerrainRendererPtr VTerrainRenderer::CreateFromRawFile(
	VStringParam in_strFileName, 
	IVDevice& in_Device,
	VStringParam in_strTextureFile
	)
{
	std::string rawfile(in_strFileName);
	std::string withoutExt(rawfile, 0, rawfile.find_last_of('.'));
	withoutExt += ".jpg";

	if( 0 == in_strTextureFile ) 
	{
		in_strTextureFile = withoutExt.c_str();
	}

	// open file and get size
	VServicePtr<vfs::IVFileSystem> pFS;

	vfs::IVFileSystem::FileStreamPtr pStream = 
		pFS->OpenFile(in_strFileName, vfs::VReadAccess);

	const vuint nSize = pStream->GetSize();
	const vfloat32 fSizeLen = std::sqrt(vfloat32(nSize));
	const vuint nSizeLen = fSizeLen;

	if( nSizeLen * nSizeLen != nSize )
	{
		V3D_THROW(VTerrainGenException, 
			VString("raw file must have n^2 filesize") +
			" filename=" + in_strFileName +
			" size=" + nSize
			);
	}

	// load data
	return CreateFromStream(*pStream, nSizeLen, in_Device, in_strTextureFile);
}

VTerrainRenderer::TerrainRendererPtr VTerrainRenderer::CreateFromStream(
	vfs::IVStream& in_Stream,
	vuint in_nSize,
	IVDevice& in_Device,
	VStringParam in_strTextureFile)
{
	// calc patch nr. for terrain
	vuint nPatchCount = 1;
	vuint nPatchSize = SizeWithNChunks(nPatchCount);

	while( nPatchSize < in_nSize )
	{
		++nPatchCount;
		nPatchSize = SizeWithNChunks(nPatchCount);
	}

	// create terrain
	TerrainRendererPtr pTerrain(
		new VTerrainRenderer(nPatchCount, in_Device, in_strTextureFile));

	vuint nTerrainSize = pTerrain->GetWidth();
	V3D_ASSERT(nPatchSize <= nTerrainSize);

	// set heightdata
	vbyte heightValue = 0;
	vfloat32 height = 0.0f;

	for(vuint y = 0; y < pTerrain->GetWidth(); ++y)
	for(vuint x = 0; x < pTerrain->GetHeight(); ++x)
	{
		in_Stream >> heightValue;

		//TODO: scale to [0,1] or [-1,1] ?
		height = vfloat32(heightValue) / 128.0f * 3 - 1.0f;
        
		pTerrain->Set(x, y, height);
	}

	return pTerrain;
}

vuint Power(vuint base, vuint exp)
{
	vuint res = 1;

	for( ; exp > 0; --exp)
	{
		res *= base;
	}

	return res;
}

vuint GetChunkSize(vuint steps)
{
	return (2 << (steps-2)) + 1;
}

vuint VTerrainRenderer::SizeWithNChunks(vuint in_nChunkCount)
{
	return (GetChunkSize(LodCount)-1) * in_nChunkCount + 1;
}

VTerrainRenderer::~VTerrainRenderer()
{
	//TODO: free texture buffer
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
		m_Chunks(x,y).lod = 0;
		m_Chunks(x,y).pChunk->SetLod(0);//LodCount-1);
		m_Chunks(x,y).pChunk->UpdateCurrentMesh(m_TextureMat);
		IVDevice::MeshHandle hMesh = m_Chunks(x,y).pChunk->GetCurrentMesh();

		// calculate position
		vfloat32 xpos = x * GetChunkUnitWidth() * 2;
		vfloat32 ypos = y * GetChunkUnitHeight() * 2;

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

vuint VTerrainRenderer::LodForChunk(vuint x, vuint y, const IVCamera& in_Camera)
{
	typedef VVector<vfloat32, 3> Position;

	// calculate distance from camera
	Position chunkPos;
	chunkPos.Set(0, 2 * x * GetChunkUnitWidth());
	chunkPos.Set(1, 2 * y * GetChunkUnitHeight());
	chunkPos.Set(2, 0.0f);
	
	// calculate appropriate lod
	chunkPos -= in_Camera.GetPosition();
	const vfloat32 distance = Length(chunkPos);
	vuint detail = CalcDetail(distance);
	//if( x == 2 && y == 1 )
	//	detail = highDetail;
	//else
	//	detail = lowDetail;

	return detail;
}

void VTerrainRenderer::MarkLodSwitch(vuint x, vuint y, vuint lod)
{
	LodChangeItem item(x, y, lod);

	// check if pos is already contained
	for(vuint p = 0; p < m_LodChanges.size(); ++p)
	if( m_LodChanges[p].m_bFree == false )
	{
		if( m_LodChanges[p].m_nX == x &&
			m_LodChanges[p].m_nY == y
			)
		{
			//m_LodChanges[p].m_nLod = lod;
			return;
		}
	}

	vuint pos = 0;

	// find free entry
	for( ; pos < m_LodChanges.size(); ++pos)
	{
        if( m_LodChanges[pos].m_bFree == true )
		{
			break;
		}
	}

	if( pos >= m_LodChanges.size() )
	{
		// increase size
		m_LodChanges.resize(pos * 2 + 1);

		vout << "increased updated chunks per frame list to " << pos * 2 + 1
			<< vendl;
	}

	// store
	m_LodChanges[pos] = item;

	V3D_ASSERT(m_LodChanges[pos].m_bFree == false);
}

void VTerrainRenderer::UpdateChunkMesh(vuint x, vuint y)
{
	// remove old model
	m_DrawList.Remove(VModel(
		m_Chunks(x,y).pChunk->GetCurrentMesh(),
		math::IdentityPtr()));

	if( m_bShowWireFrame )
	{
		m_DrawList.Remove(VModel(
			m_Chunks(x,y).pChunk->GetWireFrameMesh(),
			math::IdentityPtr()));
	}

	// add new model
	m_Chunks(x,y).pChunk->UpdateCurrentMesh(m_TextureMat);

	IVDevice::MeshHandle hMesh = m_Chunks(x,y).pChunk->GetCurrentMesh();

	vfloat32 xpos = 2 * x * GetChunkUnitWidth();
	vfloat32 ypos = 2 * y * GetChunkUnitHeight();

	VModel::TransformMatrixPtr pTransform(new VModel::TransformMatrix());
	Identity(*pTransform);
	math::SetTranslate(*pTransform, xpos, ypos, 0.0f);

	m_DrawList.Add(VModel(hMesh, pTransform));

	if( m_bShowWireFrame )
	{
		IVDevice::MeshHandle hWireframeMesh = 
			m_Chunks(x,y).pChunk->GetWireFrameMesh();
		m_DrawList.Add(VModel(hWireframeMesh, pTransform));
	}
}

void VTerrainRenderer::Update(const IVCamera& in_Camera)
{
	// for each chunk:
	for(vuint x = 0; x < m_Chunks.GetWidth(); ++x)
	for(vuint y = 0; y < m_Chunks.GetHeight(); ++y)
	{
		// calculate lod
		vuint lod = LodForChunk(x, y, in_Camera);

		// if lod changed
		if( m_Chunks(x,y).pChunk->GetLod() != lod )
		{
			// add chunk to change list
			MarkLodSwitch(x, y, lod);
	
			// store new lod
			m_Chunks(x,y).pChunk->SetLod(lod);

			// for all 4 neighbours: tell new lod + add to change list
			if( x+1 < m_Chunks.GetWidth() )
			{
				m_Chunks(x+1, y).pChunk->SetNeighbourLod(VTerrainLodChunk::Left, lod);
				MarkLodSwitch(x+1, y, m_Chunks(x+1,y).pChunk->GetLod());
			}
			if( x > 0 )
			{
				m_Chunks(x-1, y).pChunk->SetNeighbourLod(VTerrainLodChunk::Right, lod);
				MarkLodSwitch(x-1, y, m_Chunks(x-1,y).pChunk->GetLod());
			}
			if( y+1 < m_Chunks.GetHeight() )
			{
				m_Chunks(x, y+1).pChunk->SetNeighbourLod(VTerrainLodChunk::Top, lod);
				MarkLodSwitch(x, y+1, m_Chunks(x,y+1).pChunk->GetLod());
			}
			if( y > 0 )
			{
				m_Chunks(x, y-1).pChunk->SetNeighbourLod(VTerrainLodChunk::Bottom, lod);
				MarkLodSwitch(x, y-1, m_Chunks(x,y-1).pChunk->GetLod());
			}
		}
	}

	// for each item in change list
	vuint updatedChunks = 0;
	const vuint chunksPerFrameMax = 2;

	for(
		vuint pos = 0; 
		pos < m_LodChanges.size() && updatedChunks < chunksPerFrameMax; 
		++pos)
	if( m_LodChanges[pos].m_bFree == false )
	{
		VTerrainLodChunk& chunk(*m_Chunks(
			m_LodChanges[pos].m_nX, m_LodChanges[pos].m_nY).pChunk);
		
		// change mesh
		UpdateChunkMesh(m_LodChanges[pos].m_nX, m_LodChanges[pos].m_nY);

		// clear item
		m_LodChanges[pos].m_bFree = true;

		++updatedChunks;
	}
}

VTerrainLodChunk& VTerrainRenderer::GetChunk(vuint x, vuint y)
{
	return *m_Chunks(x,y).pChunk;
}

vfloat32 VTerrainRenderer::GetChunkUnitWidth() const
{
	return m_fChunkModelSize;
}

vfloat32 VTerrainRenderer::GetChunkUnitHeight() const
{
	return m_fChunkModelSize;
}

vuint VTerrainRenderer::CalcDetail(vfloat32 in_fDistance) const
{
	V3D_ASSERT(in_fDistance >= 0.0f);

	// smallest detail >= maxdist distance, greatest detail at <= 10 distance,
	// linear interpolation in between

	vuint lod = 0;
	const vfloat32 maxdist = 400.0f;
	const vfloat32 mindist = 10.0f;

	if( in_fDistance > mindist )
	{
		in_fDistance -= mindist;
	
		lod = in_fDistance / maxdist * GetLodSteps();

		lod = std::min(lod, GetLodSteps()-1);
	}

	return lod;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
