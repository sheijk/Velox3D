#include <V3dLib/Graphics/Portal/VTerrainCell.h>
//-----------------------------------------------------------------------------
#include <V3dLib/Math.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using v3d::math::IdentityPtr;

void VHeightmapSubMesh::GenerateSubArea(
	VRect<vuint> area,		
	const VTerrainChunk& terrain
	)
{
	SetGeometryType(VMeshDescription::TriangleStrip);

	const vuint width = area.GetWidth();
	const vuint height = area.GetHeight();

	ResizeVertexBuffer(width * height);

	for(vuint x = 0; x < width; ++x)
	for(vuint y = 0; y < height; ++y)
	{
		GetVertexBuffer()[width * y + x].position = 
			terrain.GetVertex(x, y).position;
	}
}

VHeightmapSubMesh::VHeightmapSubMesh()
	:
	VDynamicGeometryData<VSimpleVertex>()
{
}

//-----------------------------------------------------------------------------

VTerrainCell::VTerrainCell(
	VMultipassDrawList& drawList,
	IVCell& cell
	)	:
	terrain("/data/mapheight64.jpg", "/data/maptex.jpg"),
	modelCell(cell)
	//modelCell(CreateCube(drawList.GetDevice()))
{
	//portal.area.lowerLeft	= VVector3f(-1, -1, 0);
	//portal.area.lowerRight	= VVector3f(1, -1, 0);
	//portal.area.upperLeft	= VVector3f(-1, 1, 0);
	//portal.area.upperRight	= VVector3f(1, 1, 0);
	//portal.area.lowerLeft

	portal.pCell = &modelCell;

	const vuint holeSize = 8;
	hole.ResetSize(holeSize, holeSize);
	hole.GenerateIndices();

	for(vuint x = 0; x < hole.GetWidth(); ++x)
	for(vuint y = 0; y < hole.GetHeight(); ++y)
	{
		hole.GetVertexBuffer()[hole.GetWidth() * y + x].position = 
			terrain.GetVertex(x + 32 - holeSize/2, y + 32 - holeSize/2).position;
	}
}

void VTerrainCell::Cull(
	VCamera* in_pCamera,
	VMultipassDrawList& drawlist
	)
{
	// add portal poly
	//VBuffer<VSimpleVertex> portalVertices(new VSimpleVertex[4], 4);

	//portalVertices[0].position = portal.area.upperLeft;
	//portalVertices[1].position = portal.area.lowerLeft;
	//portalVertices[2].position = portal.area.lowerRight;
	//portalVertices[3].position = portal.area.upperRight;

	//VMeshDescription md = BuildMeshDescription(
	//	drawlist.GetDevice(),
	//	portalVertices.GetDataAddress(),
	//	portalVertices.GetSize()
	//	);

	//md.geometryType = VMeshDescription::Quads;

	VMaterialDescription mat;
	mat.defaultColor = VColor4f(1, 0, 1, 1);
	mat.frontPolyMode = VMaterialDescription::Filled;
	mat.backPolyMode = VMaterialDescription::Filled;
	mat.colorMask = NoColorWrites();
	//mat.depthTestFunction = VMaterialDescription::DepthAlways;

	//drawlist.Add(VModel(
	//	drawlist.GetDevice().CreateMesh(md, mat),
	//	IdentityPtr()),
	//	1);

	drawlist.Add(VModel(
		BuildMesh(drawlist.GetDevice(), hole, mat),
		IdentityPtr()),
		0);

	// add heightmap
	drawlist.Add(VModel(
		BuildMesh(
			drawlist.GetDevice(), 
			terrain, 
			terrain.GetMaterialDescription(drawlist.GetDevice())),
		IdentityPtr()
		), 1);

	// add other cell to render pass -1
	VMultipassDrawList& prePass(drawlist.MakeSubpassList(-1));

	if( portal.pCell )
	{
		portal.pCell->Cull(0, prePass);
	}
}

void VTerrainCell::Hide(VMultipassDrawList& in_DrawList)
{
	// hide own geometry

	// hide geometry of connected cells
	if( portal.pCell )
	{
		portal.pCell->Hide(in_DrawList);
	}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
