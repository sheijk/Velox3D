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
 * Displays a plane at y = -1 in the area x,z in [-size, size] <- quark..
 *
 * @author sheijk
 */
class VPlaneMeshPart : public scene::VMeshPartBase
{
public:
	VPlaneMeshPart(vfloat32 in_fSize = 2.0f);
	VPlaneMeshPart(vfloat32 in_fSize, const std::string& in_strMaterialResource);

	VVector3f GetPosition() const;
	void SetPosition(const VVector3f& in_Position);

	VVector3f GetRight() const;
	void SetRight(const VVector3f& in_Right);

	VVector3f GetUp() const;
	void SetUp(const VVector3f& in_Up);

	/** Changes the position in a way such that the plane will be centered
	 * at the given position
	 */
	void CenterAt(const VVector3f& in_Center);

	// overidden
	virtual void SendGeometry(graphics::IVDevice& in_Device) const;
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	VVector3f m_Position;
	VVector3f m_Right;
	VVector3f m_Up;

	vfloat32 m_fSize;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VPlaneMeshPart, v3d::scene::IVShapePart);
//-----------------------------------------------------------------------------
#endif // V3D_VPLANEMESHPART_2005_10_15_H