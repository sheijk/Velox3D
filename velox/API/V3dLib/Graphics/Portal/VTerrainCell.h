#ifndef V3D_VTERRAINCELL_2004_04_12_H
#define V3D_VTERRAINCELL_2004_04_12_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Graphics/Portal/IVCell.h>
#include <V3dLib/Graphics/Generators/VTerrainChunk.h>
#include <V3dLib/Graphics/Generators/VHeightmap.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

template<typename Scalar>
struct VRect
{
	typedef Scalar ScalarType;

	VRect(ScalarType l, ScalarType t, ScalarType r, Scalar b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	ScalarType left;
	ScalarType top;
	ScalarType right;
	ScalarType bottom;

	ScalarType GetWidth() const
	{
		return right - left;
	}

	ScalarType GetHeight() const
	{
		return top - bottom;
	}
};

class VHeightmapSubMesh : public VDynamicGeometryData<VSimpleVertex>
{
public:
	VHeightmapSubMesh();

	void GenerateSubArea(
		VRect<vuint> area,		
		const VTerrainChunk& terrain
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
	VTerrainChunk terrain;
	IVCell& modelCell;
	//VModelCell modelCell;
	VPortal portal;
	VHeightmap<VSimpleVertex> hole;

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
