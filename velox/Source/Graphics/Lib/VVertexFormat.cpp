#include <V3d/Graphics/VVertexFormat.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

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
