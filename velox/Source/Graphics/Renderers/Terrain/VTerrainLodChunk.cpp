#include <V3dLib/Graphics/Renderers/Terrain/VTerrainLodChunk.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

VTerrainLodChunk::VTerrainLodChunk(vuint in_nLodCount, IVDevice& in_Device)
	: 
	m_nLodCount(in_nLodCount),
	m_LodHeightmap(in_nLodCount),
	m_LodInfos(in_nLodCount),
	m_Device(in_Device)
{
}

vbool VTerrainLodChunk::IsMeshLoaded(vuint in_nLod) const
{
	V3D_ASSERT(in_nLod < m_nLodCount);

	return m_LodInfos[in_nLod].hMesh != 0;
}

VTerrainLodChunk::MeshHandle VTerrainLodChunk::CreateMesh(vuint in_nLod)
{
	in_nLod = std::min(in_nLod, m_nLodCount-1);

	MeshHandle hMesh = m_LodInfos[in_nLod].hMesh;

	// create the mesh if it does not exist, yet
	if( hMesh == 0 )
	{
		// create a heightmap model from the height values
		VHeightmapMesh<MyVertexType> model(
			m_LodHeightmap.GetLod(in_nLod).GetWidth(), 
			m_LodHeightmap.GetLod(in_nLod).GetHeight()
			);
		model.GenerateIndices();

		// create a mesh from the model	and store it
		VMaterialDescription mat;
		mat.frontPolyMode = VMaterialDescription::Line;
		mat.backPolyMode = VMaterialDescription::Line;

		ApplyHeightValues(model, m_LodHeightmap.GetLod(in_nLod));
		ForEachVertex(
			model.GetVertexBuffer(), 
			ScaleVertex<VColoredVertex>(
				m_LodHeightmap.GetLod(0).GetWidth(),
				m_LodHeightmap.GetLod(0).GetHeight(), 
				5));

		hMesh = BuildMesh(m_Device, model, mat);

		m_LodInfos[in_nLod].hMesh = hMesh;
	}

	V3D_ASSERT(hMesh != 0);

	return hMesh;
}

VLodHeightmap::Heightmap& VTerrainLodChunk::GetLodHeights(vuint in_nLod)
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
