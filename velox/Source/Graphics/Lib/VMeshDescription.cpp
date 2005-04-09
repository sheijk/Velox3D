#include <v3d/Graphics/VMeshDescription.h>
#include <set>

#include <V3d/Resource.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d::resource;

VMeshDescription::VMeshDescription()
	:
	m_GeometryType(Triangles) 
{
	SetTexCoordCount(1);
}

VMeshDescription::VMeshDescription(const VVertexFormat& in_Format)
	: 
	VVertexFormat(in_Format),
	m_GeometryType(Triangles)
{
	SetTexCoordCount(in_Format.GetTexCoordCount());
}

VMeshDescription::VMeshDescription(const VMeshDescription& in_Source)
	: VVertexFormat(in_Source)
{
	m_Vertices = in_Source.m_Vertices;
	m_Colors = in_Source.m_Colors;
	m_Indices = in_Source.m_Indices;
	m_TexCoords = in_Source.m_TexCoords;

	m_GeometryType = in_Source.m_GeometryType;
}

//-----------------------------------------------------------------------------

VMeshDescription::GeometryType VMeshDescription::GetGeometryType() const
{
	return m_GeometryType;
}

void VMeshDescription::SetGeometryType(GeometryType in_GeometryType)
{
	m_GeometryType = in_GeometryType;
}

//-----------------------------------------------------------------------------
//--- coordinates


void VMeshDescription::SetCoordinateResource(const std::string& in_Id)
{
	m_Vertices.resource = in_Id;
}

std::string VMeshDescription::GetCoordinateResource() const
{
	return m_Vertices.resource;
}

//--- colors
void VMeshDescription::SetColorResource(const std::string& in_Id)
{
	m_Colors.resource = in_Id;
}

std::string VMeshDescription::GetColorResource() const
{
	return m_Colors.resource;
}

//--- normals
void VMeshDescription::SetNormalResource(const std::string& in_Id)
{
	m_Normals.resource = in_Id;
}

std::string VMeshDescription::GetNormalResource() const
{
	return m_Normals.resource;
}

//--- indices
void VMeshDescription::SetIndexResource(const std::string& in_Id)
{
	m_Indices.resource = in_Id;
}

std::string VMeshDescription::GetIndexResource() const
{
	return m_Indices.resource;
}

//--- tex coords
void VMeshDescription::SetTexCoordResource(vuint in_nIndex, const std::string& in_Id)
{
	V3D_ASSERT(in_nIndex < GetTexCoordCount());
	m_TexCoords[in_nIndex].resource = in_Id;
}

std::string VMeshDescription::GetTexCoordResource(vuint in_nIndex) const
{
	V3D_ASSERT(in_nIndex < GetTexCoordCount());
	return m_TexCoords[in_nIndex].resource;
}

void VMeshDescription::SetTexCoordCount(vuint in_nNewCount)
{
	VVertexFormat::SetTexCoordCount(in_nNewCount);
	m_TexCoords.resize(in_nNewCount);
}

//-----------------------------------------------------------------------------
} } // namespace v3d::graphics
//-----------------------------------------------------------------------------

