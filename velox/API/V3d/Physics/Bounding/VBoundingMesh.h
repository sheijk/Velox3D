#ifndef V3D_VBOUNDINGMESH_12_28_05
#define V3D_VBOUNDINGMESH_12_28_05
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
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
		const float* in_pVertices,
		vuint in_nVertexCount,
		vuint in_nVertexStride = 0,
		const vint* in_pIndices = 0,
		vuint in_nIndexCount = 0,
		vuint in_nIndexStride = 0,
		const float* in_pNormals = 0,
		vuint in_nNormalCount = 0,
		vuint in_nNormalStride =0 
		);

	virtual ~VBoundingMesh();



	const vfloat32* GetVertices();
	const vint* GetIndices();
	const vfloat32* GetNormals();

	vuint GetVertexStride();
	vuint GetVertexCount();
	vuint GetIndexStride();
	vuint GetIndexCount();
	vuint GetNormalStride();
	vuint GetNormalCount();


private:

	const float* m_pVertices;
	const vint* m_pIndices;
	const float* m_pNormals;
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
