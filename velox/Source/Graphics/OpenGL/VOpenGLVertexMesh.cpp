//-----------------------------------------------------------------------------
#include "VOpenGLVertexMesh.h"
//-----------------------------------------------------------------------------
#include "VOpenGlUtils.h"
#include <v3d/Core/VIOStream.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------


VOpenGLVertexMesh::VOpenGLVertexMesh(
	const VMeshDescription& in_Descr,
	IVMaterial* in_pMaterial
	) :
	VMeshBase(in_pMaterial)	
{
	V3D_VERIFY(in_Descr.GetTexCoordCount() == 1);

	m_hCoordinateBuffer = in_Descr.GetCoordinateBuffer();
	m_hColorBuffer = in_Descr.GetColorBuffer();
	m_hTexCoordBuffer = in_Descr.GetTexCoordBuffer(0);

	m_CoordinateFormat = in_Descr.GetCoordinateFormat();
	m_ColorFormat = in_Descr.GetColorFormat();
	m_TexCoordFormat = in_Descr.GetTexCoordFormat(0);
	//m_TriangleData = in_Descr.triangleVertices;
	//m_ColorData = in_Descr.triangleColors;
	//m_TexCoordData = in_Descr.triangleTexCoords;

	m_bColors = (m_hColorBuffer != 0);
	m_bTexCoords = (m_hTexCoordBuffer != 0);

	m_PrimitiveType = GetGeometryMode(in_Descr.GetGeometryType());
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
	//glBegin(m_PrimitiveType);

	const vuint cnVertexCount = m_CoordinateFormat.GetCount();
	//const vuint cnVertexCount = m_TriangleData.nCount;

	const vfloat32* pBuffer = 
		reinterpret_cast<vfloat32*>(m_hCoordinateBuffer->GetDataAddress());
	//const vfloat32* pBuffer = 
	//	reinterpret_cast<vfloat32*>(m_TriangleData.hBuffer->GetDataAddress());
	//pBuffer += m_TriangleData.nStart;

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(
		3,
		GL_FLOAT,
		m_CoordinateFormat.GetStride() * sizeof(vfloat32),
		//m_TriangleData.nStride * sizeof(vfloat32),
		pBuffer + m_CoordinateFormat.GetFirstIndex()
		//pBuffer + m_TriangleData.nStart
		);

	if( m_bColors )
	{
		const vfloat32* pColorBuffer = reinterpret_cast<vfloat32*>(
			m_hColorBuffer->GetDataAddress());
		//const vfloat32* pColorBuffer = reinterpret_cast<vfloat32*>(
		//	m_ColorData.hBuffer->GetDataAddress());
		//pColorBuffer += m_ColorData.nStart;

		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(
			4,
			GL_FLOAT,
			m_ColorFormat.GetStride() * sizeof(vfloat32),
			//m_ColorData.nStride * sizeof(vfloat32),
			pColorBuffer + m_ColorFormat.GetFirstIndex()
			//pColorBuffer + m_ColorData.nStart
			);
	}

	if( m_bTexCoords )
	{
		const vfloat32* pTexCoordBuffer = reinterpret_cast<vfloat32*>(
			m_hTexCoordBuffer->GetDataAddress());
		//const vfloat32* pTexCoordBuffer = reinterpret_cast<vfloat32*>(
		//	m_TexCoordData.hBuffer->GetDataAddress());

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(
			2, 
			GL_FLOAT, 
			m_TexCoordFormat.GetStride() * sizeof(vfloat32),
			//m_TexCoordData.nStride * sizeof(vfloat32), 
			pTexCoordBuffer + m_TexCoordFormat.GetFirstIndex()
			//pTexCoordBuffer + m_TexCoordData.nStart
			);
	}

	glDrawArrays(m_PrimitiveType, 0, m_CoordinateFormat.GetCount());
	//glDrawArrays(m_PrimitiveType, 0, m_TriangleData.nCount);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//for(vuint nVertex = 0; nVertex < cnVertexCount; nVertex++)
	//{
	//	if( m_bColors )
	//	{
	//		glColor4f(
	//			GetVertexVal(pColorBuffer, m_ColorData.nStride, nVertex, 0),
	//			GetVertexVal(pColorBuffer, m_ColorData.nStride, nVertex, 1),
	//			GetVertexVal(pColorBuffer, m_ColorData.nStride, nVertex, 2),
	//			GetVertexVal(pColorBuffer, m_ColorData.nStride, nVertex, 3)
	//			);
	//	}

	//	if( m_bTexCoords )
	//	{
	//		glTexCoord2f(
	//		GetVertexVal(pTexCoordBuffer, m_TexCoordData.nStride, nVertex, 0),
	//		GetVertexVal(pTexCoordBuffer, m_TexCoordData.nStride, nVertex, 1)
	//		);
	//	}

	//	glVertex3f(
	//		GetVertexVal(pBuffer, m_TriangleData.nStride, nVertex, X_AXIS),
	//		GetVertexVal(pBuffer, m_TriangleData.nStride, nVertex, Y_AXIS),
	//		GetVertexVal(pBuffer, m_TriangleData.nStride, nVertex, Z_AXIS)
	//		);

	//}
	//glEnd();
}

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------