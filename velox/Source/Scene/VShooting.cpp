#include <V3d/Scene/VShooting.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>

#include <V3d/Scene/VSimpleScene.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;

VShooting::VShooting(graphics::IVDevice* in_pDevice, IVRenderAlgorithm* in_pAlgorithm)
{
	m_pScene = 0;
	m_pRenderList = 0;
	m_pRenderTarget = in_pDevice;
	m_pRenderAlgorithm.Assign(in_pAlgorithm);
	
	m_bActive = false;
}	

void VShooting::Cull()
{
//	V3D_ASSERT(m_pScene != 0);

	if( m_pScene != 0 )
		m_pScene->UpdateVisibleObjects();
	else
		vout << "error in cull" << vendl;
}

void VShooting::Render()
{
//	V3D_ASSERT(m_pRenderList != 0);
//	V3D_ASSERT(m_pRenderTarget != 0);

	if( m_pRenderTarget != 0 && m_pRenderAlgorithm.Get() != 0 && m_pRenderList != 0 )
		m_pRenderAlgorithm->Render(*m_pRenderTarget, *m_pRenderList);
	else
		vout << "error in render" << vendl;
}

vbool VShooting::IsActive() const
{
	return m_bActive;
}

void VShooting::Activate()
{
	m_bActive = true;
}

void VShooting::Deactivate()
{
	m_bActive = false;
}

void VShooting::Connect(
	Location in_Location, const std::string& in_Id, IVPart& in_Part)
{
	//FIXED, should be done correctly --ins
	//if an other part is being connected first it should be checked if it's a scene

	if(in_Part.IsOfType<VSimpleScene>())
	{
		m_pScene = in_Part.Convert<VSimpleScene>();
		if( m_pScene )
		{
			m_pRenderList = &m_pScene->GetRenderList();
		}
		else
		{
			vout << "scene not valid" << vendl;
		}
	}
}

void VShooting::Disconnect(
	Location in_Location, const std::string& in_Id, IVPart& in_Part)
{
}

vbool VShooting::IsReady() const
{
	return m_pScene != 0;
}

vuint VShooting::DependencyCount() const
{
	return 1;
}

IVPart::Dependency VShooting::GetDependencyInfo(vuint in_nIndex) const
{
	V3D_ASSERT(in_nIndex == 0);

	Dependency dependency;
	dependency.id = IVScene::GetDefaultId();
	dependency.location = VPartDependency::Neighbour;

	return dependency;
}

std::string VShooting::GetDefaultId()
{
	return "shooting";
}

//void VShooting::TellNeighbourPart(const std::string& in_Id, IVPart& in_Part)
//{
//	m_pScene = in_Part.Convert<VSimpleScene>();
//	if( m_pScene )
//	{
//		m_pRenderList = &m_pScene->GetRenderList();
//	}
//}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
