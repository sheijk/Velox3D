//-----------------------------------------------------------------------------
#include <v3dLib/Collision/VContactReport.h>
#include <v3d/Core/MemManager.h>
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

//-----------------------------------------------------------------------------
} // namespace collision
} // namespace v3d
//-----------------------------------------------------------------------------