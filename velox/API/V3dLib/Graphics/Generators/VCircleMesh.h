#ifndef V3D_VCIRCLE_H
#define V3D_VCIRCLE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3dLib//Graphics/Geometry/VVertex3f.h>
#include <V3dLib/Graphics/Geometry/VTexCoord2f.h>
#include <v3d/Graphics/VBuffer.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
template<typename VertexStructure>
class VCircleMesh
{
    vfloat32	m_fRadius;
	vint		m_nDetail;

	static vuint CalculateVertexNumber(vuint in_nDetail);

	public:
        v3d::graphics::VBuffer<VertexStructure>	buffer;

        VCircleMesh( vfloat32 in_fRadius, vuint in_nDetail )
            : m_fRadius(in_fRadius), m_nDetail(in_nDetail), buffer(new VertexStructure[CalculateVertexNumber(in_nDetail)], CalculateVertexNumber(in_nDetail))
				{
				}

		~VCircleMesh() {};

		void	CreateCoordinates();
		void	CreateTextureCoordinates();
};
//-----------------------------------------------------------------------------
#include "VCircleMesh.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
#endif // V3D_VCIRCLE_H