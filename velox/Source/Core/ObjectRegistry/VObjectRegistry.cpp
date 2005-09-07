#include <V3d/Core/VObjectRegistry.h>
//------------------------------------------------------------------------
#include <V3d/Core/VLogging.h>
#include <sstream>
#include <iomanip>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using std::ostringstream;

using std::pair;
namespace v3d {
//-----------------------------------------------------------------------------

VObjectRegistry* VObjectRegistry::s_pInstance = 0;

//-----------------------------------------------------------------------------

VObjectRegistry::VObjectRegistry()
{
	m_nLastKeyNum = 0;
	m_strLastGeneratedName = "0";
}	

VObjectRegistry::~VObjectRegistry()
{
	// unregister all objects
}

/**
 * Sets the single instance. Must only be called once. Is needed to ensure
 * that all DLLs and the main program use the same object registry instance
 * (a static variable is only unique per module, thus there would be one
 * instance for each DLL
 */
void VObjectRegistry::SetInstance(Pointer in_pInstance)
{
	if( 0 == s_pInstance )
	{
		s_pInstance = in_pInstance;
	}
	else
	{
		V3D_THROW(VObjectRegistryException, 
			"VObjectRegistry: tried to change single instance");
	}
}

/** 
 * Creates an instance of the object registry 
 * (needed by the Kernel to create the single obj. reg. instance)
 */
VObjectRegistry::Pointer VObjectRegistry::CreateInstance()
{
	return new VObjectRegistry();
}

/**
 * Returns the single instance. Instance will be created if it did not
 * exist, yet
 */
VObjectRegistry::Pointer VObjectRegistry::GetInstance()
{
	if( 0 == s_pInstance )
	{
		V3D_THROW(VObjectRegistryException,
			"Tried to access VObjectRegistry single instance before it was set");
	}

	return s_pInstance;
}

void VObjectRegistry::RegisterObject(
	const VObjectKey& in_Name,
	VNamedObject& in_Object)
{
	//std::ostringstream str;
	//str << "Object registered: addr(" << &in_Object << "), name: \""
	//	<< in_Name.ToString().AsCString() << "\"" << std::endl;
	//V3D_DEBUGMSG(str.str().c_str());

	// register object
	pair<ObjectKeyMap::iterator, bool> res;
	VNamedObject* pObj = &in_Object;
	ObjectKeyMap::value_type newVal(in_Name, pObj);
	
	res = m_Objects.insert(newVal);

	if( res.second == false ) 
	{
		// throw exception
		V3D_THROW(VObjectRegistryException, 
			"tried to register object \"" 
			+ in_Name.ToString()
			+ "\"twice");
	}
}

void VObjectRegistry::UnregisterObject(VNamedObject& in_Object)
{
	ObjectKeyMap::iterator iter;
	iter = m_Objects.find(in_Object.GetKey());
	m_Objects.erase(iter);

	//std::ostringstream str;
	//str << "Object unregistered: " << in_Object.GetKey().ToString() << std::endl;
	//V3D_DEBUGMSG(str.str().c_str());
}

VNamedObject& VObjectRegistry::GetObject(const VObjectKey& in_Key)
{
	ObjectKeyMap::iterator iter;
	VNamedObject* pObj = 0;

	iter = m_Objects.find(in_Key);

	if( iter == m_Objects.end() )
	{
		// throw exception
		V3D_THROW(VObjectRegistryException, 
			"object \"" + in_Key.ToString() + "\" does not exist");
	}

	pObj = iter->second;

	return *pObj;
}

vbool VObjectRegistry::ContainsObject(const VObjectKey& in_Key)
{
	return m_Objects.find(in_Key) != m_Objects.end();
}

VObjectKey VObjectRegistry::GetKey(const VNamedObject& obj)
{
	// find the object
	ObjectKeyMap::iterator iter = m_Objects.begin();

	for(; iter != m_Objects.end(); ++iter)
	{
		// abort of object has been found
		if( &obj == iter->second ) break;
	}

	// throw error if object could not be found
	if( m_Objects.end() == iter ) 
	{
		V3D_THROW(VObjectRegistryException, "object could not be found");
	}

	// return it's key
	return iter->first;
}

VObjectKey VObjectRegistry::GenerateKey()
{
	ostringstream str;

	// generate an unused key
	while( m_Objects.find(m_strLastGeneratedName.c_str()) != m_Objects.end() )
	{
		m_nLastKeyNum++;
		
		str << std::hex << m_nLastKeyNum;

		m_strLastGeneratedName = str.str();
	}

	return VObjectKey(m_strLastGeneratedName.c_str());
}

VStringRetVal VObjectRegistry::GetObjectDump() const
{
	ObjectKeyMap::const_iterator objIter = m_Objects.begin();
	std::string strObjList;

	for( ; objIter != m_Objects.end(); ++objIter)
	{
		strObjList += "<" + objIter->first.ToString() + ">\n";
	}

	return strObjList.c_str();
}

//-----------------------------------------------------------------------------
} // namespace v3d


