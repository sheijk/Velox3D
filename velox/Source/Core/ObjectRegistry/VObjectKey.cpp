#include <V3d/Core/VObjectKey.h>
//------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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

