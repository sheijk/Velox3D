#ifndef V3D_VNAIVESCENEMANAGERPART_2005_09_22_H
#define V3D_VNAIVESCENEMANAGERPART_2005_09_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVSceneManagerPart.h>
#include <V3d/Entity/VUnconnectedPart.h>

#include <set>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A naive scene manager which simply stores all it's shapes in a flat list
 * and does not do any culling
 *
 * @author sheijk
 */
class VNaiveSceneManagerPart : public entity::VUnconnectedPartAdapter<IVSceneManagerPart>
{
public:
	VNaiveSceneManagerPart();
	virtual ~VNaiveSceneManagerPart();

	virtual void UpdateAndCull(const graphics::IVCamera& in_Camera);
	virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const;

	virtual void Add(IVShapePart* in_pShape);
	virtual void Remove(IVShapePart* in_pShape);

	void Activate();
	void Deactivate();

	static std::string GetDefaultId() { return IVGraphicsPart::GetDefaultId(); }
private:
	typedef	std::set<IVShapePart*> ShapeList;
	ShapeList m_Shapes;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VNAIVESCENEMANAGERPART_2005_09_22_H
