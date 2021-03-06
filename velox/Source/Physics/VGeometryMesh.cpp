/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VGeometryMesh.h>
#include <V3d/Physics/VSpace.h>
#include <V3d/Core.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
VGeometryMesh::VGeometryMesh(VBoundingMesh in_BoundingMesh)
{
	m_TriMeshData = 0;
	m_BoundingMesh = in_BoundingMesh;
}

VGeometryMesh::~VGeometryMesh()
{
	Delete();
	VGeometry::~VGeometry();
}

void VGeometryMesh::Delete()
{
	dGeomTriMeshDataDestroy (m_TriMeshData);
}

void VGeometryMesh::Create(VSpace* in_SpaceState)
{
	//@note: this only works for single precision vertex buffer. to change this
	//use the according functions in collision_trimesh, in ode.
	m_TriMeshData = dGeomTriMeshDataCreate();

	dGeomTriMeshDataBuildSingle(
		m_TriMeshData,
		m_BoundingMesh.GetVertices(),
		m_BoundingMesh.GetVertexStride(),
		m_BoundingMesh.GetVertexCount(),
		m_BoundingMesh.GetIndices(),
		m_BoundingMesh.GetIndexCount(),
		m_BoundingMesh.GetIndexStride()
		//m_BoundingMesh.GetNormals()
		);
  
	V3D_ASSERT(in_SpaceState != 0);
	//@note: last 3 params are optional collision callbacks
	m_GeomID = dCreateTriMesh (*in_SpaceState->GetSpaceID(), m_TriMeshData, 0,0,0);
	
	//dGeomSetData(m_GeomID, m_TriMeshData);
	//dGeomSetPosition(m_GeomID , 0,0,0);
}
//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

