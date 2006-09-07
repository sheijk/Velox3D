/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

template <typename VertexStructure>
VPlaneMesh<VertexStructure>::VPlaneMesh(
										vfloat32 in_fNormalX,
										vfloat32 in_fNormalY,
										vfloat32 in_fNormalZ,
										vfloat32 in_fDistance,
										vfloat32 in_fVisSize = 10.0f)
										:m_fDistance(in_fDistance),
                                        VGeometryData<VertexStructure>(
										VMeshDescription::TriangleFan, 4)
{
	m_Normal.Set(0, -in_fNormalX);
	m_Normal.Set(1, -in_fNormalY);
	m_Normal.Set(2, -in_fNormalZ);

	m_fVisSize = in_fVisSize;

}

template <typename VertexStructure> 
void VPlaneMesh<VertexStructure>::GenerateCoordinates()
{
	using namespace v3d::graphics;

	//create orthogonal vector out of n
	VVector3f v(m_Normal.Get(1),m_Normal.Get(0), m_Normal.Get(2));
	//create second one
	//VVector3f u(- v.Get(2), v.Get(1), v.Get(0));

	if(v.Get(0) == m_Normal.Get(0)&& v.Get(1) == m_Normal.Get(1) && v.Get(2) == m_Normal.Get(2))
	{
		v.Set(0, m_Normal.Get(2));
		v.Set(1, m_Normal.Get(1));
		v.Set(2, m_Normal.Get(0));
	}
	VVector3f u = Cross(v,m_Normal);

	//check if all vectors are orthogonal;

	//float s = Dot(m_Normal, v);
	//float t = Dot(m_Normal, u);

	//take our scalar for the plane visualization size and get the points
	VVector3f p0(v.Get(0)*m_fVisSize,v.Get(1)*m_fVisSize, v.Get(2)*m_fVisSize);
	VVector3f p1(-v.Get(0)*m_fVisSize,-v.Get(1)*m_fVisSize, -v.Get(2)*m_fVisSize);

	VVector3f p2(u.Get(0)*m_fVisSize,u.Get(1)*m_fVisSize, u.Get(2)*m_fVisSize);
	//Add(p2,p2,p0);

	VVector3f p3(-u.Get(0)*m_fVisSize,-u.Get(1)*m_fVisSize, -u.Get(2)*m_fVisSize);
	//Add(p3,p3,p1);

	//now scale to distance
	VVector3f translation = m_Normal * m_fDistance;
    	
	//translate
	Add(p0,p0,translation);
	Add(p1,p1,translation);
	Add(p2,p2,translation);
	Add(p3,p3,translation);

	
	//build up vertex mesh
	GetVertexBuffer()[0].position = VVertex3f(p2.Get(0), p2.Get(1), p2.Get(2));
	GetVertexBuffer()[1].position = VVertex3f(p0.Get(0), p0.Get(1), p0.Get(2));
	GetVertexBuffer()[2].position = VVertex3f(p3.Get(0), p3.Get(1), p3.Get(2));
	GetVertexBuffer()[3].position = VVertex3f(p1.Get(0), p1.Get(1), p1.Get(2));
}

template <typename VertexStructure>
void VPlaneMesh<VertexStructure>::GenerateTexCoords()
{
	using namespace v3d::graphics;

	GetVertexBuffer()[0].texCoords = VTexCoord2f(0,0);
	GetVertexBuffer()[1].texCoords = VTexCoord2f(0,1);
	GetVertexBuffer()[2].texCoords = VTexCoord2f(1,1);
	GetVertexBuffer()[3].texCoords = VTexCoord2f(1,0);

}


