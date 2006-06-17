#include <V3d/Tags/VTag.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace tags {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * d'tor
 */
VTag::~VTag()
{
}

VTag::VTag(const std::string& name, vuint32 id)
{
	m_strName = name;
	m_Id = id;
}

vuint32 VTag::GetId() const
{
	return m_Id;
}

std::string VTag::GetName() const
{
	return m_strName;
}

vbool VTag::operator==(const VTag& other) const
{
	return m_Id == other.m_Id;
}

vbool VTag::operator!=(const VTag& other) const
{
	return m_Id != other.m_Id;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::tags
//-----------------------------------------------------------------------------
