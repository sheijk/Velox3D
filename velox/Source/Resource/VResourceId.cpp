/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Resource/VResourceId.h>
//-----------------------------------------------------------------------------

#include <V3d/Resource/IVResourceManager.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VResourceId::VResourceId(VStringParam in_pResName) :
	m_pResource(VResourceManagerPtr()->GetResourceByName(in_pResName).m_pResource)
{
	;
}

VResourceId::VResourceId(VResource* in_pResource) :
	m_pResource(in_pResource)
{
}

VResource* VResourceId::operator->()
{
	return m_pResource;
}

VResource& VResourceId::operator*()
{
	return *m_pResource;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------

