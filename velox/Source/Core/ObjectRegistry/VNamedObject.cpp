#include <v3d/Core/VNamedObject.h>
//------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VNamedObject::VNamedObject(
	VStringParam in_pcName, 
	const VNamedObject *in_Parent)
	:
	// save name
	m_Key(in_pcName)
{
	// register object
	VObjectRegistry::GetInstance()->RegisterObject(m_Key, *this);
}

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

//-----------------------------------------------------------------------------
} // namespace v3d
