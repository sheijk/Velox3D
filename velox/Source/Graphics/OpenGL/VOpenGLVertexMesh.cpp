//-----------------------------------------------------------------------------
#include "VOpenGLVertexMesh.h"
//-----------------------------------------------------------------------------
#include <windows.h>
#include <gl/gl.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------


VOpenGLVertexMesh::VOpenGLVertexMesh(const VMeshDescription& in_Descr)
{
	m_TriangleData = in_Descr.triangleVertices;
}

VOpenGLVertexMesh::~VOpenGLVertexMesh()
{
}

namespace
{
	const X_AXIS = 0;
	const Y_AXIS = 1;
	const Z_AXIS = 2;

	inline float GetVertexVal(
		float pStart[],
		vuint nStride,
		vuint nTriangle,
		vuint nAxis
		)
	{
		vuint nOffset = (3 * nStride * nTriangle) + nAxis;
		return *(pStart+nOffset);
	}
} // anonymous namespace

void VOpenGLVertexMesh::Render()
{
	glBegin(GL_TRIANGLES);

	const vuint cnTriangleCount 
		= (m_TriangleData.nEnd - m_TriangleData.nStart) / 3;

	vfloat32* pBuffer = m_TriangleData.hBuffer->GetDataAddress();

	//glVertex3f(1,0,0);
	//glVertex3f(0,1,0);
	//glVertex3f(-1,0,0);

	for(vuint nTriangle = 0; nTriangle < cnTriangleCount; ++nTriangle)
	{
		glVertex3f( 
			GetVertexVal(pBuffer, m_TriangleData.nStride, nTriangle, X_AXIS),
			GetVertexVal(pBuffer, m_TriangleData.nStride, nTriangle, Y_AXIS),
			GetVertexVal(pBuffer, m_TriangleData.nStride, nTriangle, Z_AXIS)
			);
	}

	glEnd();
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------