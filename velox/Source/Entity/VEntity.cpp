/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
	/** Returns true if in_Part depends on a part with id in_Id and
	 * type in_Type 
	 */
	vbool DependsOnNeighbour(
		IVPart& in_Part, const std::string& in_Id, const VTypeInfo& in_Type)
	{
		for(vuint dep = 0; dep < in_Part.DependencyCount(); ++dep)
		{
			const VPartDependency& dependency(in_Part.GetDependencyInfo(dep));

			vbool depends = true;

			if( dependency.GetId() != "" )
				depends &= dependency.GetId() == in_Id;

			depends &= dependency.GetLocation() == VPartDependency::Neighbour;
			depends &= in_Type.CanBeCastedTo(dependency.GetTypeInfo());

			if( depends )
				return true;
		}

		return false;
	}

	/** Returns true if in_Part depends on a part with id in_Id and
	* type in_Type 
	*/
	vbool DependsOnAncestor(
		IVPart& in_Part, const std::string& in_Id, const VTypeInfo& in_Type)
	{
		for(vuint dep = 0; dep < in_Part.DependencyCount(); ++dep)
		{
			const VPartDependency& dependency(in_Part.GetDependencyInfo(dep));

			vbool depends = true;

			if( dependency.GetId() != "" )
				depends &= dependency.GetId() == in_Id;

			depends &= dependency.GetLocation() == VPartDependency::Ancestor;
			depends &= in_Type.CanBeCastedTo(dependency.GetTypeInfo());

			if( depends )
				return true;
		}

		return false;
	}
}

class VEntityHelper
{
	friend ::v3d::entity::VEntity;

	static IVPart* FindAncestorWithId(VEntity* in_pStart, 
		const std::string& in_Id, const VTypeInfo& in_TypeInfo)
	{
		VEntity* pEntity = in_pStart->m_pParent;

		for( ; pEntity != 0; pEntity = pEntity->m_pParent)
		{
			VEntity::PartContainer::iterator part = pEntity->m_Parts.begin();
			for( ; part != pEntity->m_Parts.end(); ++part)
			{
				vbool found = true;

				if( in_Id != "" )
					found &= part->first == in_Id;

				found &= part->second->GetTypeInfo().CanBeCastedTo(in_TypeInfo);

				if( found )
					return part->second.Get();
			}
		}

		// nothing found
		return 0;
	}

	static std::vector<IVPart*> FindPartsWhichNeedAncestor(
		VEntity* in_pAncestorPos, const std::string& in_AncestorId, 
		const VTypeInfo& in_AncestorTypeInfo)
	{
		std::vector<IVPart*> dependentParts;

		VEntity::EntityContainer::iterator child = in_pAncestorPos->m_Entities.begin();
		for( ; child != in_pAncestorPos->m_Entities.end(); ++child)
		{
			AddPartsWhichNeedAncestor(dependentParts, child->Get(), 
				in_AncestorId, in_AncestorTypeInfo);
		}

		return dependentParts;
	}

	static void AddPartsWhichNeedAncestor(
		std::vector<IVPart*>& io_DependentParts,
		VEntity* in_pEntity, 
		const std::string& in_AncestorId,
		const VTypeInfo& in_AncestorTypeInfo)
	{
		// add all parts if they depend on the given ancestor
		VEntity::PartContainer::iterator partIter = in_pEntity->m_Parts.begin();
		for( ; partIter != in_pEntity->m_Parts.end(); ++partIter)
		{
			if( DependsOnAncestor(*partIter->second, in_AncestorId, in_AncestorTypeInfo) )
			{
				io_DependentParts.push_back(partIter->second.Get());
			}
		}

		// add dependent parts of all childs
		VEntity::EntityContainer::iterator child = in_pEntity->m_Entities.begin();
		for( ; child != in_pEntity->m_Entities.end(); ++child)
		{
			AddPartsWhichNeedAncestor(io_DependentParts, child->Get(), 
				in_AncestorId, in_AncestorTypeInfo);
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

 	m_Parts.clear();

	for(EntityContainer::iterator child = m_Entities.begin();
		child != m_Entities.end();
		++child)
	{
		child->Release();
	}

	m_Entities.clear();

	
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

void VEntity::SetAllPartsActive(vbool in_bActive)
{
	for(
		PartContainer::iterator part = m_Parts.begin();
		part != m_Parts.end();
	++part)
	{
		if( in_bActive )
			part->second->Activate();
		else
			part->second->Deactivate();
	}
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
			VSharedPtr<IVPart> pPart = part->second;

			if( ! pPart->IsReady() )
				return;
		}

		// activate all parts
		SetAllPartsActive(true);

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
		SetAllPartsActive(false);
	
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
	//// connect all part to neighbours and neighbours to part if needed
	//for(
	//	PartContainer::iterator part = m_Parts.begin();
	//	part != m_Parts.end();
	//++part)
	//{
	//	// connect neighbour to part
	//	if( DependsOnNeighbour(*(part->second), in_Id, in_pPart->GetTypeInfo()) )
	//		part->second->Connect(VPartDependency::Neighbour, in_Id, *in_pPart);

	//	// connect part to neighbour
	//	if( DependsOnNeighbour(*in_pPart, part->first, part->second->GetTypeInfo()) )
	//		in_pPart->Connect(VPartDependency::Neighbour, part->first, *(part->second));
	//}

	// establish all part connections
	for(vuint dep = 0; dep < in_pPart->DependencyCount(); ++dep)
	{
		IVPart::Dependency dependency = in_pPart->GetDependencyInfo(dep);

		if( dependency.location == VPartDependency::Ancestor )
		{
			IVPart* pAncestor = VEntityHelper::FindAncestorWithId(
				this, dependency.id, dependency.GetTypeInfo());

			if( pAncestor != 0 )
			{
				in_pPart->Connect(VPartDependency::Ancestor, dependency.id, *pAncestor);
			}
		}
		else if( dependency.location == VPartDependency::Neighbour )
		{
			// find matching part
			for(
				PartContainer::iterator part = m_Parts.begin();
				part != m_Parts.end();
				++part)
			{
				if( DependsOnNeighbour(*in_pPart, 
					part->first, part->second->GetTypeInfo()) )
				{
					in_pPart->Connect(VPartDependency::Neighbour,
						dependency.id, *part->second);
				}
			}
		}
	}
}

void VEntity::UnconnectPart(IVPart* in_pPart, const std::string& in_Id)
{
	V3D_ASSERT(in_pPart != 0);

	// unconnect from all neighbours
	for(PartContainer::iterator part = m_Parts.begin(); part != m_Parts.end(); ++part)
	{
		if( DependsOnNeighbour(*in_pPart, part->first, part->second->GetTypeInfo()) )
			in_pPart->Disconnect(VPartDependency::Neighbour, part->first, *part->second);

		//if( DependsOnNeighbour(*part->second, in_Id, in_pPart->GetTypeInfo()) )
		//	part->second->Disconnect(VPartDependency::Neighbour, in_Id, *in_pPart);
	}

	// unconnect from all ancestors
	for(vuint depNum = 0; depNum < in_pPart->DependencyCount(); ++depNum)
	{
		IVPart::Dependency& dependency(in_pPart->GetDependencyInfo(depNum));

		if( dependency.location == VPartDependency::Ancestor )
		{
			IVPart* pAncestor = VEntityHelper::FindAncestorWithId(
				this, dependency.id, dependency.GetTypeInfo());

			if( pAncestor != 0 )
				in_pPart->Disconnect(VPartDependency::Ancestor, dependency.id, *pAncestor);
		}
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
		// check dependencies for all childs
		EntityContainer::iterator child = m_Entities.begin();
		for( ; child != m_Entities.end(); ++child)
		{
			(*child)->CheckDependencies();
		}
	}
}

void VEntity::AddPart(VSharedPtr<IVPart> in_pPart)
{
	if( in_pPart.Get() != 0 ) 
	{
		AddPart(in_pPart->GetTypeInfo().GetName(), in_pPart);
	}
}

void VEntity::AddPart(const std::string& in_Id, PartPtr in_pPart)
{
	// if part is not contained, yet
	if( in_pPart.Get() != 0 && m_Parts.find(in_Id) == m_Parts.end() )
	//if( in_pPart.Get() != 0 )
	{
		if( m_bActivated )
			SetAllPartsActive(false);

		UnconnectAllParts();

		// add part to list
		m_Parts.insert(make_pair(in_Id, in_pPart));
		//m_Parts[in_Id] = in_pPart;

		ReconnectAllParts();

		if( m_bActivated )
			SetAllPartsActive(true);
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
	const vbool wasActive = IsActive();

	if( wasActive )
		Deactivate();

	UnconnectAllParts();

	// get part
	IVPart* pPart = GetPartById(in_Id);

	// remove it
	m_Parts.erase(in_Id);

	ReconnectAllParts();

	if( wasActive )
		Activate();

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

	in_pEntity->UnconnectAllParts();

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

VRangeIterator<const VEntity> VEntity::ChildIterator() const
{
	return CreateDerefBeginIterator<const VEntity>(m_Entities);
}

VRangeIterator<IVPart> VEntity::PartIterator()
{
	return CreateAccesssorIterator<
		VPair2ndDerefAccessor, IVPart, PartContainer::iterator>(
		m_Parts.begin(), m_Parts.end());
}

VRangeIterator<const IVPart> VEntity::PartIterator() const
{
	return CreateAccesssorIterator<
		VPair2ndDerefAccessor, const IVPart, PartContainer::const_iterator>(
		m_Parts.begin(), m_Parts.end());
}

VSharedPtr<VEntity> VEntity::GetChildWithName(const std::string& in_strName)
{
	for(EntityContainer::iterator childIter = m_Entities.begin();
		childIter != m_Entities.end();
		++childIter)
	{
		if( (*childIter)->GetName() == in_strName )
			return *childIter;
	}

	return VSharedPtr<VEntity>(0);
}

std::string VEntity::GetName() const
{
	return m_strName;
}

void VEntity::SetName(const std::string& in_TrName)
{
	m_strName = in_TrName;
}

void PrintPartSettings(const IVPart& in_Part, const std::string& prefix)
{
	using messaging::VMessage;

	IVPart& part = const_cast<IVPart&>(in_Part);

	VMessage request;
	request.AddProperty("type", "getSettings");
	VMessage answer;

	part.Send(request, &answer);

	VRangeIterator<const std::string> propertyIter = answer.PropertyIterator();
	while( propertyIter.HasNext() )
	{
		vout << prefix 
			<< *propertyIter 
			<< " = " 
			<< answer.GetAs<std::string>(*propertyIter) 
			<< vendl;
		++propertyIter;
	}
}

void VEntity::DumpInfo(const std::string& prefix) const
{
	if( this != 0 ) 
	{
		const std::string indent = ".\t";

		vout
			<< (IsActive() ? "" : "!")
			<< prefix
			<< "Entity \"" << GetName() << "\""
			<< (IsActive() ? "" : " (inactive)")
			<< vendl;

		VRangeIterator<const IVPart> partIter = PartIterator();
		while( partIter.HasNext() )
		{
			vout 
				<< prefix 
				<< indent << "Part " 
				<< partIter->GetTypeInfo().GetName()
				<< (partIter->IsReady() ? "" : " (unresolved dependencies)") 
				<< vendl;

			PrintPartSettings(*partIter, prefix + indent + indent);

			++partIter;
		}

		VRangeIterator<const VEntity> childIter = ChildIterator();
		while( childIter.HasNext() )
		{
			childIter->DumpInfo(prefix + indent);
			++childIter;
		}
	}
	else
	{
		vout << prefix << "Entity.this = 0";
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------


