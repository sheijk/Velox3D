//-----------------------------------------------------------------------------
#include "VOpenGLIndexMesh.h"
//-----------------------------------------------------------------------------
#include <windows.h>
#include <gl/gl.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------


VOpenGLIndexMesh::VOpenGLIndexMesh(const VMeshDescription& in_Descr)
{
	m_TriangleData = in_Descr.triangleVertices;
	m_ColorData = in_Descr.triangleColors;
	m_IndexData = in_Descr.triangleIndices;
}

VOpenGLIndexMesh::~VOpenGLIndexMesh()
{
}

void VOpenGLIndexMesh::Render()
{
	const vuint iNumElements = m_IndexData.nCount;

	const vfloat32* pBuffer = m_TriangleData.hBuffer->GetDataAddress();
	const vint32* pIndexBuffer = m_IndexData.hBuffer->GetDataAddress();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, pBuffer);
	
	glDrawElements(GL_LINE_STRIP, iNumElements, GL_UNSIGNED_INT, pIndexBuffer);
	
	glDisableClientState(GL_VERTEX_ARRAY);
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------