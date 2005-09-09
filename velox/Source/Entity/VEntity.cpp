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
	vbool DependsOnNeighbour(IVPart& in_Part, const std::string& in_Id)
	{
		for(vuint dep = 0; dep < in_Part.DependencyCount(); ++dep)
		{
			if( in_Part.GetDependencyInfo(dep).location == VPartDependency::Neighbour &&
				in_Part.GetDependencyInfo(dep).id == in_Id )
				return true;
		}

		return false;
	}

	vbool DependsOnAncestor(IVPart& in_Part, const std::string& in_Id)
	{
		for(vuint dep = 0; dep < in_Part.DependencyCount(); ++dep)
		{
			if( in_Part.GetDependencyInfo(dep).location == VPartDependency::Ancestor &&
				in_Part.GetDependencyInfo(dep).id == in_Id )
				return true;
		}

		return false;
	}
}

class VEntityHelper
{
	friend ::v3d::entity::VEntity;

	static IVPart* FindAncestorWithId(VEntity* in_pStart, const std::string& in_Id)
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
		VEntity* in_pAncestorPos, const std::string& in_AncestorId)
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
		VEntity* in_pEntity, const std::string& in_AncestorId)
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

IVPart* VEntity::GetPartById(const std::string& in_Id)
{
	PartContainer::iterator part = m_Parts.begin();
	for( ; part != m_Parts.end(); ++part)
	{
		if( part->first == in_Id )
			return part->second.Get();
	}

	return 0;
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
		ConnectPart(part->second.Get(), part->first);
	}

	EntityContainer::iterator child = m_Entities.begin();
	for( ; child != m_Entities.end(); ++child)
	{
		(*child)->ReconnectAllParts();
	}
}

void VEntity::UnconnectAllParts()
{
	PartContainer::iterator part = m_Parts.begin();
	for( ; part != m_Parts.end(); ++part)
	{
		UnconnectPart(part->second.Get(), part->first);
	}

	EntityContainer::iterator child = m_Entities.begin();
	for( ; child != m_Entities.end(); ++child)
	{
		(*child)->UnconnectAllParts();
	}
}

void VEntity::ConnectPart(IVPart* in_pPart, const std::string& in_Id)
{
	// connect all part to neighbours and neighbours to part if needed
	for(
		PartContainer::iterator part = m_Parts.begin();
		part != m_Parts.end();
	++part)
	{
		// connect neighbour to part
		if( DependsOnNeighbour(*(part->second), in_Id) )
			part->second->Connect(VPartDependency::Neighbour, in_Id, *in_pPart);

		// connect part to neighbour
		if( DependsOnNeighbour(*in_pPart, part->first) )
			in_pPart->Connect(VPartDependency::Neighbour, part->first, *(part->second));
	}

	// connect part to all ancestors it needs
	for(vuint dep = 0; dep < in_pPart->DependencyCount(); ++dep)
	{
		IVPart::Dependency dependency = in_pPart->GetDependencyInfo(dep);

		if( dependency.location == VPartDependency::Ancestor )
		{
			IVPart* pAncestor = 
				VEntityHelper::FindAncestorWithId(this, dependency.id);

			if( pAncestor != 0 )
			{
				in_pPart->Connect(VPartDependency::Ancestor, dependency.id, *pAncestor);
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
				VPartDependency::Ancestor, in_Id, *ancestorOfSameType);
		}

		dependentParts[partNum]->Connect(VPartDependency::Ancestor, in_Id, *in_pPart);
	}
}

void VEntity::UnconnectPart(IVPart* in_pPart, const std::string& in_Id)
{
	V3D_ASSERT(in_pPart != 0);

	// unconnect from all neighbours
	for(PartContainer::iterator part = m_Parts.begin(); part != m_Parts.end(); ++part)
	{
		if( DependsOnNeighbour(*in_pPart, part->first) )
			in_pPart->Disconnect(VPartDependency::Neighbour, part->first, *part->second);

		if( DependsOnNeighbour(*part->second, in_Id) )
			part->second->Disconnect(VPartDependency::Neighbour, in_Id, *in_pPart);
	}

	// unconnect from all ancestors
	for(vuint depNum = 0; depNum < in_pPart->DependencyCount(); ++depNum)
	{
		IVPart::Dependency& dependency(in_pPart->GetDependencyInfo(depNum));

		if( dependency.location == VPartDependency::Ancestor )
		{
			IVPart* pAncestor = VEntityHelper::FindAncestorWithId(this, dependency.id);

			if( pAncestor != 0 )
				in_pPart->Disconnect(VPartDependency::Ancestor, dependency.id, *pAncestor);
		}
	}

	// find all parts which have in_pPart as ancestor and unconnect them
	std::vector<IVPart*> dependentParts = 
		VEntityHelper::FindPartsWhichNeedAncestor(this, in_Id);

	for(vuint partNum = 0; partNum < dependentParts.size(); ++partNum)
	{
		IVPart& part(*dependentParts[partNum]);

		part.Disconnect(VPartDependency::Ancestor, in_Id, *in_pPart);
	}
}

void VEntity::CheckDependencies()
{
	vbool deactivate = false;

	if( IsActive() )
	{
		// check if all parts are ready (have all required connections)
		for(PartContainer::iterator part = m_Parts.begin(); 
			part != m_Parts.end(); ++part)
		{
			// deactivate if unmatched requirements
			if( ! part->second->IsReady() )
				deactivate = true;
		}
	}

	if( deactivate )
	{
		Deactivate();
	}
	else
	{
		EntityContainer::iterator child = m_Entities.begin();
		for( ; child != m_Entities.end(); ++child)
		{
			(*child)->CheckDependencies();
		}
	}
}

void VEntity::AddPart(const std::string& in_Id, PartPtr in_pPart)
{
	// if part is not contained, yet
	if( in_pPart.Get() != 0 && m_Parts.find(in_Id) == m_Parts.end() )
	{
		ConnectPart(in_pPart.Get(), in_Id);

		// add part to list
		m_Parts[in_Id] = in_pPart;
	}
	else
	{
		std::stringstream message;
		message << "Could not insert part because a part with name '";
		message << in_Id << "' already exists in entity\n";
		V3D_THROW(VPartAlreadyPresentException, message.str().c_str());
	}
}

void VEntity::RemovePart(const std::string& in_Id)
{
	// get part
	IVPart* pPart = GetPartById(in_Id);

	// unconnect it
	UnconnectPart(pPart, in_Id);

	// remove it
	m_Parts.erase(in_Id);

	// check if entity needs to deactivate
	CheckDependencies();
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

	if( (*ent)->IsActive() )
		(*ent)->Deactivate();

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
