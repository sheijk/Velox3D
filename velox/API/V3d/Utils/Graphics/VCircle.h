#ifndef V3D_VCIRCLE_H
#define V3D_VCIRCLE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Utils/Graphics/VVector3f.h>
#include <v3d/Utils/Graphics/VTexCoord2f.h>
#include <v3d/Graphics/VBuffer.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
namespace graphics {
//-----------------------------------------------------------------------------
template<typename VertexStructure>
class VCircle
{
    vfloat32	m_fRadius;
	vint		m_nDetail;

	static vuint CalculateVertexNumber(vuint in_nDetail);

	public:
        v3d::graphics::VBuffer<VertexStructure>	buffer;

        VCircle( vfloat32 in_fRadius, vuint in_nDetail )
            : m_fRadius(in_fRadius), m_nDetail(in_nDetail), buffer(new VertexStructure[CalculateVertexNumber(in_nDetail)], CalculateVertexNumber(in_nDetail))
				{
				}

		~VCircle() {};

		void	CreateCoordinates();
		void	CreateTextureCoordinates();
};
//-----------------------------------------------------------------------------
#include "VCircle.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace utils
} // namespace v3d
#endif // V3D_VCIRCLE_H