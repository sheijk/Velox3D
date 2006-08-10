#ifndef V3D_VCONTACTREPORT_09_24_04_H
#define V3D_VCONTACTREPORT_09_24_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace collision {
//-----------------------------------------------------------------------------

/**
 * Utitlity class for information about collision of a model
 * @author:		ins
 * @version:	1.0
 */

//@note: add exact contact point and normals?

class VContactReport
{
public:
	
	VContactReport();
	~VContactReport();
	
	/**
	 * deletes gained resources
	 */
    
	void Delete();

	/**
	 * returns number of contacted triangles
	 */

    vuint32		GetContactCount();

	vuint32*	GetTriangleIndices();

	void		SetContactCount(vuint32 in_nCount);

private:

	vuint32		m_iNumContacts;
	vuint32*	m_pContactedTriangleIndices;

};
//-----------------------------------------------------------------------------
} // namespace collision
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONTACTREPORT_09_24_04_H
