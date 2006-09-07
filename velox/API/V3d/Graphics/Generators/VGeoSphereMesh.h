/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VGEOSPHERE_H
#define V3D_VGEOSPHERE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
#include <V3d/Graphics/Geometry/VTexCoord2f.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <V3d/Graphics/VBuffer.h>
#include <V3d/Core/VIOStream.h>

#include <cmath>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {

template<typename VertexStructure>
class VGeoSphereMesh
{
	struct Triangle
	{
        VVertex3f tri[3];

		Triangle()
		{
			tri[0] = VVector3f(0.0f, 0.0f, 0.0f);
			tri[1] = VVector3f(0.0f, 0.0f, 0.0f);
			tri[2] = VVector3f(0.0f, 0.0f, 0.0f);
		}

		Triangle( VVertex3f a, VVertex3f b, VVertex3f c)
		{
			tri[0]=a;
			tri[1]=b;
			tri[2]=c;
		}
	};

	struct TriangleColor
	{
		v3d::graphics::VColor4f color[3];

		TriangleColor()
		{
			color[0] = color[1] = color[2] = VColor4f(0.0f, 0.0f, 0.0f, 0.0f);
		}

		TriangleColor(
			v3d::graphics::VColor4f a,
			v3d::graphics::VColor4f b,
			v3d::graphics::VColor4f c
			)
		{
            color[0] = a;
			color[1] = b;
			color[2] = c;
		}
	};

	vfloat32	m_fRadius;
	vuint		m_nLevel;

	static vuint	CalculateVertexNumber( vuint in_nLevel );

	VVertex3f		Normalize(VVertex3f in_Vector);
	VVertex3f		GetMidPoint(VVertex3f in_vecA, VVertex3f in_vecB );
public:
    
	v3d::graphics::VBuffer<VertexStructure>	buffer;

    VGeoSphereMesh( vfloat32 in_fRadius, vuint in_nLevel )
        : m_fRadius(in_fRadius), m_nLevel(in_nLevel), buffer(new VertexStructure[CalculateVertexNumber(in_nLevel)], CalculateVertexNumber(in_nLevel))
	{
    }

	~VGeoSphereMesh() {};

	void	CreateCoordinates();
	void	CreateTextureCoordinates();
	void	CreateColor(v3d::graphics::VColor4f in_Colors[8] );
};

#include "VGeoSphereMesh.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VGEOSPHERE_H
