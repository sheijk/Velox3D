#include <V3d/Resource/VResource.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>

#include <V3d/Core/SmartPtr/VServicePtr.h>
#include <V3d/Utils/VSimpleTokenizer.h>

#include <V3d/VFS/IVFileSystem.h>

#include "VResourceManager.h"

#include <iostream>
#include <list>
#include <sstream>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using utils::VSimpleTokenizer;

/**
 * standard c'tor
 */
VResource::VResource(const std::string in_strName, VResource* in_pParent)
{
	m_strName = in_strName;
	m_pParent = in_pParent;
}

/**
 * d'tor
 */
VResource::~VResource()
{
}

std::string VResource::GetQualifiedName() const
{
	std::string qualifiedName;
	const VResource* pCurrent = this;

	// add names of all self and all parents
	do
	{
		qualifiedName = "/" + pCurrent->m_strName + qualifiedName;

		pCurrent = pCurrent->GetParent();
	}
	// exit, when pCurrent is a direct child of root 
	// (= when it has no grandparent)
	while( pCurrent != 0 && pCurrent->GetParent() != 0 );

	// return qualified name
	return qualifiedName;
}

std::string VResource::GetName() const
{
	return m_strName;
}

void VResource::SetParent(VResource* in_pParent)
{
	m_pParent = in_pParent;
}

const VResource* VResource::GetParent() const
{
	return m_pParent;
}

VResource* VResource::GetParent()
{
	return m_pParent;
}

VResource* VResource::GetRootResource()
{
	VResource* pCurrent = this;

	while( pCurrent->GetParent() != 0 )
	{
		pCurrent = pCurrent->GetParent();
	}
	
	return pCurrent;
}

VResource* VResource::AddSubResource(const std::string& in_strChildName)
{
	// if the given sub resource does not exist, yet
	if( GetSubResource(in_strChildName) == 0 )
	{
		// create it and add it to sub resource list
		VSharedPtr<VResource> pNewResource(new VResource(in_strChildName, this));

		m_SubResources.push_back(pNewResource);

		return pNewResource.Get();
	}
	else
	{
		return GetSubResource(in_strChildName);
	}
}

VResource* VResource::AddRandomNamedSubResource()
{
	// get an unused name
	std::stringstream name;

	vuint id = 0;

	do
	{
		name.clear();
		name << "res" << id;
	}
	while( GetSubResource(name.str()) != 0 );

	// add sub resource
	return AddSubResource(name.str());
}

VResource* VResource::GetSubResource(const std::string& in_strSubResource)
{
	// look in loaded sub resources, return if matching sub res found
	ResourceContainer::iterator resIter = m_SubResources.begin();
	const ResourceContainer::iterator end = m_SubResources.end();

	for( ; resIter != end; ++resIter)
	{
		std::string currentName = (*resIter)->GetName();
		if( currentName == in_strSubResource )
			return resIter->Get();
	}

	// if the virtual file system contains a directory or file whose name 
	// matches the resource's name, create a new sub resource for it
	std::string qualifiedChildName = GetQualifiedName();
	if( qualifiedChildName.length() > 0 &&
		qualifiedChildName[qualifiedChildName.length()-1] != '/' )
	{
		qualifiedChildName += "/";
	}
	qualifiedChildName += in_strSubResource;

	if( vfs::VFileSystemPtr()->Exists(qualifiedChildName.c_str()) )
	{
		VResource* newChild = new VResource(in_strSubResource, this);
		m_SubResources.push_back(VSharedPtr<VResource>(newChild));

		return newChild;
	}
	else
	{
		// not found
		return 0;
	}
}

VRangeIterator<VResource> VResource::ChildIterator()
{
	return CreateDerefBeginIterator<VResource>(m_SubResources);
}

VRangeIterator<const VResource> VResource::ChildIterator() const
{
	return CreateDerefBeginIterator<const VResource>(m_SubResources);
}

VResource* VResource::GetResourceByPath(const std::string& in_strChildName)
{
    // parse string to get all elements seperated by '/'
	VSimpleTokenizer tokens(in_strChildName, '/');
	VSimpleTokenizer::Iterator currentRes = tokens.TokenBegin();

	VResource* pCurrentResource = this;

	// select initial resource: root for absolute and this for relative paths
	if(in_strChildName.size() > 0 && in_strChildName[0] == '/' )
	{
		pCurrentResource = GetRootResource();

		// first string in path will be "", skip it
		++currentRes;
	}

	// as long as we have a valid resource and have not reached the paths end
	while( pCurrentResource != 0 && currentRes != tokens.TokenEnd() )
	{
		const std::string currentResName = *currentRes;

		// on '..' navigate to parent
		if( *currentRes == ".." )
			pCurrentResource = pCurrentResource->GetParent();
		// on '.' stay in same resource
		else if( *currentRes == "." )
			pCurrentResource = pCurrentResource;
		// else navigate to child
		else
			pCurrentResource = pCurrentResource->GetSubResource(*currentRes);

		++currentRes;
	}

	// resource could not be found
	if( 0 == pCurrentResource )
	{
		std::stringstream message;
		message << "Could not find resource '" << in_strChildName  
			<< "' from resource '" << GetQualifiedName() << "'";

		V3D_THROW(VResourceNotFoundException, message.str().c_str());
	}
	// resource could be found
	else
	{
		return pCurrentResource;
	}
}

void VResource::DumpInfo(const std::string& in_strPrefix) const
{
	using namespace std;

	vout << in_strPrefix << "-> " << m_strName << vendl;

	// print info about data
	for(DataMap::const_iterator data = m_Data.begin();
		data != m_Data.end();
		++data)
	{
		VResourceData* pData = data->second.Get();

		vout << in_strPrefix << "Data of type '";
		vout << data->first.ToString() << "'" << vendl;
	}

	// print info about subdirectories    
	for(ResourceContainer::const_iterator child = m_SubResources.begin();
		m_SubResources.end() != child;
		++child)
	{
		(*child)->DumpInfo(in_strPrefix + "  ");
	}
}

vbool VResource::ContainsData(VResourceData::TypeId in_Type)
{
	DataMap::const_iterator data = m_Data.find(in_Type);
	return data != m_Data.end();
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
			try
			{
				// try to generate data
				(*resType)->Generate(this, in_Type);

				// try to get data again
				data = m_Data.find(in_Type);
			}
			// if the resource type tried to get data which does not exists
			// just continue the generation process
			catch(VDataNotFoundException&)
			{}

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
		message << "Could not find data of type '" << in_Type.ToString();
		//message << typeid(VTypedResourceData<DataType>).name() << "'";
		message << "' in resource '" << GetQualifiedName() << "'";

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
