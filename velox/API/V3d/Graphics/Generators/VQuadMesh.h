/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VQUADMESH_2004_06_18_H
#define V3D_VQUADMESH_2004_06_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/VMeshDescription.h>
#include <V3d/Graphics/Geometry/VGeometryData.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

template<typename VertexStructure>
class VQuadMesh : public VGeometryData<VertexStructure>
{
public:
	VQuadMesh(vfloat32 in_fSize = 1.0f) :
		VGeometryData<VertexStructure>(VMeshDescription::Quads, 4, 0),
		m_fSize(in_fSize)
	{
		GenerateCoordinates();
	}

	void GenerateCoordinates()
	{
		VertexBuffer& vertices(GetVertexBuffer());
		vertices[0].position = VVector3f(-m_fSize, -m_fSize, 0);
		vertices[1].position = VVector3f(-m_fSize,  m_fSize, 0);
		vertices[2].position = VVector3f( m_fSize,  m_fSize, 0);
		vertices[3].position = VVector3f( m_fSize, -m_fSize, 0);
	}

	void GenerateTexCoords()
	{
		VertexBuffer& vertices(GetVertexBuffer());

		vertices[0].texCoords = VTexCoord2f(0, 1);
		vertices[1].texCoords = VTexCoord2f(0, 0);
		vertices[2].texCoords = VTexCoord2f(1, 0);
		vertices[3].texCoords = VTexCoord2f(1, 1);
	}
private:
	vfloat32 m_fSize;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VQUADMESH_2004_06_18_H

