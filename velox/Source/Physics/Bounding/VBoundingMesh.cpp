/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/Bounding/VBoundingMesh.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VBoundingMesh::VBoundingMesh()
{
	m_pVertices = 0;
	m_pIndices = 0;
	m_pNormals = 0;

	m_nVertexCount = 0;
	m_nVertexStride = 0;
	
	m_nIndexCount = 0;
	m_nIndexStride = 0;
	
	m_nNormalCount = 0;
	m_nNormalStride = 0;
}

VBoundingMesh::VBoundingMesh(
							 float* in_pVertices,
							 vuint in_nVertexCount,
							 vuint in_nVertexStride,
							 vuint* in_pIndices,
							 vuint in_nIndexCount,
							 vuint in_nIndexStride,
							 float* in_pNormals,
							 vuint in_nNormalCount,
							 vuint in_nNormalStride
							 )
{
	m_pVertices = in_pVertices;
	m_nVertexCount = in_nVertexCount;
	m_nVertexStride = in_nVertexStride;

	m_pIndices = in_pIndices;
	m_nIndexCount = in_nIndexCount;
	m_nIndexStride = in_nIndexStride;

	m_pNormals = in_pNormals;
	m_nNormalCount = in_nNormalCount;
	m_nNormalStride = in_nNormalStride;
}

VBoundingMesh::~VBoundingMesh()
{
	;
}

vfloat32* VBoundingMesh::GetVertices()
{
	return m_pVertices;
}

vuint* VBoundingMesh::GetIndices()
{
	return m_pIndices;
}

vfloat32* VBoundingMesh::GetNormals()
{
	return m_pNormals;
}

vuint VBoundingMesh::GetVertexStride()
{
	return m_nVertexStride;
}

vuint VBoundingMesh::GetVertexCount()
{
	return m_nVertexCount;
}

vuint VBoundingMesh::GetIndexStride()
{
	return m_nIndexStride;
}

vuint VBoundingMesh::GetIndexCount()
{
	return m_nIndexCount;
}

vuint VBoundingMesh:: GetNormalStride()
{
	return m_nNormalStride;
}

vuint VBoundingMesh::GetNormalCount()
{
	return m_nNormalCount;
}


//-----------------------------------------------------------------------------
} // namespace v3d::
//-----------------------------------------------------------------------------

