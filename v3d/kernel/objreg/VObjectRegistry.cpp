#include "VObjectRegistry.h"
//------------------------------------------------------------------------
#include <iostream>

using std::cout;
using std::endl;

using std::pair;

VObjectRegistry* VObjectRegistry::m_pInstance = 0;

VObjectRegistry::VObjectRegistry()
{
}

VObjectRegistry::~VObjectRegistry()
{
	// unregister all objects
}

/**
 * Returns the single instance. Instance will be created if it did not
 * exist, yet
 */
VObjectRegistry::Pointer VObjectRegistry::GetInstance()
{
	// create instance if it does not exist already
	if( m_pInstance == 0 )
	{
		m_pInstance = new VObjectRegistry();
	}

	return m_pInstance;
}

void VObjectRegistry::RegisterObject(
	const VObjectKey& in_Name,
	VNamedObject& in_Object)
{
//	cout << "Object registered: addr(" << &in_Object << "), name: \""
//		<< in_Name.toString() << "\"" << endl;

	// register object
	pair<ObjectKeyMap::iterator, bool> res;
	VNamedObject* pObj = &in_Object;
	ObjectKeyMap::value_type newVal(in_Name, pObj);
	
	res = m_Objects.insert(newVal);

	if( res.second == false ) 
	{
		// throw exception
		V3D_THROW(VObjectRegistryException, "could not insert object");
	}
}

void VObjectRegistry::UnregisterObject(VNamedObject& in_Object)
{
//	cout << "Object unregistered: " << in_Object.GetKey().toString() << endl;

	ObjectKeyMap::iterator iter;
	iter = m_Objects.find(in_Object.GetKey());

	m_Objects.erase(iter);
}

VNamedObject& VObjectRegistry::GetObject(const VObjectKey& in_Key)
{
	ObjectKeyMap::iterator iter;
	VNamedObject* pObj = 0;

	iter = m_Objects.find(in_Key);

	if( iter == m_Objects.end() )
	{
		// throw exception
		V3D_THROW(VObjectRegistryException, "object does not exist");
	}

	pObj = iter->second;

	return *pObj;
}

VObjectKey VObjectRegistry::GetKey(const VNamedObject& obj)
{
	return VObjectKey("invalid");
}

VObjectKey VObjectRegistry::GenerateKey()
{
	return VObjectKey("lalala");
}




