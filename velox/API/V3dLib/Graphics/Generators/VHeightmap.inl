template <typename VertexStructure>
vuint VHeightmap<VertexStructure>::GetVertexCount() const
{
	return m_nWidth * m_nHeight;
}

template <typename VertexStructure>
vuint VHeightmap<VertexStructure>::GetIndexCount() const
{
	return m_nWidth * (m_nHeight-1) * 2 + ((m_nHeight-1) * 2);
}

template <typename VertexStructure>
vuint VHeightmap<VertexStructure>::GetVertexNum(vuint x, vuint y) const
{
	return y * m_nWidth + x;
}

template <typename VertexStructure>
VertexStructure& VHeightmap<VertexStructure>::GetVertex(vuint x, vuint y)
{
	return GetVertexBuffer()[y * m_nWidth + x];
}

template <typename VertexStructure>
const VertexStructure& 
VHeightmap<VertexStructure>::GetVertex(vuint x, vuint y) const
{
	return GetVertexBuffer()[y * m_nWidth + x];
}

template <typename VertexStructure>
vfloat32 VHeightmap<VertexStructure>::GetHeight(vuint x, vuint y) const
{
	return vfloat32(m_pHeightmap->GetData()[y * m_nWidth + x]);
}

template <typename VertexStructure>
void VHeightmap<VertexStructure>::GenerateCoordinatesAtZ(vfloat32 in_nZ)
{
	vfloat32 left = -1;
	vfloat32 right = 1;
	vfloat32 top = -1;
	vfloat32 bottom = 1;

	const vfloat32 xdelta = (right - left) / m_nWidth;
	const vfloat32 ydelta = (bottom - top) / m_nHeight;
    
	for(vint x = 0; x < m_nWidth; ++x)
	{
		for(vint y = 0; y < m_nHeight; ++y)
		{
            GetVertex(x, y).position.x = x * xdelta + left;
			GetVertex(x, y).position.y = y * ydelta + top;
			GetVertex(x, y).position.z = in_nZ;
		}
	}
}

template <typename VertexStructure>
void VHeightmap<VertexStructure>::GenerateTexCoords()
{
	GenerateInterpolatedTexCoords(GetVertexBuffer(), m_nWidth, m_nHeight);
}

template <typename VertexStructure>
void VHeightmap<VertexStructure>::GenerateIndices()
{
	vuint num = 0;

	// for each y
	for(vuint y = 0; y < m_nHeight - 1; ++y)
	{
		// create strip
		for(vint x = 0; x < m_nWidth; ++x)
		{
			GetIndexBuffer()[num] = GetVertexNum(x, y);
			++num;

			GetIndexBuffer()[num] = GetVertexNum(x, y + 1);
			++num;
		}

		// add degenerated triangle
        GetIndexBuffer()[num] = GetVertexNum(x - 1, y + 1);
		++num;
		GetIndexBuffer()[num] = GetVertexNum(0, y + 1);
		++num;
	}

	V3D_ASSERT(num == GetIndexBuffer().GetSize());
}

template <typename VertexStructure>
VHeightmap<VertexStructure>::VHeightmap(vuint in_nWidth, vuint in_nHeight)
{
	SetGeometryType(VMeshDescription::TriangleStrip);

	ResetSize(in_nWidth, in_nHeight);
}

template<typename VertexStructure>
VHeightmap<VertexStructure>::VHeightmap()
{
	SetGeometryType(VMeshDescription::TriangleStrip);
	ResizeVertexBuffer(0);
	ResizeIndexBuffer(0);
//	ResetSize(0,0);
}

template <typename VertexStructure>
void VHeightmap<VertexStructure>::ResetSize(vuint in_nWidth, vuint in_nHeight)
{
	m_nHeight = in_nHeight;
	m_nWidth = in_nWidth;

	ResizeVertexBuffer(GetVertexCount());
	ResizeIndexBuffer(GetIndexCount());        

	GenerateCoordinatesAtZ(0);
}

template <typename VertexStructure>
vuint VHeightmap<VertexStructure>::GetWidth() const
{
	return m_nWidth;
}

template <typename VertexStructure>
vuint VHeightmap<VertexStructure>::GetHeight() const 
{
	return m_nHeight;
}