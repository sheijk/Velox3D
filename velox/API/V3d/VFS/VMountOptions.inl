/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

inline const VString& VMountOptions::GetName() const
{
	return m_strName;
}

inline const VString& VMountOptions::GetType() const
{
	return m_strType;
}

inline const VString& VMountOptions::GetOptions() const
{
	return m_strOptions;
}

inline const VString& VMountOptions::GetSource() const
{
	return m_strSource;
}

inline const VMountOptions::AccessRightsPtr VMountOptions
	::GetAccessRights() const
{
	return m_pAccessRights;
}
