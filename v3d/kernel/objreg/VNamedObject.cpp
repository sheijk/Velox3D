#include "VNamedObject.h"
//------------------------------------------------------------------------
#include "VObjectRegistry.h"

VNamedObject::VNamedObject(const VNamedObject *in_Parent) :
	// get a name
	m_Key(VObjectRegistry::GetInstance()->GenerateKey())
{
	// register object
	VObjectRegistry::GetInstance()->RegisterObject(m_Key, *this);
}

VNamedObject::~VNamedObject()
{
	// unregister object
	VObjectRegistry::GetInstance()->UnregisterObject(*this);
}

const VObjectKey& VNamedObject::GetKey() const
{
	return m_Key;
}