#ifndef V3D_VPLANEMESH_05_02_11_H
#define V3D_VPLANEMESH_05_02_11_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
#include <V3d/Graphics/Geometry/VTexCoord2f.h>
#include <V3d/Graphics/VBuffer.h>
#include <V3d/Graphics/Geometry/VGeometryData.h>
#include <V3d/Math.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * @author: ins
 */
template<typename VertexStructure>
class VPlaneMesh : public VGeometryData<VertexStructure>
{
	vfloat32	m_fDistance;
	vfloat32	m_fVisSize;
	VVector3f	m_Normal;

public:
	VPlaneMesh(
		vfloat32 in_fNormalX,
		vfloat32 in_fNormalY,
		vfloat32 in_fNormalZ,
		vfloat32 in_fDistance,
		vfloat32 in_fVisSize = 10.0f);
		

	~VPlaneMesh() {};

	void	GenerateCoordinates();
	void	GenerateTexCoords();

};

#include "VPlaneMesh.inl"

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VPLANEMESH_05_02_11_H