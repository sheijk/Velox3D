#ifndef V3D_VPLANEMESHPART_2005_10_15_H
#define V3D_VPLANEMESHPART_2005_10_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/VMeshPartBase.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Displays a plane at y = -1 in the area x,z in [-size, size]
 *
 * @author sheijk
 */
class VPlaneMeshPart : public scene::VMeshPartBase
{
public:
	VPlaneMeshPart(vfloat32 in_fSize);
	VPlaneMeshPart(vfloat32 in_fSize, const std::string& in_strMaterialResource);

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;

private:
	vfloat32 m_fSize;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VPLANEMESHPART_2005_10_15_H
