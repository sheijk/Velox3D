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
	VPlaneMeshPart(vfloat32 in_fSize = 2.0f);
	VPlaneMeshPart(vfloat32 in_fSize, const std::string& in_strMaterialResource);

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
private:
	vfloat32 m_fSize;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VPlaneMeshPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VPLANEMESHPART_2005_10_15_H
