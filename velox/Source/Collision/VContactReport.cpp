/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//-----------------------------------------------------------------------------
#include <V3d/Collision/VContactReport.h>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace collision {
//-----------------------------------------------------------------------------
VContactReport::VContactReport()
{
	m_iNumContacts				= 0;
	m_pContactedTriangleIndices = 0;
}

VContactReport::~VContactReport()
{
	Delete();
}

/**
* deletes gained resources
*/

void VContactReport::Delete()
{
	delete [] m_pContactedTriangleIndices;
	m_iNumContacts = 0;
}

vuint32 VContactReport::GetContactCount()
{
	return m_iNumContacts;
}

vuint32* VContactReport::GetTriangleIndices()
{
	return m_pContactedTriangleIndices;
}

void VContactReport::SetContactCount(vuint32 in_nCount)
{
	m_iNumContacts = in_nCount;
}

//-----------------------------------------------------------------------------
} // namespace collision
} // namespace v3d
//-----------------------------------------------------------------------------
