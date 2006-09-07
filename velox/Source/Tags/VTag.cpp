/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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

