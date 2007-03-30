/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Entity/VEntityManager.h>
//-----------------------------------------------------------------------------

#include <algorithm>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VEntityManager::VEntityManager() : VNamedObject("entity.manager", 0)
{
}

VEntityManager::~VEntityManager()
{
}

void VEntityManager::Add(EntityPtr in_pEntity)
{
	V3D_ASSERT(in_pEntity.Get() != 0);

	m_Entities.push_back(in_pEntity);
}

void VEntityManager::Remove(EntityPtr in_pEntity)
{
	EntityContainer::iterator ent = 
		std::find(m_Entities.begin(), m_Entities.end(), in_pEntity);

	m_Entities.erase(ent);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

