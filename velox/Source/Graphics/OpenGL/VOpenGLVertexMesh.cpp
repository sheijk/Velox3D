//-----------------------------------------------------------------------------
#include "VOpenGLVertexMesh.h"
//-----------------------------------------------------------------------------
#include <windows.h>
#include <gl/gl.h>

#include <v3d/Core/VIOStream.h>
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

	// returns the float value of the triangle
	inline float GetVertexVal(
		float pStart[],
		vuint nStride,
		vuint nVertex,
		vuint nAxis
		)
	{
		vuint nOffset = (nStride * nVertex) + nAxis;
		return *(pStart+nOffset);
	}
} // anonymous namespace

void VOpenGLVertexMesh::Render()
{
	glBegin(GL_TRIANGLES);

	const vuint cnVertexCount = m_TriangleData.nCount;

	vfloat32* pBuffer = m_TriangleData.hBuffer->GetDataAddress();
	pBuffer += m_TriangleData.nStart;

	vfloat32* pColorBuffer = m_ColorData.hBuffer->GetDataAddress();
	pColorBuffer += m_ColorData.nStart;

	for(vuint nVertex = 0; nVertex < cnVertexCount; nVertex++)
	{
		glColor4f(
			GetVertexVal(pColorBuffer, m_ColorData.nStride, nVertex, 0),
			GetVertexVal(pColorBuffer, m_ColorData.nStride, nVertex, 1),
			GetVertexVal(pColorBuffer, m_ColorData.nStride, nVertex, 2),
			GetVertexVal(pColorBuffer, m_ColorData.nStride, nVertex, 3)
			);

		glVertex3f(
			GetVertexVal(pBuffer, m_TriangleData.nStride, nVertex, X_AXIS),
			GetVertexVal(pBuffer, m_TriangleData.nStride, nVertex, Y_AXIS),
			GetVertexVal(pBuffer, m_TriangleData.nStride, nVertex, Z_AXIS)
			);

	}
	glEnd();
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------