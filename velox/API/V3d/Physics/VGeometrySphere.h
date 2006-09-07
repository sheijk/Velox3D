/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VGeometrySphere_2004_11_07_H
#define V3D_VGeometrySphere_2004_11_07_H
//-----------------------------------------------------------------------------
#include <V3d/Physics/VGeometry.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
class VSpace;

class VGeometrySphere : public VGeometry
{
public:

	VGeometrySphere();
	virtual ~VGeometrySphere();

	void CreateSphere(VSpace* in_SpaceState);
	void SetSphereRadius(vfloat32 in_fRadius);
	vfloat32 GetSphereRadius();
	
private:

	VGeometrySphere(const VGeometrySphere&);
	VGeometrySphere& operator=(const VGeometrySphere&);
    
	vfloat32 m_fRadius;
};


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGeometrySphere_2004_11_07_H

