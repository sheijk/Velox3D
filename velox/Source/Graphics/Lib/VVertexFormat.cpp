#include <V3d/Graphics/VVertexFormat.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VVertexFormat::VVertexFormat()
{
}

VVertexFormat::VVertexFormat(
	DataTypes in_DataTypes, 
	vuint in_nVertexCount, 
	vuint in_nIndexCount)
{
	// iff index count > 0 there must be indices in the data format
	V3D_ASSERT(
		in_nIndexCount > 0 ? 
			(in_DataTypes & Indices) != 0 : 
			(in_DataTypes & Indices) == 0);

	vuint firstFreeIndex = 0;

	if( in_DataTypes & Coordinates )
	{
		m_CoordinateFormat.SetFirstIndex(firstFreeIndex);
		m_CoordinateFormat.SetCount(in_nVertexCount);
		m_CoordinateFormat.SetStride(3);
		firstFreeIndex += 3 * in_nVertexCount;
	}

	if( in_DataTypes & Colors )
	{
		m_ColorFormat.SetFirstIndex(firstFreeIndex);
		m_ColorFormat.SetCount(in_nVertexCount);
		m_ColorFormat.SetStride(4);
		firstFreeIndex += 4 * in_nVertexCount;
	}

	if( in_DataTypes & Normals )
	{
		m_NormalFormat.SetFirstIndex(firstFreeIndex);
		m_NormalFormat.SetCount(in_nVertexCount);
		m_NormalFormat.SetStride(3);
		firstFreeIndex += 3 * in_nVertexCount;
	}

	if( in_DataTypes & Indices )
	{
		m_IndexFormat.SetFirstIndex(firstFreeIndex);
		m_IndexFormat.SetCount(in_nIndexCount);
		m_IndexFormat.SetStride(1);
		firstFreeIndex += in_nIndexCount;
	}

	if( in_DataTypes & TexCoords )
	{
        SetTexCoordCount(1);
		m_TexCoordFormats[0].SetFirstIndex(firstFreeIndex);
		m_TexCoordFormats[0].SetCount(in_nVertexCount);
		m_TexCoordFormats[0].SetStride(2);
		firstFreeIndex += 2 * sizeof(vfloat32);
	}
}

VDataFormat VVertexFormat::GetCoordinateFormat() const
{
	return m_CoordinateFormat;
}

void VVertexFormat::SetCoordinateFormat(VDataFormat in_Format)
{
	m_CoordinateFormat = in_Format;
}

VDataFormat VVertexFormat::GetColorFormat() const
{
	return m_ColorFormat;
}

void VVertexFormat::SetColorFormat(VDataFormat in_Format)
{
	m_ColorFormat = in_Format;
}

VDataFormat VVertexFormat::GetNormalFormat() const
{
	return m_NormalFormat;
}

void VVertexFormat::SetNormalFormat(VDataFormat in_Format)
{
	m_NormalFormat = in_Format;
}

VDataFormat VVertexFormat::GetIndexFormat() const
{
	return m_IndexFormat;
}

void VVertexFormat::SetIndexFormat(VDataFormat in_Format)
{
	m_IndexFormat = in_Format;
}

vuint VVertexFormat::GetTexCoordCount() const
{
	return vuint(m_TexCoordFormats.size());
}

void VVertexFormat::SetTexCoordCount(vuint in_nNewCount)
{
	m_TexCoordFormats.resize(in_nNewCount);
}

VDataFormat VVertexFormat::GetTexCoordFormat(vuint in_nCoord) const
{
	V3D_VERIFY(in_nCoord < GetTexCoordCount());

	return m_TexCoordFormats[in_nCoord];
}

void VVertexFormat::SetTexCoordFormat(vuint in_nCoord, VDataFormat in_Format)
{
	V3D_ASSERT(in_nCoord < GetTexCoordCount());

	m_TexCoordFormats[in_nCoord] = in_Format;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
