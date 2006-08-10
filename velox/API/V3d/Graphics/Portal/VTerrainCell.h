#ifndef V3D_VTERRAINCELL_2004_04_12_H
#define V3D_VTERRAINCELL_2004_04_12_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Graphics/Portal/IVCell.h>
#include <V3dLib/Graphics/Generators/VTerrainChunkMesh.h>
#include <V3dLib/Graphics/Generators/VHeightmapMesh.h>

#include <V3d/Math/VRect.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

class VHeightmapSubMesh : public VDynamicGeometryData<VSimpleVertex>
{
public:
	VHeightmapSubMesh();

	void GenerateSubArea(
		math::VRect<vuint> area,		
		const VTerrainChunkMesh& terrain
		);
};

class VPortal 
{
public:
//	typedef VQuad<VVector3f> PortalArea;

	IVCell* pCell;
//	PortalArea area;

	VPortal()
	{
		pCell = 0;
	}
};


class VTerrainCell : public IVCell
{
	VTerrainChunkMesh terrain;
	IVCell& modelCell;
	//VModelCell modelCell;
	VPortal portal;
	VHeightmapMesh<VSimpleVertex> hole;

public:
	VTerrainCell(
		VMultipassDrawList& drawList,
		IVCell& cell
		);

	virtual void Cull(
		VCamera* in_pCamera,
		VMultipassDrawList& drawlist
		);

	virtual void Hide(VMultipassDrawList& in_DrawList);
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAINCELL_2004_04_12_H
