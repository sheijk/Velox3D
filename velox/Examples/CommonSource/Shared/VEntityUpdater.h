#ifndef V3D_VENTITYUPDATER_2004_10_12_H
#define V3D_VENTITYUPDATER_2004_10_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <list>
#include <algorithm>
//-----------------------------------------------------------------------------
namespace v3d { namespace racer {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * A generic manager for updating entity parts. Use it as a base class for
 * all systems which need to update entity parts on a regular basis
 *
 * @author sheijk
 */
template<typename EntityType>
class VEntityUpdater
{
	typedef std::list<EntityType*> EntityList;

	EntityList m_Subjects;

public:
	/** Adds the entity part to the update list */
	void Add(EntityType* in_pEntity);
	/** Remove the entity part from the update list */
	void Remove(EntityType* in_pEntity);

	/** Calls part.Update() for each part in the update list */
	void UpdateAll();
};

//-----------------------------------------------------------------------------

template<typename EntityType>
void VEntityUpdater<EntityType>::UpdateAll()
{
	for(EntityList::iterator ent = m_Subjects.begin(); ent != m_Subjects.end(); ++ent)
	{
		(*ent)->Update();
	}
}

template<typename EntityType>
void VEntityUpdater<EntityType>::Add(EntityType* in_pEntity)
{
	m_Subjects.push_back(in_pEntity);
}

template<typename EntityType>
void VEntityUpdater<EntityType>::Remove(EntityType* in_pEntity)
{
	EntityList::iterator ent = std::find(m_Subjects.begin(), m_Subjects.end(), in_pEntity);
	m_Subjects.erase(ent);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::racer
//-----------------------------------------------------------------------------
#endif // V3D_VENTITYUPDATER_2004_10_12_H
