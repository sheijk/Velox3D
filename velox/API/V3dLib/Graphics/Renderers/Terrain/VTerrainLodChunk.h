#ifndef V3D_VTERRAINLODCHUNK_2004_05_10_H_H
#define V3D_VTERRAINLODCHUNK_2004_05_10_H_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Graphics/Renderers/Terrain/VLodHeightmap.h>
#include <V3dLib/Graphics/Generators/VHeightmapMesh.h>
#include <V3dLib/Graphics/Geometry.h>

#include <algorithm>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Applies the height values of a 2d array to a VHeightmapMesh
 */
template<typename Array2d, typename VertexStructure>
void ApplyHeightValues(
	VHeightmapMesh<VertexStructure>& io_Heightmap, 
	const Array2d& in_Heights
	);

template<typename T>
class VRectangle
{
public:
	typedef T Scalar;
	
	Scalar left, top, right, bottom;

	VRectangle() :
		left(0), top(0), right(0), bottom(0)
	{
	}

	VRectangle(Scalar l, Scalar t, Scalar r, Scalar b) :
		left(l), top(t), right(r), bottom(b)
	{
	}
};

/**
 * Creates meshes from a heightmap and manages the meshes, and geometry data
 *
 * @author sheijk
 */
class VTerrainLodChunk
{
	typedef VTexturedVertex MyVertexType;
public:
	typedef IVDevice::MeshHandle MeshHandle;

	VTerrainLodChunk(
		vuint in_nLodCount, 
		vfloat32 in_fMeshSize, 
		VRectangle<vfloat32> in_TexCoords,
		IVDevice& in_Device
		//const VMaterialDescription& in_Material
		);

	virtual ~VTerrainLodChunk();
	
	vbool IsMeshLoaded(vuint in_nLod) const;
	//MeshHandle CreateMesh(vuint in_nLod);
	VLodHeightmap::Heightmap& GetLodHeights(vuint in_nLod);
	const VLodHeightmap::Heightmap& GetLodHeights(vuint in_nLod) const;
	vuint LodCount() const;
	void InvalidateLodData();

	void SetLod(vuint in_nLod);
	vuint GetLod() const;
	MeshHandle GetCurrentMesh() const;
	VLodHeightmap::Heightmap& GetCurrentHeightmap();
	const VLodHeightmap::Heightmap& GetCurrentHeightmap() const;
	void UpdateCurrentMesh(const VMaterialDescription& in_Mat);

	enum Direction
	{
		Right, Left, Top, Bottom
	};

	void SetNeighbourLod(Direction in_Dir, vuint in_nLod);

private:
	struct LevelOfDetailInfo
	{
		LevelOfDetailInfo() : hMesh(0) {}

		MeshHandle hMesh;
	};

	const vuint m_nLodCount;
	const vfloat32 m_fMeshSize;

	vuint m_NeighbourLod[4];

	std::vector<LevelOfDetailInfo> m_LodInfos;
	IVDevice& m_Device;

	VLodHeightmap m_LodHeightmap;
	VLodHeightmap::Heightmap m_CurrentHeightmap;

	MeshHandle m_hCurrentMesh;
	IVDevice::BufferHandle m_hVertexBuffer;
	IVDevice::BufferHandle m_hIndexBuffer;

	vuint m_nCurrentLod;

	VRectangle<vfloat32> m_TexCoords;

	//const VMaterialDescription& m_Material;

	void DeleteDeviceData();
	void AdjustBorderVertical(
		VHeightmapMesh<MyVertexType>& model,
		vuint borderLod,
		vuint x
		);
	void AdjustBorderHorizontal(
		VHeightmapMesh<MyVertexType>& model,
		vuint borderLod,
		vuint x
		);
};

//-----------------------------------------------------------------------------
template<typename Array2d, typename VertexStructure>
void ApplyHeightValues(
	VHeightmapMesh<VertexStructure>& io_Heightmap, 
	const Array2d& in_Heights
	)
{
	V3D_ASSERT(in_Heights.GetWidth() == io_Heightmap.GetWidth());
	V3D_ASSERT(in_Heights.GetHeight() == io_Heightmap.GetHeight());

	vfloat32 maxH = -1000;
	vfloat32 minH = 1000;

	for(vuint y = 0; y < io_Heightmap.GetHeight(); ++y)
	for(vuint x = 0; x < io_Heightmap.GetWidth(); ++x)
	{
		vfloat32 h = in_Heights.Get(x, y);
		io_Heightmap.GetVertex(x, y).position.z = in_Heights.Get(x,y);
		//io_Heightmap.GetVertex(x, y).texCoords = VTexCoord2f(
		//	vfloat32(x) / vfloat32(io_Heightmap.GetWidth()-1),
		//	vfloat32(y) / vfloat32(io_Heightmap.GetHeight()-1)
		//	);

		if( h < minH )
			minH = h;

		if( h > maxH )
			maxH = h;
	}

	//minH *= .8f;
	//maxH *= .8f;

	// set colors
	//for(vuint y = 0; y < io_Heightmap.GetHeight(); ++y)
	//for(vuint x = 0; x < io_Heightmap.GetWidth(); ++x)
	//{
	//	vfloat32 h = in_Heights.Get(x, y);

	//	vfloat32 percentage = (h - minH)/(maxH - minH);

	//	io_Heightmap.GetVertex(x, y).color.green = percentage/3;
	//}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAINLODCHUNK_2004_05_10_H_H
