/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VGEOMETRYMESH_2006_17_03_H
#define V3D_VGEOMETRYMESH_2006_17_03_H
//-----------------------------------------------------------------------------
#include <V3d/Physics/VGeometry.h>
#include <V3d/Physics/Bounding/VBoundingMesh.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
class VSpace;

class VGeometryMesh : public VGeometry
{
public:

	VGeometryMesh(VBoundingMesh in_BoundingMesh);
	virtual ~VGeometryMesh();

	void Create(VSpace* in_SpaceState);
	void Delete();
	/*void CreateSphere(VSpace* in_SpaceState);
	void SetSphereRadius(vfloat32 in_fRadius);
	vfloat32 GetSphereRadius();
	*/
private:

	VBoundingMesh m_BoundingMesh;
	dTriMeshDataID m_TriMeshData;

	VGeometryMesh(const VGeometryMesh&);
	VGeometryMesh& operator=(const VGeometryMesh&);
    
};


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGEOMETRYMESH_2006_17_03_H

