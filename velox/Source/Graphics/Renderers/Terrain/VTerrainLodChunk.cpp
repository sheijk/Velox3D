#include <V3dLib/Graphics/Renderers/Terrain/VTerrainLodChunk.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

VTerrainLodChunk::VTerrainLodChunk(
		vuint in_nLodCount,
		vfloat32 in_fMeshSize,
		VRectangle<vfloat32> in_TexCoords,
		IVDevice& in_Device
		//const VMaterialDescription& in_Material
		)
	: 
	m_nLodCount(in_nLodCount),
	m_fMeshSize(in_fMeshSize),
	m_LodHeightmap(in_nLodCount),
	m_LodInfos(in_nLodCount),
	m_Device(in_Device),
	m_hCurrentMesh(0),
	m_hIndexBuffer(0),
	m_hVertexBuffer(0),
	//m_Material(in_Material),
	m_TexCoords(in_TexCoords)
{
	SetLod(0);
}

VTerrainLodChunk::~VTerrainLodChunk()
{
	DeleteDeviceData();
}

vbool VTerrainLodChunk::IsMeshLoaded(vuint in_nLod) const
{
	V3D_ASSERT(in_nLod < m_nLodCount);

	return m_LodInfos[in_nLod].hMesh != 0;
}

//VTerrainLodChunk::MeshHandle VTerrainLodChunk::CreateMesh(vuint in_nLod)
//{
//	in_nLod = std::min(in_nLod, m_nLodCount-1);
//
//	MeshHandle hMesh = m_LodInfos[in_nLod].hMesh;
//
//	// create the mesh if it does not exist, yet
//	if( hMesh == 0 )
//	{
//		// create a heightmap model from the height values
//		VHeightmapMesh<MyVertexType> model(
//			m_LodHeightmap.GetLod(in_nLod).GetWidth(), 
//			m_LodHeightmap.GetLod(in_nLod).GetHeight()
//			);
//		model.GenerateIndices();
//
//		// create a mesh from the model	and store it
//		VMaterialDescription mat;
//		//mat.frontPolyMode = VMaterialDescription::Line;
//		//mat.backPolyMode = VMaterialDescription::Line;
//
//		ApplyHeightValues(model, m_LodHeightmap.GetLod(in_nLod));
//		ForEachVertex(
//			model.GetVertexBuffer(), 
//			ScaleVertex<VColoredVertex>(m_fMeshSize, m_fMeshSize, 5.0f));
//
//		hMesh = BuildMesh(m_Device, model, mat);
//
//		m_LodInfos[in_nLod].hMesh = hMesh;
//	}
//
//	V3D_ASSERT(hMesh != 0);
//
//	return hMesh;
//}

void VTerrainLodChunk::SetLod(vuint in_nLod)
{
	// store current lod
    m_nCurrentLod = in_nLod;

	// copy heightmap
	m_CurrentHeightmap = m_LodHeightmap.GetLod(m_nCurrentLod);
}

vuint VTerrainLodChunk::GetLod() const
{
	return m_nCurrentLod;
}

VTerrainLodChunk::MeshHandle VTerrainLodChunk::GetCurrentMesh() const
{
	return m_hCurrentMesh;
}

VLodHeightmap::Heightmap& VTerrainLodChunk::GetCurrentHeightmap()
{
	return m_CurrentHeightmap;
}

const VLodHeightmap::Heightmap& VTerrainLodChunk::GetCurrentHeightmap() const
{
	return m_CurrentHeightmap;
}

void VTerrainLodChunk::SetNeighbourLod(Direction in_Dir, vuint in_nLod)
{
	V3D_ASSERT(vuint(in_Dir) < 4);

	m_NeighbourLod[vint(in_Dir)] = in_nLod;
}

void VTerrainLodChunk::DeleteDeviceData()
{
	m_Device.DeleteMesh(m_hCurrentMesh);
	m_Device.DeleteBuffer(m_hVertexBuffer);
	m_Device.DeleteBuffer(m_hIndexBuffer);
	m_hCurrentMesh = 0;
	m_hVertexBuffer = 0;
	m_hIndexBuffer = 0;
}

void VTerrainLodChunk::AdjustBorderVertical(
	VHeightmapMesh<MyVertexType>& model,
	vuint borderLod,
	vuint x
	)
{
	vuint factor = 1;
	for(vint lodDiff = borderLod - GetLod();
		lodDiff > 0; --lodDiff)
	{
		factor *= 2;
	}
    
	const vuint leftH = GetCurrentHeightmap().GetHeight() / factor;
	for(vuint y = 0; y < leftH; ++y)
	{
		for(vuint dy = 0; dy < factor; ++dy)
		{
			model.GetVertex(x, y*factor+dy) = 
				model.GetVertex(x, y*factor);
		}
	}
}

void VTerrainLodChunk::AdjustBorderHorizontal(
	VHeightmapMesh<MyVertexType>& model,
	vuint borderLod,
	vuint y
	)
{
	vuint factor = 1;
	for(vint lodDiff = borderLod - GetLod();
		lodDiff > 0; --lodDiff)
	{
		factor *= 2;
	}
    
	const vuint borderW = GetCurrentHeightmap().GetWidth() / factor;
	for(vuint x = 0; x < borderW; ++x)
	{
		for(vuint dx = 0; dx < factor; ++dx)
		{
			model.GetVertex(x*factor+dx, y) = 
				model.GetVertex(x*factor, y);
		}
	}
}

template<typename VertexStructure>
void GenerateInterpolatedTexCoords(
	v3d::graphics::VBuffer<VertexStructure>& buffer,
	vuint width,
	vuint height,
	VRectangle<vfloat32> in_Range
	)
{
	V3D_ASSERT(width * height == buffer.GetSize());

	const vfloat32 deltax = (in_Range.right-in_Range.left) / vfloat32(width-1);
	const vfloat32 deltay = (in_Range.bottom-in_Range.top) / vfloat32(height-1);

	for(vuint x = 0; x < width; ++x)
	for(vuint y = 0; y < height; ++y)
	{
		buffer[x + y*width].texCoords.u = x * deltax + in_Range.left;
		buffer[x + y*width].texCoords.v = y * deltay + in_Range.top;
	}    
}

void VTerrainLodChunk::UpdateCurrentMesh(const VMaterialDescription& in_Mat)
{
	// delete old mesh
	DeleteDeviceData();

	// create new mesh
	// create a heightmap model from the height values
	VHeightmapMesh<MyVertexType> model(
		GetCurrentHeightmap().GetWidth(), 
		GetCurrentHeightmap().GetHeight()
		);
	model.GenerateIndices();

	// create a mesh from the model	and store it
	const VMaterialDescription& mat = in_Mat;

	ApplyHeightValues(model, GetCurrentHeightmap());
	GenerateInterpolatedTexCoords(
		model.GetVertexBuffer(),
		model.GetWidth(),
		model.GetHeight(),
		m_TexCoords
		);

	ForEachVertex(
		model.GetVertexBuffer(), 
		ScaleVertex<MyVertexType>(m_fMeshSize, m_fMeshSize, 50.0f));

	// move border vertices if the neighbour mesh has a lower detail
	if( m_NeighbourLod[vint(Left)] > GetLod() )
	{
		AdjustBorderVertical(model, m_NeighbourLod[vint(Left)], 0);
	}
	if( m_NeighbourLod[vint(Right)] > GetLod() )
	{
		AdjustBorderVertical(model, m_NeighbourLod[vint(Right)], 
			model.GetWidth()-1);
	}
	if( m_NeighbourLod[vint(Top)] > GetLod() )
	{
		AdjustBorderHorizontal(model, m_NeighbourLod[vint(Top)], 0);
	}
	if( m_NeighbourLod[vint(Bottom)] > GetLod() )
	{
		AdjustBorderHorizontal(model, m_NeighbourLod[vint(Bottom)],
			model.GetHeight()-1);
	}

	VMeshDescription meshd = BuildMeshDescription(
		m_Device,
		model.GetVertexBuffer().GetDataAddress(),
		model.GetVertexBuffer().GetSize(),
		model.GetIndexBuffer().GetDataAddress(),
		model.GetIndexBuffer().GetSize());
	meshd.geometryType = model.GetGeometryType();

	m_hVertexBuffer = meshd.triangleVertices.hBuffer;
	m_hIndexBuffer = meshd.triangleIndices.hBuffer;

	m_hCurrentMesh = m_Device.CreateMesh(meshd, mat);
}

VLodHeightmap::Heightmap& VTerrainLodChunk::GetLodHeights(vuint in_nLod)
{
	return m_LodHeightmap.GetLod(in_nLod);
}

const VLodHeightmap::Heightmap& VTerrainLodChunk::GetLodHeights(vuint in_nLod) const
{
	return m_LodHeightmap.GetLod(in_nLod);
}

vuint VTerrainLodChunk::LodCount() const
{
	return m_nLodCount;
}

void VTerrainLodChunk::InvalidateLodData()
{
	m_LodHeightmap.InvalidateLodData();

	//TODO: update meshes
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
