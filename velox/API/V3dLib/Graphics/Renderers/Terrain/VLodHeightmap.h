#ifndef V3D_VLODHEIGHTMAP_2004_05_10_H_H
#define V3D_VLODHEIGHTMAP_2004_05_10_H_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Math.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * A Heightmap with multiple levels of detail. Lod 0 is the highest detail
 * and may be changed. All other lod details will be generated on demand
 *
 * @author sheijk
 */
class VLodHeightmap
{
public:
	typedef VArray2d<vfloat32, vuint> Heightmap;

	VLodHeightmap(vuint in_nLodCount);

	vbool LodLoaded(vuint in_nLevel) const;

    Heightmap& GetLod(vuint in_nLevel);
	const Heightmap& GetLod(vuint in_nLevel) const;

	void GenerateLod(vuint in_nLevel);

	vuint LodCount() const;

	/**
	 * Removes all chached lod data. Call this after changing the height
	 * values of lod 0
	 */
	void InvalidateLodData();

private:
	struct LodInfo
	{
		LodInfo() : bIsLoaded(false) {}

		Heightmap lodData;
		vbool bIsLoaded;
	};

	typedef std::vector<LodInfo> LodList;

	LodList m_Lods;

	const vuint m_nLodCount;

	vuint SizeOfLod(vuint in_nLod) const;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VLODHEIGHTMAP_2004_05_10_H_H
