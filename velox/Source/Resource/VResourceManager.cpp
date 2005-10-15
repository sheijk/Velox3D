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

VResourceId VResourceManager::GetResourceByName(VStringParam in_strName)
{
	CheckResourceName(in_strName);

	return VResourceId(m_RootResource.GetResourceByPath(std::string(in_strName)));
}

void VResourceManager::RegisterResourceType(VSharedPtr<IVResourceType> in_pResType)
{
	VRangeIterator<VTypeInfo> typeIter = in_pResType->CreatedTypes();

	while(typeIter.HasNext())
	{
		m_ManagedTypes.insert(TypeMap::value_type(*typeIter, in_pResType));
		typeIter++;
	}
}

std::vector<IVResourceType*> VResourceManager::GetResourceTypes(VTypeInfo in_Type)
{
	std::vector<IVResourceType*> types;

	TypeMap::const_iterator iter = m_ManagedTypes.begin();
	for( ; iter != m_ManagedTypes.end(); ++iter)
	{
		if( iter->first.CanBeCastedTo(in_Type) )
		{
			types.push_back(iter->second.Get());
		}
	}

	//TypeMap::const_iterator iter = m_ManagedTypes.find(in_Type);

	//while(iter != m_ManagedTypes.end() && iter->first == in_Type)
	//{
	//	types.push_back(iter->second.Get());
	//	++iter;
	//}

	return types;
}

void VResourceManager::DumpResourceInfo() const
{
	m_RootResource.DumpInfo("");
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
