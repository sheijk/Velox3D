#include "VOpenGLIndexMesh.h"
//-----------------------------------------------------------------------------
#include "VOpenGLUtils.h"

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VOpenGLIndexMesh::VOpenGLIndexMesh(
	const VMeshDescription& in_Descr,
	std::vector<IVMaterial*> in_Materials
	) :
	VMeshBase(in_Materials)
{
	V3D_ASSERT(in_Descr.GetCoordinateBuffer() != 0);
	//V3D_ASSERT(in_Descr.triangleVertices.hBuffer != 0);
	V3D_ASSERT(in_Descr.GetTexCoordCount() == 1);

	m_MeshDescription = in_Descr;
	//m_TriangleData = in_Descr.triangleVertices;
	//m_ColorData = in_Descr.triangleColors;
	//m_IndexData = in_Descr.triangleIndices;
	//m_TexCoordData = in_Descr.triangleTexCoords;

	m_PrimitiveType = GetGeometryMode(in_Descr.GetGeometryType());
	//m_PrimitiveType = GetGeometryMode(in_Descr.geometryType);
}

VOpenGLIndexMesh::~VOpenGLIndexMesh()
{
}

void VOpenGLIndexMesh::Render()
{
	const vuint iNumElements = m_MeshDescription.GetIndexFormat().GetCount();
	//const vuint iNumElements = m_IndexData.nCount;

	const vfloat32* pBuffer = reinterpret_cast<vfloat32*>(
		m_MeshDescription.GetCoordinateBuffer()->GetDataAddress());
	//const vfloat32* pBuffer = reinterpret_cast<vfloat32*>(
	//	m_TriangleData.hBuffer->GetDataAddress());

	VDataFormat coordinateFormat = m_MeshDescription.GetCoordinateFormat();
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(
		3, 
		GL_FLOAT, 
		coordinateFormat.GetStride() * sizeof(vfloat32),
		//m_TriangleData.nStride * sizeof(vfloat32), 
		pBuffer + coordinateFormat.GetFirstIndex());
		//pBuffer + m_TriangleData.nStart);

	if(m_MeshDescription.GetTexCoordBuffer(0) != 0)
    //if( m_TexCoordData.hBuffer != 0 )
	{
		VDataFormat texCoordFormat = m_MeshDescription.GetTexCoordFormat(0);

		const vfloat32* pTexBuffer = reinterpret_cast<vfloat32*>(
			m_MeshDescription.GetTexCoordBuffer(0)->GetDataAddress());
		//const vfloat32* pTexBuffer = reinterpret_cast<vfloat32*>(
		//	m_TexCoordData.hBuffer->GetDataAddress());

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(
			2, 
			GL_FLOAT, 
			texCoordFormat.GetStride() * sizeof(vfloat32),
			//m_TexCoordData.nStride * sizeof(vfloat32), 
			pTexBuffer + texCoordFormat.GetFirstIndex());
			//pTexBuffer + m_TexCoordData.nStart);
	}

	if( m_MeshDescription.GetColorBuffer() != 0 )
	//if( m_ColorData.hBuffer != 0 )
	{
		const vfloat32* pColorBuffer = reinterpret_cast<vfloat32*>(
			m_MeshDescription.GetColorBuffer()->GetDataAddress());
		//const vfloat32* pColorBuffer = reinterpret_cast<vfloat32*>(
		//	m_ColorData.hBuffer->GetDataAddress());
        VDataFormat colorFormat = m_MeshDescription.GetColorFormat();

		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(
			4, 
			GL_FLOAT, 
			colorFormat.GetStride() * sizeof(vfloat32),
			//m_ColorData.nStride * sizeof(vfloat32), 
			pColorBuffer + colorFormat.GetFirstIndex());
			//pColorBuffer + m_ColorData.nStart);
	}

	const vuint32* pIndexBuffer =
		reinterpret_cast<vuint32*>(m_MeshDescription.GetIndexBuffer()->GetDataAddress());
	//const vint32* pIndexBuffer = reinterpret_cast<vint32*>(m_IndexData.hBuffer->GetDataAddress());
	
	glDrawElements(m_PrimitiveType, iNumElements, GL_UNSIGNED_INT, pIndexBuffer);
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------