/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Core/VNamedObject.h>
//------------------------------------------------------------------------
#include <V3d/Core/VObjectRegistry.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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
	m_bRegistered = true;
}

VNamedObject::VNamedObject(const VNamedObject *in_Parent) :
	// get a name
	m_Key(VObjectRegistry::GetInstance()->GenerateKey())
{
	// register object
	VObjectRegistry::GetInstance()->RegisterObject(m_Key, *this);
	m_bRegistered = true;
}

VNamedObject::~VNamedObject()
{
	// unregister object
	UnregisterFromObjectRegistry();
}

const VObjectKey& VNamedObject::GetKey() const
{
	return m_Key;
}

void VNamedObject::UnregisterFromObjectRegistry()
{
	if( m_bRegistered )
	{
		VObjectRegistry::GetInstance()->UnregisterObject(*this);
		m_bRegistered = false;
	}
}

//-----------------------------------------------------------------------------
} // namespace v3d

