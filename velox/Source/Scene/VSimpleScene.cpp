#include <V3d/Scene/VSimpleScene.h>
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

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
