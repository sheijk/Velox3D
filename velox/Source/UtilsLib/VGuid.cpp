/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3dLib/Utils/VGuid.h>
//-----------------------------------------------------------------------------
#include <V3d/Core.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------

VGuid::VGuid()
{
}

VGuid::~VGuid()
{
}

vbool VGuid::operator ==(const VGuid& in_other) const
{
	return m_iID == in_other.m_iID;
}

vbool VGuid::operator !=(const VGuid& in_other) const
{
	return m_iID != in_other.m_iID;
}

VGuid VGuid::Generate()
{
	m_iID++;

	return *this;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
