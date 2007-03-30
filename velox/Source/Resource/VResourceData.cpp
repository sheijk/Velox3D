/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Resource/VResourceData.h>
//-----------------------------------------------------------------------------

#include <cstring>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d;

VResourceData::VResourceData(VResource* in_pResource)
{
	m_nReferenceCount = 0;
	m_pResource = in_pResource;
}

VResourceData::~VResourceData()
{
}

VResource* VResourceData::GetEnclosingResource()
{
	return m_pResource;
}

const VResource* VResourceData::GetEnclosingResource() const
{
	return m_pResource;
}

vuint VResourceData::GetReferenceCount() const
{
	return m_nReferenceCount;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------

