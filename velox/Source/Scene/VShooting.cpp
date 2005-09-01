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

void VShooting::Activate()
{
}

void VShooting::Deactivate()
{
}

void VShooting::Connect(
	Location in_Location, const std::string& in_Id, IVPart& in_Part)
{
	m_pScene = in_Part.Convert<VSimpleScene>();
	if( m_pScene )
	{
		m_pRenderList = &m_pScene->GetRenderList();
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
	dependency.id = GetDefaultId();
	dependency.location = IVPart::Neighbour;

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
