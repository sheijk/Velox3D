#include <V3dLib/Graphics/Renderers/Terrain/VLodHeightmap.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

VLodHeightmap::VLodHeightmap(vuint in_nLodCount)
	:
	m_nLodCount(in_nLodCount)
{
	const vuint size = SizeOfLod(0);

	m_Lods.resize(in_nLodCount);

	// create lod 0
	m_Lods[0].lodData.Resize(size, size, Heightmap::FillZero);
	m_Lods[0].bIsLoaded = true;
}

vbool VLodHeightmap::LodLoaded(vuint in_nLevel) const
{
	V3D_ASSERT(in_nLevel < m_nLodCount);

	return m_Lods[in_nLevel].bIsLoaded;
}

VLodHeightmap::Heightmap& VLodHeightmap::GetLod(vuint in_nLevel)
{
	if( ! LodLoaded(in_nLevel) )
		GenerateLod(in_nLevel);

	return m_Lods[in_nLevel].lodData;
}

V3D_DECLARE_EXCEPTION(VLodGenerationException, VException);

const VLodHeightmap::Heightmap& VLodHeightmap::GetLod(vuint in_nLevel) const
{
	if( ! LodLoaded(in_nLevel) )
	{
		V3D_THROW(VLodGenerationException,
			VString("accessing lod ") + in_nLevel + 
				VString(" which has not been loaded, yet from const function"));
	}

	return m_Lods[in_nLevel].lodData;
}

void VLodHeightmap::GenerateLod(vuint in_nLevel)
{
	using v3d::math::SampleDown;

	if( ! LodLoaded(in_nLevel) )
	{
		GenerateLod(in_nLevel-1);

		// generate lod from superordinated lod
		const vuint size = SizeOfLod(in_nLevel);
		m_Lods[in_nLevel].lodData.Resize(
			size, size, Heightmap::Uninitialized);

		SampleDown(m_Lods[in_nLevel].lodData, m_Lods[in_nLevel-1].lodData);
		m_Lods[in_nLevel].bIsLoaded = true;
	}
}

vuint VLodHeightmap::LodCount() const
{
	return m_nLodCount;
}

void VLodHeightmap::InvalidateLodData()
{
	for(
		LodList::iterator lod = m_Lods.begin();
		lod != m_Lods.end();
		++lod
		)
	{
		lod->bIsLoaded = false;
	}
}

vuint VLodHeightmap::SizeOfLod(vuint in_nLod) const
{
	if( in_nLod >= m_nLodCount )
		return 0;
	if( in_nLod == m_nLodCount - 1 )
		return 2;
	else
		return SizeOfLod(in_nLod+1)*2 - 1;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
