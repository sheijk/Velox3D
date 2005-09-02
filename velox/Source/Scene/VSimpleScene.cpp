#include <V3d/Scene/VSimpleScene.h>
#include <v3d/Scene/VSceneModelPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;

VSimpleScene::VSimpleScene()
{
}

VSimpleScene::~VSimpleScene()
{
}

VSimpleScene::Id VSimpleScene::Add(const graphics::VModelMesh& in_Mesh)
{
	vout << "added mesh " << vendl;
	return m_VisibleObjects.Add(in_Mesh);
}

VSimpleScene::Id VSimpleScene::Add(const graphics::VModel& in_Model)
{
	vout << "added model" << vendl;
	return m_VisibleObjects.Add(in_Model);
}

void VSimpleScene::Remove(Id in_Id)
{
	vout << "removed model" << vendl;
	m_VisibleObjects.Remove(in_Id);
}
void VSimpleScene::Add(scene::VSceneModelPart* in_pModelPart)
{
	m_ModelParts.push_back(in_pModelPart);
}

void VSimpleScene::Remove(scene::VSceneModelPart* in_pModelPart)
{
	m_ModelParts.remove(in_pModelPart);
}

void VSimpleScene::UpdateVisibleObjects()
{
	ModelList::iterator i = m_ModelParts.begin();

	for(; i != m_ModelParts.end(); ++i)
	{
		(*i)->Update();
	}
}

VRenderList& VSimpleScene::GetRenderList()
{
	return m_VisibleObjects;
}

void VSimpleScene::Activate()
{
}

void VSimpleScene::Deactivate()
{
}

vbool VSimpleScene::IsReady() const
{
	return true;
}

vuint VSimpleScene::DependencyCount() const
{
	return 0;
}

IVPart::Dependency VSimpleScene::GetDependencyInfo(vuint in_nIndex) const
{
	V3D_THROW(VException, "No dependencies");
}

void VSimpleScene::Send(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	using std::string;
	using utils::VStringValue;

	if( in_pAnswer == 0 || ! in_Message.HasProperty("type") )
		return;

	string type = in_Message.Get("type").Get<string>();

	if( type == "getSettings" )
	{
		in_pAnswer->AddProperty("count", VStringValue(m_VisibleObjects.MeshCount()));
	}
}

std::string VSimpleScene::GetDefaultId()
{
	return "scene";
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
