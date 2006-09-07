/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VResourceManager.h"
//-----------------------------------------------------------------------------
#include <V3d/Utils/VSimpleTokenizer.h>

#include <iostream>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace std;
using utils::VSimpleTokenizer;

/**
 * standard c'tor
 */
VResourceManager::VResourceManager(VStringParam in_strName) :
	IVResourceManager(in_strName),
	m_RootResource("")
{
	m_pRandomRoot = m_RootResource.AddSubResource("=v3d-private=");
}

/**
 * d'tor
 */
VResourceManager::~VResourceManager()
{
}

namespace {
	VResource* CreateSubResource(
		VResource* in_pParent, 
		std::list<std::string>::const_iterator begin,
		std::list<std::string>::const_iterator end
		)
	{
		// there is at least one more sub name
		if( begin != end )
		{
			std::string name = *begin;

			// look if the sub resource already exists
			VResource* pSubResource = in_pParent->GetSubResource(name);

			// if it doesn't, create it
			if( pSubResource == 0 )
			{
				pSubResource = in_pParent->AddSubResource(name);

				if( 0 == pSubResource )
					return 0;
			}

			// continue with rest of the list
			return CreateSubResource(pSubResource, ++begin, end);
		}
		// no more sub names, we are done
		else
		{
			return in_pParent;
		}
	}

	void CheckResourceName(VStringParam in_strName)
	{
		V3D_ASSERT(0 != in_strName);
//		V3D_ASSERT(in_strName[0] == '/');
	}
} // anonymous namespace

VResourceId VResourceManager::CreateResource(VStringParam in_strName)
{
	CheckResourceName(in_strName);

	//cout << sizeof(vfloat64) << endl; //TODO: no need here for this --ins

	// get sub names of name (ignoring the leading '/')
	VSimpleTokenizer tokens(std::string(in_strName+1), '/');

    VResource* pResource = CreateSubResource(
		&m_RootResource, 
		tokens.TokenBegin(), 
		tokens.TokenEnd());

	return VResourceId(pResource);
}

VResourceId VResourceManager::CreateRandomNamedResource(VStringParam in_strUsageHint)
{
	return m_pRandomRoot->AddRandomNamedSubResource(in_strUsageHint);
}

VResourceId VResourceManager::GetResourceByName(VStringParam in_strName)
{
	CheckResourceName(in_strName);

	return VResourceId(m_RootResource.GetResourceByPath(std::string(in_strName)));
}

void VResourceManager::RegisterResourceType(VSharedPtr<IVResourceType> in_pResType)
{
	// add as manager for managed types (ignore those types which already
	// have a type manager
	VRangeIterator<VTypeInfo> managedTypes = in_pResType->ManagedTypes();

	while( managedTypes.HasNext() )
	{
		ManagerMap::iterator managedIter = m_TypeManagers.find(*managedTypes);

		if( managedIter == m_TypeManagers.end() )
		{
			m_TypeManagers[*managedTypes] = in_pResType;
		}
		else
		{
			vout << "Warning: manager for type " << managedTypes->GetName()
				<< " already registered, ignoring second one" << vendl;
		}

		++managedTypes;
	}

	// add to type creators
	VRangeIterator<VTypeInfo> typeIter = in_pResType->CreatedTypes();

	while(typeIter.HasNext())
	{
		m_TypeCreators.insert(CreatorMap::value_type(*typeIter, in_pResType));
		typeIter++;
	}
}

std::vector<IVResourceType*> VResourceManager::GetResourceTypes(VTypeInfo in_Type)
{
	std::vector<IVResourceType*> types;

	CreatorMap::const_iterator iter = m_TypeCreators.begin();
	for( ; iter != m_TypeCreators.end(); ++iter)
	{
		if( iter->first.CanBeCastedTo(in_Type) )
		{
			types.push_back(iter->second.Get());
		}
	}

	//CreatorMap::const_iterator iter = m_TypeCreators.find(in_Type);

	//while(iter != m_TypeCreators.end() && iter->first == in_Type)
	//{
	//	types.push_back(iter->second.Get());
	//	++iter;
	//}

	return types;
}

IVResourceType* VResourceManager::GetResourceManager(const VTypeInfo& in_Type)
{
	ManagerMap::iterator typeIter = m_TypeManagers.find(in_Type);

	if( typeIter == m_TypeManagers.end() )
		return 0;
	else
		return typeIter->second.Get();
}

void VResourceManager::NotifyChange(VResource* in_pResource, VTypeInfo in_Type)
{
	// get a set containing every managed type exactly once
	set<IVResourceType*> uniqueManagers;

	for(ManagerMap::iterator manager = m_TypeManagers.begin();
		manager != m_TypeManagers.end();
		++manager)
	{
		IVResourceType* pCurrent = manager->second.Get();
		uniqueManagers.insert(pCurrent);
	}

	// update them
	for(set<IVResourceType*>::iterator manager = uniqueManagers.begin();
		manager != uniqueManagers.end();
		++manager)
	{
		IVResourceType* pCurrent = *manager;
		pCurrent->NotifyChange(in_Type, in_pResource);
	}
}

void VResourceManager::DumpResourceInfo() const
{
	m_RootResource.DumpInfo("");
}

vbool VResourceManager::ExistsResource(VStringParam in_strName)
{
	// quick and dirty hack..
	try
	{
		VResourceId x(in_strName);
		return true;
	}
	catch(VException&)
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------

