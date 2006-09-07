/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Tags/VTagRegistry.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace tags {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VTagRegistry::VTagRegistry() :
	VNamedObject("tag.registry", 0)
{
	m_nLastId = 0;
}

/**
 * d'tor
 */
VTagRegistry::~VTagRegistry()
{
}

VTag& VTagRegistry::GetTagWithName(const std::string& name)
{
	for(TagSet::iterator tagIter = m_Tags.begin();
		tagIter != m_Tags.end();
		++tagIter)
	{
		if( (*tagIter)->GetName() == name )
			return *tagIter->Get();
	}

	m_nLastId++;

	VSharedPtr<VTag> pNewTag(new VTag(name, m_nLastId));
	m_Tags.push_back(pNewTag);
	return *pNewTag;
}

vbool VTagRegistry::ExistsTagWithName(const std::string& name)
{
	for(TagSet::iterator tagIter = m_Tags.begin();
		tagIter != m_Tags.end();
		++tagIter)
	{
		if( (*tagIter)->GetName() == name )
			return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::tags
//-----------------------------------------------------------------------------

