#include <v3d/Graphics/VMeshDescription.h>
#include <set>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

VMeshDescription::GeometryType VMeshDescription::GetGeometryType() const
{
	return m_GeometryType;
}

void VMeshDescription::SetGeometryType(GeometryType in_GeometryType)
{
	m_GeometryType = in_GeometryType;
}

void VMeshDescription::SetCoordinateData(
	BufferHandle in_hBuffer, 
	VDataFormat in_Format)
{
	m_Vertices.format = in_Format;
	m_Vertices.hBuffer = in_hBuffer;
}

VDataFormat VMeshDescription::GetCoordinateFormat() const
{
	return m_Vertices.format;
}

VMeshDescription::BufferHandle VMeshDescription::GetCoordinateBuffer() const
{
	return m_Vertices.hBuffer;
}

void VMeshDescription::SetColorData(
	BufferHandle in_hBuffer, 
	VDataFormat in_Format)
{
	m_Colors.format = in_Format;
	m_Colors.hBuffer = in_hBuffer;
}

VDataFormat VMeshDescription::GetColorFormat() const
{
	return m_Colors.format;
}

VMeshDescription::BufferHandle VMeshDescription::GetColorBuffer() const
{
	return m_Colors.hBuffer;
}

void VMeshDescription::SetIndexData(
	BufferHandle in_hBuffer, 
	VDataFormat in_Format)
{
	m_Indices.format = in_Format;
	m_Indices.hBuffer = in_hBuffer;
}

VDataFormat VMeshDescription::GetIndexFormat() const
{
	return m_Indices.format;
}

VMeshDescription::BufferHandle VMeshDescription::GetIndexBuffer() const
{
	return m_Indices.hBuffer;
}

vuint VMeshDescription::GetTexCoordCount() const
{
	return vuint(m_TexCoords.size());
}

void VMeshDescription::SetTexCoordData(
	vuint in_nCoord,
	BufferHandle in_hBuffer, 
	VDataFormat in_Format)
{
	SetMinTexCoords(in_nCoord + 1);

    m_TexCoords[in_nCoord].format = in_Format;
	m_TexCoords[in_nCoord].hBuffer = in_hBuffer;
}

VDataFormat VMeshDescription::GetTexCoordFormat(vuint in_nCoord) const
{
	V3D_VERIFY(in_nCoord < GetTexCoordCount());

	return m_TexCoords[in_nCoord].format;
}

VMeshDescription::BufferHandle 
VMeshDescription::GetTexCoordBuffer(vuint in_nCoord) const
{
	V3D_VERIFY(in_nCoord < GetTexCoordCount());

	return m_TexCoords[in_nCoord].hBuffer;
}

void VMeshDescription::SetMinTexCoords(vuint in_nCoordCount)
{
	if( GetTexCoordCount() < in_nCoordCount )
	{
		m_TexCoords.resize(in_nCoordCount);
	}
}

VMeshDescription::DataRef::DataRef()
{
	hBuffer = 0;
}

void VMeshDescription::Replace(
	DataRef& io_Ref, 
	BufferHandle in_hOldBuffer, 
	BufferHandle in_hNewBuffer)
{
	if( io_Ref.hBuffer == in_hOldBuffer )
		io_Ref.hBuffer = in_hNewBuffer;
}

void VMeshDescription::ReplaceBuffer(
	BufferHandle in_hOldBuffer, 
	BufferHandle in_hNewBuffer)
{
	Replace(m_Vertices,	in_hOldBuffer, in_hNewBuffer);
	Replace(m_Colors,	in_hOldBuffer, in_hNewBuffer);

	Replace(m_Indices,	in_hOldBuffer, in_hNewBuffer);

	for(vuint texCoordId = 0; texCoordId < GetTexCoordCount(); ++texCoordId)
	{
		Replace(m_TexCoords[texCoordId], in_hOldBuffer, in_hNewBuffer);
	}
}

std::vector<VMeshDescription::BufferHandle> VMeshDescription::GetAllBuffers() const
{
	std::set<BufferHandle> buffers;

	buffers.insert(m_Vertices.hBuffer);
	buffers.insert(m_Colors.hBuffer);

	for(vuint texCoordId = 0; texCoordId < GetTexCoordCount(); ++texCoordId)
	{
		buffers.insert(m_TexCoords[texCoordId].hBuffer);
	}

	buffers.insert(m_Indices.hBuffer);

	// remove null
	buffers.erase(buffers.find(0));

	return std::vector<BufferHandle>(buffers.begin(), buffers.end());
}

//-----------------------------------------------------------------------------
} } // namespace v3d::graphics
//-----------------------------------------------------------------------------


