#ifndef V3D_VCYLINDER_H
#define V3D_VCYLINDER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Graphics/Geometry/VVector3f.h>
#include <V3dLib/Graphics/Geometry/VTexCoord2f.h>
#include <v3d/Graphics/VBuffer.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {

//-----------------------------------------------------------------------------
template<typename VertexStructure>
class VCylinderMesh
{
    vfloat32	m_fRadius;
	vfloat32	m_fHeight;
    vint		m_nDetail;

    static vuint CalculateVertexNumber(vuint in_nDetail);

public:
    v3d::graphics::VBuffer<VertexStructure>	buffer;

    VCylinderMesh( vfloat32 in_fRadius, vfloat32 in_fHeight, vuint in_nDetail )
        : m_fRadius(in_fRadius), m_fHeight(in_fHeight), m_nDetail(in_nDetail), buffer(new VertexStructure[CalculateVertexNumber(in_nDetail)], CalculateVertexNumber(in_nDetail))
    {
    }

	~VCylinderMesh() {};

		void	CreateCoordinates();
		void	CreateTextureCoordinates();
};
//-----------------------------------------------------------------------------
#include "VCylinderMesh.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
#endif // V3D_VCIRCLE_H