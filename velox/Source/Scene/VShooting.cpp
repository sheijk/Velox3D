#include <V3d/Scene/VShooting.h>
//-----------------------------------------------------------------------------

#include <V3d/Scene/VSimpleScene.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VShooting::VShooting(graphics::IVDevice* in_pDevice, IVRenderAlgorithm* in_pAlgorithm)
{
	m_pScene = 0;
	m_pRenderList = 0;
	m_pRenderTarget = in_pDevice;
	m_pRenderAlgorithm.Assign(in_pAlgorithm);
}

void VShooting::Cull()
{
	V3D_ASSERT(m_pScene != 0);

	m_pScene->UpdateVisibleObjects();
}

void VShooting::Render()
{
	V3D_ASSERT(m_pRenderList != 0);
	V3D_ASSERT(m_pRenderTarget != 0);

	m_pRenderAlgorithm->Render(*m_pRenderTarget, *m_pRenderList);
}

void VShooting::Activate()
{
}

void VShooting::Deactivate()
{
}

void VShooting::TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part)
{
	m_pScene = in_Part.Convert<VSimpleScene>();
	if( m_pScene )
	{
		m_pRenderList = &m_pScene->GetRenderList();
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
