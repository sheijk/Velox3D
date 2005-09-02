#ifndef V3D_VSCENEMODELPART_2005_05_22_H
#define V3D_VSCENEMODELPART_2005_05_22_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Scene/VSimpleScene.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Graphics/VModel.h>
#include <v3dLib/EntityParts/VRigidBodyPart.h>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VSceneModelPart : public entity::VPartBase
{
public:
	VSceneModelPart(const graphics::VModel& in_Model);

	void AddModelMesh(
		VStringParam in_strMeshResource, 
		VStringParam in_strMaterialResource);
	
	void AddModelMesh(const graphics::VModelMesh in_ModelMesh);

	void RemoveAllMeshes();
	graphics::VModel& GetModel();

    // derived from IVPart:
	virtual void Activate();
	virtual void Deactivate();

	virtual void Send(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer = 0);

	void Update();

	static std::string GetDefaultId();

private:
	graphics::VModel m_Model;
	scene::VSimpleScene::Id m_Id;
	entity::VPartConnection<VSimpleScene> m_pParent;
	

	entity::VPartConnection<entity::VRigidBodyPart> m_RigidBodyPart;
	std::string m_strMeshRes;
	std::string m_strMatRes;
	
	std::string m_strModel;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VSCENEMODELPART_2005_05_22_H
