#include <v3d/Core/VObjectKey.h>
//------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VObjectKey::VObjectKey()
{
}

VObjectKey::VObjectKey(VStringParam in_pcName)
{
	m_strName = in_pcName;
}

VObjectKey::~VObjectKey()
{
}

VStringRetVal VObjectKey::ToString() const
{
	return m_strName.AsCString();
}

//-----------------------------------------------------------------------------
} // namespace v3d

