//-----------------------------------------------------------------------------
#include <extgl/extgl.h>
#include "VOpenGLVBOMesh.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VOpenGLVBOMesh::VOpenGLVBOMesh(
		const VMeshDescription& in_Descr,
		IVMaterial* in_pMaterial)  : VMeshBase(in_pMaterial)	
{
	m_TriangleData = in_Descr.triangleVertices;
	m_ColorData = in_Descr.triangleColors;
	
	
	vbyte* pBuffer = m_TriangleData.hBuffer->GetDataAddress();
	
	
	//TODO
	//vfloat32* pColorBuffer = m_ColorData.hBuffer->GetDataAddress();

	glEnableClientState(GL_VERTEX_ARRAY);

	/* create a vertex buffer object */
	glGenBuffersARB(1, &m_ArrayID);

	/* create a data score for vertex information and fill it with the vertices*/
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_ArrayID);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_TriangleData.nCount * sizeof(GLfloat),
		pBuffer,
		GL_STATIC_DRAW_ARB
		);

	/*glEnableClientState(GL_COLOR_ARRAY);

	glGenBuffersARB(1, &m_ColorArrayID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_ColorArrayID);
	glColorPointer(3, GL_FLOAT,0, 0);

	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_iNumElements *3 * sizeof(GLfloat),
		pColorBuffer,
		GL_STATIC_DRAW_ARB
		);*/


	// Free system memory buffer
	//TODO free when we know we can free it
	//free(data);
}

VOpenGLVBOMesh::~VOpenGLVBOMesh()
{
	// Delete buffer object
	vuint iBuffer[1] = {1};
	glDeleteBuffersARB(m_ArrayID, iBuffer);
	//glDeleteBuffersARB(m_ColorArrayID, iBuffer);

}

void VOpenGLVBOMesh::Render()
{
	// Enable arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_ArrayID);
	
	//TODO: needed?
	glVertexPointer(3, GL_FLOAT, 0, 0);
	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_ColorArrayID);
	//glColorPointer(3, GL_FLOAT,0, 0);

	
	/* one way to draw the array */
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_TriangleData.nCount);

	// Disable arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------