#include "VObjectKey.h"
//------------------------------------------------------------------------

VObjectKey::VObjectKey()
{
}

VObjectKey::VObjectKey(const std::string &in_strName)
{
	m_strName = in_strName;
}

VObjectKey::~VObjectKey()
{
}

const std::string& VObjectKey::toString() const
{
	return m_strName;
}



