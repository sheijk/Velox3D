#include "VTriangle.h"
//-------------------------------------------------------------------------

VTriangle::VTriangle()
{
}

VTriangle::VTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	m_Vertices[0] = v1;
	m_Vertices[1] = v2;
	m_Vertices[2] = v3;
}

VTriangle::VTriangle(const Vertex[3]& v)
{
	m_Vertices[0] = v[0];
	m_Vertices[1] = v[1];
	m_Vertices[2] = v[2];
}

void VTriangle::SetVertex(vuint in_nIndex, const Vertex& in_Value)
{
	m_Vertices[in_nIndex] = in_Value;
}

VTriangle::Vertex VTriangle::GetVertex(vuint in_nIndex)
{
	return m_Vertices[in_nIndex];
}


vuint VTriangle::VertexCount()
{
	return 3;
}


//-------------------------------------------------------------------------
