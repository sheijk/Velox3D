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
	m_TexCoordData = in_Descr.triangleTexCoords;
}

VOpenGLIndexMesh::~VOpenGLIndexMesh()
{
}

void VOpenGLIndexMesh::Render()
{
	const vuint iNumElements = m_IndexData.nCount;

	const vfloat32* pBuffer = reinterpret_cast<vfloat32*>(m_TriangleData.hBuffer->GetDataAddress());
	const vint32* pIndexBuffer = reinterpret_cast<vint32*>(m_IndexData.hBuffer->GetDataAddress());
	const vfloat32* pTexBuffer = reinterpret_cast<vfloat32*>(m_TexCoordData.hBuffer->GetDataAddress());

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, pBuffer);
	glTexCoordPointer(2, GL_FLOAT, 0, pTexBuffer);
	
	glDrawElements(GL_TRIANGLE_STRIP, iNumElements, GL_UNSIGNED_INT, pIndexBuffer);
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------