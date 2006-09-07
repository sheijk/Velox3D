/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Core/VObjectKey.h>
//------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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


