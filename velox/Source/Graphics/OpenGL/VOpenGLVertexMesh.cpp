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
	m_ColorData = in_Descr.triangleColors;
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
	vfloat32* pColorBuffer = m_ColorData.hBuffer->GetDataAddress();

	for(vuint i = 0; i < cnTriangleCount; i++)
	{
		glVertex3f( 
			GetVertexVal(pBuffer, m_TriangleData.nStride, i, X_AXIS),
			GetVertexVal(pBuffer, m_TriangleData.nStride, i, Y_AXIS),
			GetVertexVal(pBuffer, m_TriangleData.nStride, i, Z_AXIS)
			);

		glColor3f( 
			GetVertexVal(pColorBuffer, m_ColorData.nStride, i, X_AXIS),
			GetVertexVal(pColorBuffer, m_ColorData.nStride, i, Y_AXIS),
			GetVertexVal(pColorBuffer, m_ColorData.nStride, i, Z_AXIS)
			);

	}

	glEnd();
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------