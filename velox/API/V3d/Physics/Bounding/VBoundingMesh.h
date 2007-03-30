/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VBOUNDINGMESH_12_28_05
#define V3D_VBOUNDINGMESH_12_28_05
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d { 
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * implements a arbitrary bounding volume
 * @author: ins
 */
class VBoundingMesh
{
public:

	VBoundingMesh();
	VBoundingMesh(
		float* in_pVertices,
		vuint in_nVertexCount,
		vuint in_nVertexStride = 0,
		vuint* in_pIndices = 0,
		vuint in_nIndexCount = 0,
		vuint in_nIndexStride = 0,
		float* in_pNormals = 0,
		vuint in_nNormalCount = 0,
		vuint in_nNormalStride =0 
		);

	virtual ~VBoundingMesh();



	vfloat32* GetVertices();
	vuint* GetIndices();
	vfloat32* GetNormals();

	vuint GetVertexStride();
	vuint GetVertexCount();
	vuint GetIndexStride();
	vuint GetIndexCount();
	vuint GetNormalStride();
	vuint GetNormalCount();


private:

	float* m_pVertices;
	vuint* m_pIndices;
	float* m_pNormals;
	vuint m_nVertexStride;
	vuint m_nVertexCount;
	vuint m_nIndexStride;
	vuint m_nIndexCount;
	vuint m_nNormalStride;
	vuint m_nNormalCount;


};

//-----------------------------------------------------------------------------
} // namespace v3d::
//-----------------------------------------------------------------------------
#endif // V3D_VBOUNDINGMESH_12_28_05

