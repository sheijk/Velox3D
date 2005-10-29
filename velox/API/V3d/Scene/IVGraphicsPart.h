#ifndef V3D_IVGRAPHICSPART_2005_09_22_H
#define V3D_IVGRAPHICSPART_2005_09_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
#include <V3d/Core/RangeIter.h>

namespace v3d { namespace graphics {
	class IVCamera;
}} // namespace v3d::graphics

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVShapePart;

/**
 * A part of a scene representing a graphical part which may have child parts
 *
 * @author sheijk
 */
class IVGraphicsPart : public entity::IVPart
{
public:
	virtual ~IVGraphicsPart() {}

	/**
	 * Called in regular intervals. Use this method to update lod settings, do
	 * culling etc. No guarantees are made about timing. Thus do not use this
	 * method for animation! Use the entity part update system 
	 * (-> VUpdateablePart, VUpdateManagerPart) instead for reliable updating
	 * and animation
	 */
	virtual void UpdateAndCull(const graphics::IVCamera& in_Camera) = 0;

	/**
	 * Returns all shapes in this part and in child parts to be rendered.
	 * UpdateAndCull is guaranteed to be called at least once before this
	 * method (but there is no guarantee about the frequency of updates, thus
	 * UpdateAndCull may be called more than once per GetVisibleMeshes or the
	 * other way round
	 */
	virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const = 0;

	//const IVBoundingVolume& GetBoundingVolume() const = 0;

	static std::string GetDefaultId() { return "v3d.scene.graphics"; }
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::IVGraphicsPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_IVGRAPHICSPART_2005_09_22_H
