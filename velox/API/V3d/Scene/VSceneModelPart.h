//TODO: add file creation date to file guard
#ifndef V3D_VSCENEMODELPART_2005_05_22_H
#define V3D_VSCENEMODELPART_2005_05_22_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Scene/VSimpleScene.h>

#include <V3d/Entity/IVPart.h>
#include <V3d/Graphics/VModel.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VSceneModelPart : public entity::IVPart
{
public:
	VSceneModelPart(const graphics::VModel& in_Model);

	void AddModelMesh(
		VStringParam in_strMeshResource, 
		VStringParam in_strMaterialResource);

	void RemoveAllMeshes();

	//void RemoveModelMesh(
	//	VStringParam in_strMeshResource, 
	//	VStringParam in_strMaterialResource);

    // dervicd from IVPart:
	virtual void Activate();
	virtual void Deactivate();

	virtual void TellParentPart(const utils::VFourCC& in_Id, IVPart& in_Part);

	static utils::VFourCC GetDefaultId();
private:
	graphics::VModel m_Model;
	VSimpleScene::Id m_Id;
	VSimpleScene* m_pParent;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VSCENEMODELPART_2005_05_22_H
