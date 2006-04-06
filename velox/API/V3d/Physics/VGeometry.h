#ifndef V3D_VGEOMETRY_2004_11_19_H
#define V3D_VGEOMETRY_2004_11_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypes.h>
#include <ode/ode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------

/**
 * Abstract class for ode geometry
 *
 * @author: ins
 */

class VGeometry
{
public:
	
	dGeomID* GetGeomID();
	
	//TODO: FIX ME

	/**
	* MUST be explicitly called to destroy
	* dtor can't do the job yet cos of scalar deleting destructor bug
	*/
	void Destroy();

	/**
	 * Enable a geometry for collision
	 * @note: this is default
	 */
	void Enable();

	/**
	 * Disable this body for no collision test
	 */
	void Disable();

	/**
	 * Returns true if geometry is enabled for collision test
	 */
    vbool IsEnabled();

	enum Group
	{
		Group1  = 1,
		Group2  = 2,
		Group3  = 4,
		Group4  = 8,
		Group5  = 16,
		Group6  = 32,
		Group7  = 64,
		Group8  = 128,
		Group9  = 256,
		Group10 = 512,
		Group11 = 1024,
		Group12 = 2048,
		Group13 = 4096,
		Group14 = 8192,
		Group15 = 16384,
		Group16 = 32768,
		Group17 = 65536,
		Group18 = 131072,
		Group19 = 262144,
		Group20 = 524288,
		Group21 = 1048576,
		Group22 = 2097152,
		Group23 = 4194304,
		Group24 = 8388608,
		Group25 = 16777216,
		Group26 = 33554432,
		Group27 = 67108864,
		Group28 = 134217728,
		Group29 = 268435456,
		Group30 = 536870912,
		Group31 = 1073741824,
		Group32 = 2147483648,
	};

	void SetCategoryGroup(Group in_CategoryGroup);
	vint GetCategoryGroup();

	void SetCollisionGroup(Group in_CollisionGroup);
	vint GetCollisionGroup();

protected:

	VGeometry();
//	virtual ~VGeometry();

	VGeometry(const VGeometry&);
	VGeometry& operator=(const VGeometry&);

	dGeomID m_GeomID;
	vbool m_bIsEnabled;
	vint m_CategoryGroup;
	vint m_CollisionGroup;
};

//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGEOMETRY_2004_11_19_H
