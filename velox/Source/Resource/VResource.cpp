#include <V3d/Resource/VResource.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>

#include <V3d/Core/SmartPtr/VServicePtr.h>

#include "VResourceManager.h"

#include <iostream>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VResource::VResource(const std::string in_strName)
{
	m_strName = in_strName;
}

/**
 * d'tor
 */
VResource::~VResource()
{
}

const std::string& VResource::GetName() const
{
	return m_strName;
}

VResource* VResource::AddSubResource(const std::string& in_strChildName)
{
	if( GetSubResource(in_strChildName) == 0 )
	{
		VSharedPtr<VResource> pNewResource(new VResource(in_strChildName));

		m_SubResources.push_back(pNewResource);

		return pNewResource.Get();
	}
	else
	{
		return 0;
	}
}

VResource* VResource::GetSubResource(const std::string& in_strSubResource)
{
	ResourceContainer::iterator resIter = m_SubResources.begin();
	const ResourceContainer::iterator end = m_SubResources.end();

	for( ; resIter != end; ++resIter)
	{
		std::string currentName = (*resIter)->GetName();
		if( currentName == in_strSubResource )
			return resIter->Get();
	}

	// not found
	return 0;
}

using namespace std;

void VResource::DumpInfo(const std::string& in_strPrefix) const
{
	vout << in_strPrefix << "-> " << GetName() << vendl;

	// print info about data
	for(DataMap::const_iterator data = m_Data.begin();
		data != m_Data.end();
		++data)
	{
		VResourceData* pData = data->second.Get();

		vout << in_strPrefix << "Data of type '";
		vout << typeid(*pData).name() << "'" << vendl;
	}

	// print info about subdirectories    
	for(ResourceContainer::const_iterator child = m_SubResources.begin();
		m_SubResources.end() != child;
		++child)
	{
		(*child)->DumpInfo(in_strPrefix + "  ");
	}
}

VResourceData* VResource::GetData(VResourceData::TypeId in_Type)
{
	// if such data exists, return it
	DataMap::const_iterator data = m_Data.find(in_Type);

	// if data does not exist, try to create it
	if( data == m_Data.end() )
	{
		// get managers for type
		VServicePtr<VResourceManager> pResManager;
		std::vector<IVResourceType*> managers = 
			pResManager->GetResourceTypes(in_Type);

		// for each type: try to create
		std::vector<IVResourceType*>::iterator resType = managers.begin();
		for( ; resType != managers.end(); ++resType)
		{
			// try to generate data
			(*resType)->Generate(this);

			// try to get data again
			data = m_Data.find(in_Type);

			// if data could be generated, break
			if( data != m_Data.end() )
				break;
		}
	}

	if( data != m_Data.end() )
	{
		VResourceData* pUntypedData = data->second.Get();

		return pUntypedData;
	}
	// if it doesn't exist, throw error
	else
	{
		std::stringstream message;
		message << "Could not find data of type '(TODO;)";
		//message << typeid(VTypedResourceData<DataType>).name() << "'";
		message << "' in resource '" << GetName() << "'";

		V3D_THROW(VDataNotFoundException, message.str().c_str());
	}
}

void VResource::AddData(
	VResourceData::TypeId in_Type, VSharedPtr<VResourceData> in_pData)
{
	// if no data of same type exists, yet
	if( m_Data.find(in_Type) == m_Data.end() )
	{
		// store data
		m_Data.insert(DataMap::value_type(in_Type, in_pData));
	}
	// if data already existed, throw exception
	else
	{
		std::stringstream message;
		message << "Could not attach data of type '";
		message << typeid(*in_pData).name();
		message << "' to resource '" << GetName();
		message << " because such data already existed";

		V3D_THROW(VDataAlreadyAttachedException, message.str().c_str());
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
