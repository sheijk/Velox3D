#include "VResourceManager.h"
//-----------------------------------------------------------------------------

#include <iostream>
#include <list>
#include <algorithm>
#include <string>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

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

/**
 * A simple tokenizer class. Takes a string and a delimeter character
 * and parses the string into a list of tokens
 *
 * @author sheijk
 */
class VSimpleTokenizer
{
public:
	typedef std::list<std::string>::iterator Iterator;

	VSimpleTokenizer(const std::string& in_strString, char in_cDelimeter);

	Iterator TokenBegin();
	Iterator TokenEnd();

private:
	std::list<std::string> m_Tokens;
};

//-----------------------------------------------------------------------------
VSimpleTokenizer::VSimpleTokenizer(
	const std::string& in_strString, char in_cDelimeter)
{
	std::string::const_iterator tokenStart = in_strString.begin();
	std::string::const_iterator tokenEnd;

	while( true )
	{
		tokenEnd = std::find(tokenStart, in_strString.end(), in_cDelimeter);
		if( tokenStart == in_strString.end() )
			break;

		// get token
		std::string token(tokenStart, tokenEnd);
		m_Tokens.push_back(token);

		tokenStart = tokenEnd;
		if( tokenStart != in_strString.end() )
			++tokenStart;
	}
}

VSimpleTokenizer::Iterator VSimpleTokenizer::TokenBegin()
{
	return m_Tokens.begin();
}

VSimpleTokenizer::Iterator VSimpleTokenizer::TokenEnd()
{
	return m_Tokens.end();
}
//-----------------------------------------------------------------------------
using namespace std;

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
		V3D_ASSERT(in_strName[0] == '/');
	}
} // anonymous namespace

VResourceId VResourceManager::CreateResource(VStringParam in_strName)
{
	CheckResourceName(in_strName);

	cout << sizeof(vfloat64) << endl;

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

	//// get directories of path
	//VSimpleTokenizer tokens(std::string(in_strName+1), '/');

	//// find resource
	//VResource* pCurrentRes = &m_RootResource;
	//VSimpleTokenizer::Iterator currentDir = tokens.TokenBegin();

	//// until end of name list reached, or a (sub) resource has not been found
	//while(currentDir != tokens.TokenEnd() && 0 != pCurrentRes )
	//{
	//	pCurrentRes = pCurrentRes->GetSubResource(*currentDir);
	//	++currentDir;
	//}

	//return VResourceId(pCurrentRes);
}

void VResourceManager::RegisterResourceType(VSharedPtr<IVResourceType> in_pResType)
{
	m_ManagedTypes.insert(
		TypeMap::value_type(in_pResType->GetTypeId(), in_pResType));
}

std::vector<IVResourceType*> VResourceManager::GetResourceTypes(
	VResourceData::TypeId in_Type)
{
	std::vector<IVResourceType*> types;

	TypeMap::const_iterator iter = m_ManagedTypes.find(in_Type);

	while(iter != m_ManagedTypes.end() && iter->first == in_Type)
	{
		types.push_back(iter->second.Get());
		++iter;
	}

	return types;
}

void VResourceManager::DumpResourceInfo() const
{
	m_RootResource.DumpInfo("");
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
