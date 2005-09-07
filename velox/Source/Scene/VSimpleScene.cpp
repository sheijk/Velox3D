#include <V3d/Scene/VSimpleScene.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VSimpleScene::VSimpleScene()
{
}

VSimpleScene::~VSimpleScene()
{
}

VSimpleScene::Id VSimpleScene::Add(const graphics::VModelMesh& in_Mesh)
{
	return m_VisibleObjects.Add(in_Mesh);
}

VSimpleScene::Id VSimpleScene::Add(const graphics::VModel& in_Model)
{
	return m_VisibleObjects.Add(in_Model);
}

void VSimpleScene::Remove(Id in_Id)
{
	m_VisibleObjects.Remove(in_Id);
}

void VSimpleScene::UpdateVisibleObjects()
{
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

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
