#include <cmath>

template<typename VertexStructure>
VPolarSphereMesh<VertexStructure>::VPolarSphere(
	vuint in_nRings, 
	vuint in_nSectors) :
m_cfTop(1.0f),
m_cfBottom(-1.0f),
m_nRings(in_nRings), 
m_nSectors(in_nSectors),
m_nVertexCount(CalculateVertexCount()),
geometry(
		 v3d::graphics::VMeshDescription::TriangleStrip, 
		 CalculateVertexCount(), CalculateIndexCount()
		 )
{
	GenerateIndices();
}

template<typename VertexStructure>
VPolarSphereMesh<VertexStructure>::VPolarSphere(
	vuint in_nRings, vuint in_nSectors, 
	vfloat32 in_fBottom, vfloat32 in_fTop
	) :
m_cfTop(in_fTop),
m_cfBottom(in_fBottom),
m_nRings(in_nRings), 
m_nSectors(in_nSectors),
m_nVertexCount(CalculateVertexCount()),
geometry(
		 v3d::graphics::VMeshDescription::TriangleStrip, 
		 CalculateVertexCount(), CalculateIndexCount()
		 )
{
	GenerateIndices();
}

template<typename VertexStructure>
vuint VPolarSphereMesh<VertexStructure>::CalculateVertexCount()
{
	return m_nSectors * m_nRings;
}

template<typename VertexStructure>
vuint VPolarSphereMesh<VertexStructure>::CalculateIndexCount()
{
	return 2 * (m_nSectors+1) * m_nRings;
}

template<typename VertexStructure>
void VPolarSphereMesh<VertexStructure>::GenerateCoordinates()
{
	using namespace std;

	const float pi = 3.141592654f;

	const float deltaAngle = 2 * pi / m_nSectors;
	const float height = m_cfTop - m_cfBottom;
	const float deltaY = height / (m_nRings-1);

	float angle = 0;
	for(vuint sector = 0; sector < m_nSectors; ++sector, angle += deltaAngle)
	{
		const float xpos = cos(angle);
		const float zpos = sin(angle);

		float ypos = m_cfBottom;
		int ring = 0;
		for(vuint ring = 0; ring < m_nRings; ++ring, ypos += deltaY)
		{
			const float scale = sqrt(1 - ypos*ypos);
			geometry.GetVertexBuffer()[GetVertexNum(sector, ring)].position.x = xpos * scale;
			geometry.GetVertexBuffer()[GetVertexNum(sector, ring)].position.y = ypos;
			geometry.GetVertexBuffer()[GetVertexNum(sector, ring)].position.z = zpos * scale;
		}
	}
}

template<typename VertexStructure>
void VPolarSphereMesh<VertexStructure>::GenerateTexCoords()
{
	const vfloat32 deltaRing =  1.0f / m_nRings;
	const vfloat32 deltaSector = 1.0f / m_nSectors;

	// for each ring
	for(vuint ring = 0; ring < m_nRings; ++ring)
	{
		// for each sector
		for(vuint sector = 0; sector < m_nSectors; ++sector)
		{
			VertexStructure& vertex =
				geometry.GetVertexBuffer()[GetVertexNum(sector, ring)];

            vertex.texCoords.u = deltaSector * sector;
			vertex.texCoords.v = deltaRing * ring;
		}
	}
}

template<typename VertexStructure>
vuint VPolarSphereMesh<VertexStructure>::GetVertexNum(vuint sector, vuint ring)
{
	return ring * m_nSectors + sector;
}

template<typename VertexStructure>
void VPolarSphereMesh<VertexStructure>::GenerateIndices()
{
	for(vuint index = 0; index < geometry.GetIndexBuffer().GetSize(); ++index)
	{
		geometry.GetIndexBuffer()[index] = 0;
	}

	vuint indexNum = 0;

	for(vuint ring = 0; ring < m_nRings-1; ++ring)
	{
		for(vuint sector = 0; sector < m_nSectors; ++sector)
		{
			geometry.GetIndexBuffer()[indexNum] = GetVertexNum(sector, ring);
			++indexNum;
			geometry.GetIndexBuffer()[indexNum] = GetVertexNum(sector, ring+1);
			++indexNum;
		}
		geometry.GetIndexBuffer()[indexNum] = GetVertexNum(0, ring);
		++indexNum;
		geometry.GetIndexBuffer()[indexNum] = GetVertexNum(0, ring+1);
		++indexNum;
	}
}

template<typename VertexStructure>
typename VPolarSphereMesh<VertexStructure>::VertexBuffer&
VPolarSphereMesh<VertexStructure>::GetVertexBuffer()
{
	return geometry.GetVertexBuffer();
}

template<typename VertexStructure>
typename VPolarSphereMesh<VertexStructure>::IndexBuffer&
VPolarSphereMesh<VertexStructure>::GetIndexBuffer()
{
	return geometry.GetIndexBuffer();
}

template<typename VertexStructure>
v3d::graphics::VMeshDescription::GeometryType
VPolarSphereMesh<VertexStructure>::GetGeometryType()
{
	return geometry.GetGeometryType();
}