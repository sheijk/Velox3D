//-----------------------------------------------------------------------------
#include <extgl/extgl.h>
#include "VOpenGLVBOMesh.h"
#include "VOpenGlUtils.h"

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
//disable cast warning
#pragma warning (disable : 4312)

VOpenGLVBOMesh::HandleVBOMap VOpenGLVBOMesh::s_VBOMap;

VOpenGLVBOMesh::VOpenGLVBOMesh(
		const VMeshDescription& in_Descr,
		IVMaterial* in_pMaterial)  : VMeshBase(in_pMaterial)

{
	// init def vals
	m_bColors = false;
	m_bTexCoords = false;
	m_bIndex = false;

	m_VertexVBOID = 0;
	m_ColorVBOID = 0;
	m_TexCoordVBOID = 0;
	m_IndexVBOID = 0;

    // do vertices exist?
	V3D_VERIFY(in_Descr.GetCoordinateBuffer() != 0);

	m_PrimitiveType = GetGeometryMode(in_Descr.GetGeometryType());
	
	m_VertexVBOID = GetVertexBuffer(in_Descr.GetCoordinateBuffer());
	
	//m_TriangleData  = in_Descr.triangleVertices;
	m_CoordinateFormat = in_Descr.GetCoordinateFormat();
	
	if(in_Descr.GetColorBuffer() != 0)
	{
		m_bColors = true;
		//m_ColorData = in_Descr.triangleColors;
		m_ColorFormat = in_Descr.GetColorFormat();
		m_ColorVBOID = GetVertexBuffer(in_Descr.GetColorBuffer());
	}

	V3D_ASSERT(in_Descr.GetTexCoordCount() == 0);

	if(in_Descr.GetTexCoordBuffer(0) != 0)
	{
		m_bTexCoords = true;
		//m_TexCoordData = in_Descr.triangleTexCoords;
		m_TexCoordFormat = in_Descr.GetTexCoordFormat(0);
		m_TexCoordVBOID = GetVertexBuffer(in_Descr.GetTexCoordBuffer(0));
	}
	
	if(in_Descr.GetIndexBuffer() != 0)
	{
		m_bIndex = true;
		//m_IndexData = in_Descr.triangleIndices;
		m_IndexFormat = in_Descr.GetIndexFormat();
		
		m_IndexVBOID = GetVertexBuffer(in_Descr.GetIndexBuffer());
	}
	
}

VOpenGLVBOMesh::~VOpenGLVBOMesh()
{
	// Delete buffer object
	vuint iBuffer[1] = {1};
	
	glDeleteBuffersARB(m_VertexVBOID, iBuffer);
	
	if(m_bColors)
		glDeleteBuffersARB(m_ColorVBOID, iBuffer);
}

void VOpenGLVBOMesh::Render()
{
	// Enable array
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VertexVBOID);
	glVertexPointer(3, GL_FLOAT, 
		m_CoordinateFormat.GetStride() * sizeof(vfloat32), 
		(void*)(m_CoordinateFormat.GetFirstIndex() * sizeof(vfloat32)));
		
	if(m_bColors)
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_ColorVBOID);
		glColorPointer(4, GL_FLOAT,
			m_ColorFormat.GetStride() * sizeof(vfloat32), 
			(void*) (m_ColorFormat.GetFirstIndex() * sizeof(vfloat32)));		
	}

	if(m_bTexCoords)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_TexCoordVBOID);
		glTexCoordPointer(2, GL_FLOAT, 
			m_TexCoordFormat.GetStride() * sizeof(vfloat32), 
			(void*) (m_TexCoordFormat.GetFirstIndex() * sizeof(vfloat32)));
	}

	if(m_bIndex)
	{
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexVBOID);
		//glDrawElements(m_PrimitiveType, m_IndexData.nCount, GL_UNSIGNED_INT, m_IndexData.hBuffer->GetDataAddress());
		glDrawElements(m_PrimitiveType, 
			m_IndexFormat.GetCount(), GL_UNSIGNED_INT, 
			(void*)(m_IndexFormat.GetFirstIndex() * sizeof(vuint)));
	}
	else
	{
		glDrawArrays(m_PrimitiveType, 0, m_CoordinateFormat.GetCount());
	}
	
	/* one way to draw the array */
	

	// Disable arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

GLuint VOpenGLVBOMesh::GetVertexBuffer(VMeshDescription::BufferHandle in_hHandle)
{
	//look if our handle is still in the list
	HandleVBOMap::iterator findIter;
	findIter = s_VBOMap.find(in_hHandle);

	if(findIter == s_VBOMap.end())
	{
		//TODO: ClientState may be interesting for driver optimization. build in! -ins
		//glEnableClientState(GL_COLOR_ARRAY);

		GLuint vboID;

		/* create a vertex buffer object */
		glGenBuffersARB(1, &vboID);

		// add the new key to the map
		s_VBOMap[in_hHandle] = vboID;

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboID);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, (in_hHandle->GetSize()),
			in_hHandle->GetDataAddress(),
			GL_STATIC_DRAW_ARB
			);

	/*	glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);*/

		return vboID;
	}
	
	else	
	{
		return m_VertexVBOID;
	}

}
#pragma warning (default : 4312)

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------