#include <V3d/Entity/VEntityManager.h>
//-----------------------------------------------------------------------------

#include <algorithm>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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
