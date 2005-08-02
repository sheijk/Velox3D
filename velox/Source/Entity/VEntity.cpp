#include <V3d/Entity/VEntity.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>

#include <V3d/Core/RangeIter/VSTLAccessorRangePolicy.h>

#include <sstream>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::utils;

namespace {
	vbool DependsOnNeighbour(IVPart& in_Part, VFourCC in_Id)
	{
		for(vuint dep = 0; dep < in_Part.DependencyCount(); ++dep)
		{
			if( in_Part.GetDependencyInfo(dep).location == IVPart::Neighbour &&
				in_Part.GetDependencyInfo(dep).id == in_Id )
				return true;
		}

		return false;
	}

	vbool DependsOnAncestor(IVPart& in_Part, VFourCC in_Id)
	{
		for(vuint dep = 0; dep < in_Part.DependencyCount(); ++dep)
		{
			if( in_Part.GetDependencyInfo(dep).location == IVPart::Ancestor &&
				in_Part.GetDependencyInfo(dep).id == in_Id )
				return true;
		}

		return false;
	}
}

class VEntityHelper
{
	friend ::v3d::entity::VEntity;

	static IVPart* FindAncestorWithId(VEntity* in_pStart, VFourCC in_Id)
	{
		VEntity* pEntity = in_pStart->m_pParent;

		for( ; pEntity != 0; pEntity = pEntity->m_pParent)
		{
			VEntity::PartContainer::iterator part = pEntity->m_Parts.begin();
			for( ; part != pEntity->m_Parts.end(); ++part)
			{
				if( part->first == in_Id )
					return part->second.Get();
			}
		}

		// nothing found
		return 0;
	}

	static std::vector<IVPart*> FindPartsWhichNeedAncestor(
		VEntity* in_pAncestorPos, VFourCC in_AncestorId)
	{
		std::vector<IVPart*> dependentParts;

		VEntity::EntityContainer::iterator child = in_pAncestorPos->m_Entities.begin();
		for( ; child != in_pAncestorPos->m_Entities.end(); ++child)
		{
			AddPartsWhichNeedAncestor(dependentParts, child->Get(), in_AncestorId);
		}

		return dependentParts;
	}

	static void AddPartsWhichNeedAncestor(std::vector<IVPart*>& io_DependentParts,
		VEntity* in_pEntity, VFourCC in_AncestorId)
	{
		// add all parts if they depend on the given ancestor
		VEntity::PartContainer::iterator partIter = in_pEntity->m_Parts.begin();
		for( ; partIter != in_pEntity->m_Parts.end(); ++partIter)
		{
            if( DependsOnAncestor(*partIter->second, in_AncestorId) )
			{
				io_DependentParts.push_back(partIter->second.Get());
			}
		}

		// add dependent parts of all childs
		VEntity::EntityContainer::iterator child = in_pEntity->m_Entities.begin();
		for( ; child != in_pEntity->m_Entities.end(); ++child)
		{
			AddPartsWhichNeedAncestor(io_DependentParts, child->Get(), in_AncestorId);
		}
	}
};

//int g_nEntityCount = 0;

VEntity::VEntity()
{
	m_pParent = 0;
	m_bActivated = false;
	
//	++g_nEntityCount;
//	vout << g_nEntityCount << " entities existing" << vendl;
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
	
//	--g_nEntityCount;
//	vout << g_nEntityCount << " entities remaining" << vendl;
}

void VEntity::Activate()
{
	if( ! m_bActivated )
	{
		// check if all parts are fine, and do not activate if a part is not
		// ready for use
		for(
			PartContainer::iterator part = m_Parts.begin();
			part != m_Parts.end();
			++part)
		{
			if( ! part->second->IsReady() )
				return;
		}

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
}

void VEntity::Deactivate()
{
	if( m_bActivated )
	{
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
}

vbool VEntity::IsActive() const
{
	return m_bActivated;
}

void VEntity::ReconnectAllParts()
{
	PartContainer::iterator part = m_Parts.begin();
	for( ; part != m_Parts.end(); ++part)
	{
		ConnectPart(part->second, part->first);
	}

	EntityContainer::iterator child = m_Entities.begin();
	for( ; child != m_Entities.end(); ++child)
	{
		(*child)->ReconnectAllParts();
	}
}

void VEntity::ConnectPart(PartPtr in_pPart, utils::VFourCC in_Id)
{
	// connect all part to neighbours and neighbours to part if needed
	for(
		PartContainer::iterator part = m_Parts.begin();
		part != m_Parts.end();
	++part)
	{
		// connect neighbour to part
		if( DependsOnNeighbour(*(part->second), in_Id) )
			part->second->Connect(IVPart::Neighbour, in_Id, *in_pPart);

		// connect part to neighbour
		if( DependsOnNeighbour(*in_pPart, part->first) )
			in_pPart->Connect(IVPart::Neighbour, part->first, *(part->second));
	}

	// connect part to all ancestors it needs
	for(vuint dep = 0; dep < in_pPart->DependencyCount(); ++dep)
	{
		IVPart::Dependency dependency = in_pPart->GetDependencyInfo(dep);

		if( dependency.location == IVPart::Ancestor )
		{
			IVPart* pAncestor = 
				VEntityHelper::FindAncestorWithId(this, dependency.id);

			if( pAncestor != 0 )
			{
				in_pPart->Connect(IVPart::Ancestor, dependency.id, *pAncestor);
			}
		}
	}


	// reconnect "child" parts which are connected to an ancestor of
	// the same type like the new one
	IVPart* ancestorOfSameType = VEntityHelper::FindAncestorWithId(this, in_Id);

	// find all parts which depend on the ancestor, disconnect them
	std::vector<IVPart*> dependentParts = 
		VEntityHelper::FindPartsWhichNeedAncestor(this, in_Id);

	// from it and reconnect them to new part
	for(vuint partNum = 0; partNum < dependentParts.size(); ++partNum)
	{
		if( ancestorOfSameType != 0 )
		{
			dependentParts[partNum]->Disconnect(
				IVPart::Ancestor, in_Id, *ancestorOfSameType);
		}

		dependentParts[partNum]->Connect(IVPart::Ancestor, in_Id, *in_pPart);
	}
}

void VEntity::AddPart(const utils::VFourCC& in_Id, PartPtr in_pPart)
{
	// if part is not contained, yet
	if( m_Parts.find(in_Id) == m_Parts.end() )
	{
		ConnectPart(in_pPart, in_Id);

		//// find closest parent with same id
		//VEntity* parent = m_pParent;
		//while( parent != 0 )
		//{
		//	// check whether the entity contains a part with the given id
		//	PartContainer::iterator part = parent->m_Parts.find(in_Id);
		//	if( part != parent->m_Parts.end() )
		//	{
		//		in_pPart->Connect(IVPart::Ancestor, in_Id, *(part->second));
		//		//in_pPart->TellParentPart(in_Id, *(part->second));
		//		break;
		//	}

		//	parent = parent->m_pParent;
		//}

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

	in_pEntity->ReconnectAllParts();
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

VRangeIterator<VEntity> VEntity::ChildIterator()
{
	return CreateDerefBeginIterator<VEntity>(m_Entities);
}

VRangeIterator<IVPart> VEntity::PartIterator()
{
	return CreateAccesssorIterator<
		VPair2ndDerefAccessor, IVPart, PartContainer::iterator>(
		m_Parts.begin(), m_Parts.end());
}


//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
