#include <cmath>

template<typename VertexStructure>
VPolarSphere<VertexStructure>::VPolarSphere(
	vuint in_nRings, 
	vuint in_nSectors) :
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
vuint VPolarSphere<VertexStructure>::CalculateVertexCount()
{
	return m_nSectors * m_nRings;
}

template<typename VertexStructure>
vuint VPolarSphere<VertexStructure>::CalculateIndexCount()
{
	return 2 * (m_nSectors+1) * m_nRings;
}

template<typename VertexStructure>
void VPolarSphere<VertexStructure>::GenerateCoordinates()
{
	using namespace std;

	const float pi = 3.141592654f;

	const float deltaAngle = 2 * pi / m_nSectors;
	const float deltaY = 2.0f / (m_nRings-1);

	float color = 0;
	const float deltaColor = 1.0f / CalculateVertexCount();

	float angle = 0;
	for(vuint sector = 0; sector < m_nSectors; ++sector, angle += deltaAngle)
	{
		const float xpos = cos(angle);
		const float zpos = sin(angle);

		float ypos = -1;
		int ring = 0;
		for(vuint ring = 0; ring < m_nRings; ++ring, ypos += deltaY)
		{
			const float scale = sqrt(1 - ypos*ypos);
			geometry.vertices[GetVertexNum(sector, ring)].position.x = xpos * scale;
			geometry.vertices[GetVertexNum(sector, ring)].position.y = ypos;
			geometry.vertices[GetVertexNum(sector, ring)].position.z = zpos * scale;

			geometry.vertices[ring * m_nSectors + sector].color.red = color;
			color += deltaColor;
		}
	}
}

template<typename VertexStructure>
vuint VPolarSphere<VertexStructure>::GetVertexNum(vuint sector, vuint ring)
{
	return ring * m_nSectors + sector;
}

template<typename VertexStructure>
void VPolarSphere<VertexStructure>::GenerateIndices()
{
	for(vuint index = 0; index < geometry.indices.GetSize(); ++index)
	{
		geometry.indices[index] = 0;
	}

	vuint indexNum = 0;

	for(vuint ring = 0; ring < m_nRings-1; ++ring)
	{
		for(vuint sector = 0; sector < m_nSectors; ++sector)
		{
			geometry.indices[indexNum] = GetVertexNum(sector, ring);
			++indexNum;
			geometry.indices[indexNum] = GetVertexNum(sector, ring+1);
			++indexNum;
		}
		geometry.indices[indexNum] = GetVertexNum(0, ring);
		++indexNum;
		geometry.indices[indexNum] = GetVertexNum(0, ring+1);
		++indexNum;
	}
}

template<typename VertexStructure>
typename VPolarSphere<VertexStructure>::VertexBuffer&
VPolarSphere<VertexStructure>::GetVertexBuffer()
{
	return geometry.vertices;
}

template<typename VertexStructure>
typename VPolarSphere<VertexStructure>::IndexBuffer&
VPolarSphere<VertexStructure>::GetIndexBuffer()
{
	return geometry.indices;
}

template<typename VertexStructure>
v3d::graphics::VMeshDescription::GeometryType
VPolarSphere<VertexStructure>::GetGeometryType()
{
	return geometry.type;
}