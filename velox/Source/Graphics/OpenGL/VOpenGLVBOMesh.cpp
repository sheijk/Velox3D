//-----------------------------------------------------------------------------
#include "VOpenGLVBOMesh.h"

#include <v3d/Core/VException.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VOpenGLVBOMesh::VOpenGLVBOMesh(VMeshDescription& in_MeshDescr)
{
	m_TriangleData = in_MeshDescr.triangleVertices;
	m_ColorData = in_MeshDescr.triangleColors;
	vfloat32* pBuffer = m_TriangleData.hBuffer->GetDataAddress();
	vfloat32* pColorBuffer = m_ColorData.hBuffer->GetDataAddress();

	m_iNumElements = m_TriangleData.nCount;
//	m_iNumElements = (m_TriangleData.nEnd - m_TriangleData.nStart) / 3;

	glEnableClientState(GL_VERTEX_ARRAY);


	/* create a vertex buffer object */
	glGenBuffersARB(1, &m_ArrayID);

	/* create a data score for vertex information and fill it with the vertices*/
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_ArrayID);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_iNumElements *3 * sizeof(GLfloat),
		pBuffer,
		GL_STATIC_DRAW_ARB
		);

	glEnableClientState(GL_COLOR_ARRAY);

	glGenBuffersARB(1, &m_ColorArrayID);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_ColorArrayID);
	glColorPointer(3, GL_FLOAT,0, 0);
		
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_iNumElements *3 * sizeof(GLfloat),
		pColorBuffer,
		GL_STATIC_DRAW_ARB
		);

	
	// Free system memory buffer
	//TODO free when we know we can free it
	//free(data);
}

VOpenGLVBOMesh::~VOpenGLVBOMesh()
{
    // Delete buffer object
	vuint iBuffer[1] = {1};
	glDeleteBuffersARB(m_ArrayID, iBuffer);
	glDeleteBuffersARB(m_ColorArrayID, iBuffer);

}

void VOpenGLVBOMesh::Render()
{
	// Enable arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_ArrayID);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_ColorArrayID);
	glColorPointer(3, GL_FLOAT,0, 0);

	// oben wird noch VException.h eingebunden, muss auch wieder raus
	// nCount gibt jetzt die anzahl der vertices an..
	// die ganze semantik von VMeshDescription hat sich leicht geaendert
	V3D_THROW(VException, "broken, nEnd replaced by nCount (different"
		" meaning! fix this.. (-sheijk)");

	/* one way to draw the array */
//	glDrawArrays(GL_TRIANGLES, m_TriangleData.nStart, m_TriangleData.nEnd);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, m_iNumElements*3);

	// Disable arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------