#ifndef V3D_VSIMPLESCENE_2005_05_22_H
#define V3D_VSIMPLESCENE_2005_05_22_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Scene/IVScene.h>
#include <V3d/Scene/IVRenderList.h>
#include <V3d/Scene/VRenderList.h>

#include <V3d/Graphics/VModel.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VSimpleScene : public IVScene
{
public:
	typedef IVRenderList::Id Id;

	VSimpleScene();
	virtual ~VSimpleScene();

	Id Add(const graphics::VModelMesh& in_Mesh);
	Id Add(const graphics::VModel& in_Model);
	void Remove(Id in_Id);

	/** 
	* Puts all visible objects to it's associated draw list and removes all
	* invisible objects from it
	*/
	virtual void UpdateVisibleObjects();

	/**
	* Gets the draw list which contains all visible objects of the scene
	*/
	virtual VRenderList& GetRenderList();

	virtual void Activate();
	virtual void Deactivate();

	virtual vbool IsReady() const;
	virtual vuint DependencyCount() const;
	virtual Dependency GetDependencyInfo(vuint in_nIndex) const;

	static std::string GetDefaultId();

private:
	VRenderList m_VisibleObjects;
	Id m_nNextFreeId;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLESCENE_2005_05_22_H
