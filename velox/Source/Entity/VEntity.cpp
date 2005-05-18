#include <V3d/Entity/VEntity.h>
//-----------------------------------------------------------------------------

#include <sstream>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VEntity::VEntity()
{
	m_pParent = 0;
	m_bActivated = false;
}

VEntity::~VEntity()
{
	// delete all parts
	for(
		PartContainer::iterator part = m_Parts.begin();
		part != m_Parts.end();
		++part)
	{
		part->second.Release();
	}
}

void VEntity::Activate()
{
	V3D_ASSERT(m_bActivated == false);

	// activate all parts
	for(
		PartContainer::iterator part = m_Parts.begin();
		part != m_Parts.end();
		++part)
	{
		part->second->Activate();
	}

	// activate all childs
	for(EntityContainer::iterator child = m_Entities.begin();
		child != m_Entities.end();
		++child)
	{
		(*child)->Activate();
	}

	m_bActivated = true;
}

void VEntity::Deactivate()
{
	V3D_ASSERT(m_bActivated == true);

	// deactivate all childs
	for(EntityContainer::iterator child = m_Entities.begin();
		child != m_Entities.end();
		++child)
	{
		(*child)->Deactivate();
	}

	// deactivate all parts
	for(
		PartContainer::iterator part = m_Parts.begin();
		part != m_Parts.end();
		++part)
	{
		part->second->Deactivate();
	}

	m_bActivated = false;
}

void VEntity::AddPart(const utils::VFourCC& in_Id, PartPtr in_pPart)
{
	// if part is not contained, yet
	if( m_Parts.find(in_Id) == m_Parts.end() )
	{
		// tell all parts about new part		 
		// tell part about all other parts
		for(
			PartContainer::iterator part = m_Parts.begin();
			part != m_Parts.end();
			++part)
		{
			part->second->TellNeighbourPart(in_Id, *in_pPart);
			in_pPart->TellNeighbourPart(part->first, *(part->second));
		}

		// find closest parent with same id
		VEntity* parent = m_pParent;
		while( parent != 0 )
		{
			// check whether the entity contains a part with the given id
			PartContainer::iterator part = parent->m_Parts.find(in_Id);
			if( part != parent->m_Parts.end() )
			{
				in_pPart->TellParentPart(in_Id, *(part->second));
				break;
			}

			parent = parent->m_pParent;
		}

		// add part to list
		m_Parts[in_Id] = in_pPart;
	}
	else
	{
		std::stringstream message;
		message << "Could not insert part because a part with name '";
		message << in_Id.AsStdString() << "' already exists in entity\n";
		V3D_THROW(VPartAlreadyPresentException, message.str().c_str());
	}
}

void VEntity::AddChild(EntityPtr in_pEntity)
{
	V3D_ASSERT(in_pEntity.Get() != 0);
	V3D_ASSERT(in_pEntity.Get() != this);
	V3D_ASSERT(in_pEntity->m_bActivated == false);

	m_Entities.push_back(in_pEntity);
	in_pEntity->m_pParent = this;
}

void VEntity::RemoveChild(EntityPtr in_pEntity)
{
	V3D_ASSERT(in_pEntity.Get() != 0);
	V3D_ASSERT(in_pEntity->m_bActivated == false);

	EntityContainer::iterator ent = 
		std::find(m_Entities.begin(), m_Entities.end(), in_pEntity);

	m_Entities.erase(ent);
	in_pEntity->m_pParent = 0;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
