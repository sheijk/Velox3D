/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
#include <V3d/Scene/Shapes/VSkyDomeGenerator.h>
#include <V3d/Math.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::math;
VSkyDomeGenerator::VSkyDomeGenerator(
									 Mode in_Mode,
									 vuint in_Slices,
									 vuint in_Sides,
									 vuint in_DivSteps,
									 vfloat32 in_fRadius,
									 vfloat32 in_fWidth,
									 vfloat32 in_fHeight)
									 : m_Mode(in_Mode),
									 m_nSides(in_Sides),
									 m_nSlices(in_Slices),
									 m_DivSteps(in_DivSteps),
									 m_fRadius(in_fRadius),
									 m_fWidth(in_fWidth),
									 m_fHeight(in_fHeight)
{
	m_pVertexBuffer = 0;
	m_pIndexBuffer = 0;

	Generate();
}

void VSkyDomeGenerator::Generate()
{ 
	if(m_Mode == Dome)
		GenerateVertices();
	else
		GeneratePlaneVertices();
}

void VSkyDomeGenerator::GenerateVertices()
{
	m_nVertexCount = (m_nSlices+ 1) * (m_nSides + 1);
	m_nIndexCount = m_nSlices * (m_nSides + 1) * 2;

	m_pVertexBuffer = new vfloat32 [m_nVertexCount * 3];
	m_pIndexBuffer = new vuint[m_nIndexCount];

	vfloat32 polyAng = (2.0f * math::Pi() / m_nSides);
	vfloat32 angle = 0.0f;
	vfloat32 x, y, z;

	for (vuint j = 0; j <= m_nSlices; j++)
	{
		vfloat32 val = static_cast<vfloat32>(j) / static_cast<vfloat32>(m_nSlices);
		angle = val * val * math::Pi() * 0.5f;
		for (vuint i = 0; i <= m_nSides; i++)
		{						
			x = cos(i * polyAng) * cos(angle);
			y = sin(angle);
			z = sin(i * polyAng) * cos(angle);

			m_pVertexBuffer[3*(j * (m_nSides + 1) + i )+ 0] = x * m_fRadius;
			m_pVertexBuffer[3*(j * (m_nSides + 1) + i )+ 1] = y * m_fRadius;	
			m_pVertexBuffer[3*(j * (m_nSides + 1) + i )+ 2] = z * m_fRadius;
		}
	}

	vuint nCount = 0;
	for (vuint j = 1; j <= m_nSlices; j++)
	{
		for (vuint i = 0; i <= m_nSides; i++)
		{			
			m_pIndexBuffer[nCount++] = j * (m_nSides + 1) + i;
			m_pIndexBuffer[nCount++] = (j - 1) * (m_nSides + 1) + i;
		}
	}
}

VSkyDomeGenerator::~VSkyDomeGenerator()
{
	delete [] m_pVertexBuffer;
	delete [] m_pIndexBuffer;
}

vuint VSkyDomeGenerator::GetVertexCount()
{
	return m_nVertexCount;
}

vfloat32* VSkyDomeGenerator::GetVertexBuffer()
{
	return m_pVertexBuffer;
}

vuint* VSkyDomeGenerator::GetIndexBuffer()
{
	return m_pIndexBuffer;
}

void VSkyDomeGenerator::SetRadius(vfloat32 in_fRadius)
{
	m_fRadius = in_fRadius;
}

void VSkyDomeGenerator::SetSides(vuint in_Sides)
{
	m_nSides = in_Sides;
}

void VSkyDomeGenerator::SetSlices(vuint in_Slices)
{
	m_nSlices = in_Slices;
}

vfloat32 VSkyDomeGenerator::GetRadius() const
{
	return m_fRadius;
}

vuint VSkyDomeGenerator::GetSlices() const 
{
	return m_nSlices;
}

vuint VSkyDomeGenerator::GetSides() const 
{
	return m_nSides;
}
void VSkyDomeGenerator::GeneratePlaneVertices()
{

	m_pVertexBuffer = new vfloat32[3*((m_DivSteps+1) * (m_DivSteps+1))];
	m_pIndexBuffer = new vuint[2*3*m_DivSteps*m_DivSteps];

	vuint nVertexCount = 0;
	vuint nIndexCount = 0;

	vfloat32 planeSize = 2 * gmtl::Math::sqrt(m_fWidth*m_fWidth - m_fHeight * m_fHeight);
	vfloat32 planeDelta = planeSize / m_DivSteps;
	VVector3f vertex;

	for(vuint i = 0; i <= m_DivSteps; i++)
	{
		for(vuint j = 0; j <= m_DivSteps; j++)
		{
			vfloat32 factor = (sinf(3.14f * (vfloat32) j / (vfloat32)m_DivSteps));
			vertex[0] = (-0.5f * planeSize) + j*planeDelta;
			vertex[2] = (-0.5f * planeSize) + i*planeDelta;

			vfloat32 x_height = vertex[0] * vertex[0] / m_fWidth;
			vfloat32 z_height = vertex[2] * vertex[2] / m_fWidth;
			//vfloat32 height = x_height + (z_height * factor);
			vfloat32 height = x_height + (z_height);

			m_pVertexBuffer[nVertexCount++] = vertex[0];
			m_pVertexBuffer[nVertexCount++] = -height + m_fWidth;
			m_pVertexBuffer[nVertexCount++] = vertex[2];
		}
	}
	m_nVertexCount = nVertexCount / 3;

	for(vuint i = 0; i < m_DivSteps;  i++)
	{
		for(vuint j = 0; j < m_DivSteps; j++)
		{
			int start = (i*(m_DivSteps+1) +j);

			m_pIndexBuffer[nIndexCount] = start;
			nIndexCount++;
			m_pIndexBuffer[nIndexCount] = start+1;
			nIndexCount++;
			m_pIndexBuffer[nIndexCount] = start+m_DivSteps+1;
			nIndexCount++;

			m_pIndexBuffer[nIndexCount] = start+1;
			nIndexCount++;
			m_pIndexBuffer[nIndexCount] = start+m_DivSteps + 2;
			nIndexCount++;
			m_pIndexBuffer[nIndexCount] = start+m_DivSteps + 1;
			nIndexCount++;
		}
	}
	m_nIndexCount = nIndexCount;
}

vuint VSkyDomeGenerator::GetIndexCount()
{
	return m_nIndexCount;
}
//-----------------------------------------------------------------------------
}} // namespace v3d::v3d::scene
//-----------------------------------------------------------------------------

