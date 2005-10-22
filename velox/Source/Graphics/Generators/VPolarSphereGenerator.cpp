#include <V3dLib/Graphics/Generators/VPolarSphereGenerator.h>
//-----------------------------------------------------------------------------
#include <cmath>

#include <V3dLib/Graphics/Geometry/VTexCoord2f.h>
#include <V3d/Math/VVectorOps.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VPolarSphereGenerator::VPolarSphereGenerator(
	VVertexFormat::DataTypes in_DataTypes,
	vuint in_nRings, vuint in_nSectors, 
	vfloat32 in_fBottom, vfloat32 in_fTop,
	vfloat32 in_fSize
	)
{
	V3D_THROW(VException, "not implemented");
//	if( (in_DataTypes & VVertexFormat::Indices) == VVertexFormat::Indices )
//		V3D_THROW(VMeshGenException, "Generating a polar sphere requires indices");
//
//	in_DataTypes = VVertexFormat::DataTypes( in_DataTypes & (!VVertexFormat::Indices) );
//
//	m_nSectors = in_nSectors;
//	m_nRings = in_nRings;
//	m_fBottom = in_fBottom;
//    m_fTop = in_fTop;
//    
//	m_Format = VVertexFormat(
//		in_DataTypes,
//		CalculateVertexCount(), 0);
////		CalculateIndexCount());
}

VPolarSphereGenerator::VPolarSphereGenerator(
	VVertexFormat::DataTypes in_DataTypes,
	vuint in_nRings, vuint in_nSectors,
	vfloat32 in_fSize)
{
	//if( (in_DataTypes & VVertexFormat::Indices) != 0 )
	//	V3D_THROW(VMeshGenException, "Generating a polar sphere requires indices");

	in_DataTypes = VVertexFormat::DataTypes( in_DataTypes & (~VVertexFormat::Indices) );

	m_nSectors = in_nSectors;
	m_nRings = in_nRings;
	m_fBottom = -1.0f;
	m_fTop = 1.0f;
	m_fSize = in_fSize;

	m_Format = VVertexFormat(
		in_DataTypes,
		CalculateVertexCount(), 0);
}

/**
 * d'tor
 */
VPolarSphereGenerator::~VPolarSphereGenerator()
{
}

VVertexBuffer* VPolarSphereGenerator::CreateVertexBuffer() const
{
	VVertexBuffer* pVertexBuffer = new VVertexBuffer(m_Format);
	//GenerateIndices(pVertexBuffer);

	if( m_Format.Contains(VVertexFormat::Coordinates) )
		GenerateCoordinates(pVertexBuffer);

	if( m_Format.Contains(VVertexFormat::TexCoords) )
		GenerateTexCoords(pVertexBuffer);

	return pVertexBuffer;
}

VVertexBuffer* VPolarSphereGenerator::CreateIndexBuffer() const
{
	VVertexFormat indexFormat;
	indexFormat.SetIndexFormat(VDataFormat(0, CalculateIndexCount(), 1));

    VVertexBuffer* pIndexBuffer = new VVertexBuffer(indexFormat);
	GenerateIndices(pIndexBuffer);

	return pIndexBuffer;
}

vuint VPolarSphereGenerator::CalculateVertexCount() const
{
	return m_nSectors * m_nRings;
}

vuint VPolarSphereGenerator::CalculateIndexCount() const
{
	return 2 * (m_nSectors+1) * m_nRings;
}

vuint VPolarSphereGenerator::GetVertexNum(vuint sector, vuint ring) const
{
	return ring * m_nSectors + sector;
}

void VPolarSphereGenerator::GenerateIndices(VVertexBuffer* io_pVB) const
{
	//for(vuint index = 0; index < geometry.GetIndexBuffer().GetSize(); ++index)
	for(vuint index = 0; index < io_pVB->GetIndexCount(); ++index)
	{
		io_pVB->SetIndex(0, index);
	}

	vuint indexNum = 0;

	for(vuint ring = 0; ring < m_nRings-1; ++ring)
	{
		for(vuint sector = 0; sector < m_nSectors; ++sector)
		{
			io_pVB->SetIndex(GetVertexNum(sector, ring), indexNum);
			//geometry.GetIndexBuffer()[indexNum] = GetVertexNum(sector, ring);
			++indexNum;
			io_pVB->SetIndex(GetVertexNum(sector, ring+1), indexNum);
			//geometry.GetIndexBuffer()[indexNum] = GetVertexNum(sector, ring+1);
			++indexNum;
		}
		//geometry.GetIndexBuffer()[indexNum] = GetVertexNum(0, ring);
		io_pVB->SetIndex(GetVertexNum(0, ring), indexNum);
		++indexNum;
		//geometry.GetIndexBuffer()[indexNum] = GetVertexNum(0, ring+1);
		io_pVB->SetIndex(GetVertexNum(0, ring+1), indexNum);
		++indexNum;
	}
}

void VPolarSphereGenerator::GenerateCoordinates(VVertexBuffer* io_pVB) const
{
	using namespace std;

	const float pi = 3.141592654f;

	const float deltaAngle = 2 * pi / m_nSectors;
	const float height = m_fTop - m_fBottom;
	const float deltaY = height / (m_nRings-1);

	float angle = 0;
	for(vuint sector = 0; sector < m_nSectors; ++sector, angle += deltaAngle)
	{
		const float xpos = cos(angle);
		const float zpos = sin(angle);

		float ypos = m_fBottom;
		int ring = 0;
		for(vuint ring = 0; ring < m_nRings; ++ring, ypos += deltaY)
		{
			const float scale = sqrt(1 - ypos*ypos);
			//const float scale = 1.0f;
			VVector3f coord;
			coord.Set(xpos * scale, ypos, zpos * scale);
			coord *= m_fSize;
			io_pVB->SetCoordinate(coord, GetVertexNum(sector, ring));
			//geometry.GetVertexBuffer()[GetVertexNum(sector, ring)].position.x = xpos * scale;
			//geometry.GetVertexBuffer()[GetVertexNum(sector, ring)].position.y = ypos;
			//geometry.GetVertexBuffer()[GetVertexNum(sector, ring)].position.z = zpos * scale;
		}
	}
}

void VPolarSphereGenerator::GenerateTexCoords(VVertexBuffer* io_pVB) const
{
	const vfloat32 deltaRing = 1.0f / m_nRings;
	const vfloat32 deltaSector = 1.0f / m_nSectors;

	// for each ring
	for(vuint ring = 0; ring < m_nRings; ++ring)
	{
		// for each sector
		for(vuint sector = 0; sector < m_nSectors; ++sector)
		{
			//VertexStructure& vertex =
			//	geometry.GetVertexBuffer()[GetVertexNum(sector, ring)];

			//vertex.texCoords.u = deltaSector * sector;
			//vertex.texCoords.v = deltaRing * ring;

			VTexCoord2f texCoord;
			texCoord.u = deltaSector * sector;
			texCoord.v = deltaRing * ring;
			io_pVB->SetTexCoord(0, GetVertexNum(sector, ring), texCoord);
		}
	}
}

VMeshDescription::GeometryType VPolarSphereGenerator::GetGeometryType() const
{
	return VMeshDescription::TriangleStrip;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
