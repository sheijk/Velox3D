#include "VOpenGLIndexMesh.h"
//-----------------------------------------------------------------------------
#include "VOpenGLUtils.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VOpenGLIndexMesh::VOpenGLIndexMesh(
	const VMeshDescription& in_Descr,
	IVMaterial* in_pMaterial
	) :
	VMeshBase(in_pMaterial)
{
	V3D_ASSERT(in_Descr.triangleVertices.hBuffer != 0);

	m_TriangleData = in_Descr.triangleVertices;
	m_ColorData = in_Descr.triangleColors;
	m_IndexData = in_Descr.triangleIndices;
	m_TexCoordData = in_Descr.triangleTexCoords;

	m_PrimitiveType = GetGeometryMode(in_Descr.geometryType);
}

VOpenGLIndexMesh::~VOpenGLIndexMesh()
{
}

void VOpenGLIndexMesh::Render()
{
	//TODO: vertex formate beachten (stride, offset, start..)

	const vuint iNumElements = m_IndexData.nCount;

	const vfloat32* pBuffer = reinterpret_cast<vfloat32*>(
		m_TriangleData.hBuffer->GetDataAddress());

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, pBuffer);

    if( m_TexCoordData.hBuffer != 0 )
	{
		const vfloat32* pTexBuffer = reinterpret_cast<vfloat32*>(
			m_TexCoordData.hBuffer->GetDataAddress());

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, pTexBuffer);
	}

	if( m_ColorData.hBuffer != 0 )
	{
		const vfloat32* pColorBuffer = reinterpret_cast<vfloat32*>(
			m_ColorData.hBuffer->GetDataAddress());
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, pColorBuffer);
	}

	const vint32* pIndexBuffer = reinterpret_cast<vint32*>(m_IndexData.hBuffer->GetDataAddress());
	
	glDrawElements(m_PrimitiveType, iNumElements, GL_UNSIGNED_INT, pIndexBuffer);
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------