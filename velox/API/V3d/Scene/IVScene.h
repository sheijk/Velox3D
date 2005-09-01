#ifndef V3D_IVSCENE_2005_05_20_H
#define V3D_IVSCENE_2005_05_20_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
#include <V3d/Scene/IVRenderList.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A scene manager
 *
 * @author
 */
class IVScene : public entity::IVPart
{
public:
	//typedef vuint Id;

	IVScene() {}
	virtual ~IVScene() {}

	/** Adds a new object or sub scene */
	//virtual Id Add(const IVScene& in_Scene) = 0;

	/** Removes an object or sub scene */
	//virtual void Remove(Id in_Object) = 0;

	/** 
	 * Puts all visible objects to it's associated draw list and removes all
	 * invisible objects from it
	 */
	virtual void UpdateVisibleObjects() = 0;

	/**
	 * Gets the draw list which contains all visible objects of the scene
	 */
	virtual IVRenderList& GetRenderList() = 0;

	static std::string GetDefaultId() { return "scene"; }

};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_IVSCENE_2005_05_20_H
