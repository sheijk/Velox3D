#ifndef V3D_VGEOSPHERE_H
#define V3D_VGEOSPHERE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Utils/Graphics/VVector3f.h>
#include <v3d/Utils/Graphics/VTexCoord2f.h>
#include <v3d/Utils/Graphics/VColor4f.h>
#include <v3d/Graphics/VBuffer.h>
#include <v3d/Core/VIOStream.h>

#include <cmath>

//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
namespace graphics {

template<typename VertexStructure>
class VGeoSphere
{
	struct Triangle
	{
        VVector3f tri[3];

		Triangle()
		{
			tri[0] = VVector3f(0.0f, 0.0f, 0.0f);
			tri[1] = VVector3f(0.0f, 0.0f, 0.0f);
			tri[2] = VVector3f(0.0f, 0.0f, 0.0f);
		}

		Triangle( VVector3f a, VVector3f b, VVector3f c)
		{
			tri[0]=a;
			tri[1]=b;
			tri[2]=c;
		}
	};

	struct TriangleColor
	{
		VColor4f color[3];

		TriangleColor()
		{
			color[0] = color[1] = color[2] = VColor4f(0.0f, 0.0f, 0.0f, 0.0f);
		}

		TriangleColor( VColor4f a, VColor4f b, VColor4f c )
		{
            color[0] = a;
			color[1] = b;
			color[2] = c;
		}
	};

	vfloat32	m_fRadius;
	vuint		m_nLevel;

	static vuint	CalculateVertexNumber( vuint in_nLevel );

	VVector3f		Normalize(VVector3f in_Vector);
	VVector3f		GetMidPoint(VVector3f in_vecA, VVector3f in_vecB );
public:
    
	v3d::graphics::VBuffer<VertexStructure>	buffer;

    VGeoSphere( vfloat32 in_fRadius, vuint in_nLevel )
        : m_fRadius(in_fRadius), m_nLevel(in_nLevel), buffer(new VertexStructure[CalculateVertexNumber(in_nLevel)], CalculateVertexNumber(in_nLevel))
	{
    }

	~VGeoSphere() {};

	void	CreateCoordinates();
	void	CreateTextureCoordinates();
	void	CreateColor( VColor4f in_Colors[8] );
};

#include "VGeoSphere.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VGEOSPHERE_H