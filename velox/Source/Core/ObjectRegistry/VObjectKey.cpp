#include <v3d/Core/VObjectKey.h>
//------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VObjectKey::VObjectKey()
{
}

VObjectKey::VObjectKey(const std::string &in_strName)
{
	m_strName = in_strName;
}

VObjectKey::VObjectKey(const char* in_pcName)
{
	m_strName = in_pcName;
}

VObjectKey::~VObjectKey()
{
}

const std::string& VObjectKey::ToString() const
{
	return m_strName;
}

//-----------------------------------------------------------------------------
} // namespace v3d

