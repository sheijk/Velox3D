#include <V3d/Scene/VSimpleShooting.h>
//-----------------------------------------------------------------------------

#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Scene/IVShapePart.h>

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace graphics;
using namespace entity;

VSimpleShooting::VSimpleShooting() :
	m_pScene(VPartDependency::Neighbour, RegisterTo())
{
	m_pDevice = 0;
	m_pCamera = 0;
	m_bActive = false;
}

VSimpleShooting::VSimpleShooting(VPartDependency::Location in_SceneLocation,
				const std::string& in_SceneId,
				VPartDependency::Condition in_SceneCondition)
				:
	m_pScene(in_SceneLocation, in_SceneId, in_SceneCondition, RegisterTo())
{
	m_pDevice = 0;
	m_pCamera = 0;
	m_bActive = false;
}

void VSimpleShooting::SetRenderTarget(graphics::IVDevice* in_pDevice)
{
	m_pDevice = in_pDevice;
	SetupRenderSteps();
}

graphics::IVDevice* VSimpleShooting::GetRenderTarget() const
{
	return m_pDevice;
}

void VSimpleShooting::SetCamera(graphics::IVCamera* in_pCamera)
{
	m_pCamera = in_pCamera;
}

graphics::IVCamera* VSimpleShooting::GetCamera() const
{
	return m_pCamera;
}

void VSimpleShooting::UpdateAndCull()
{
	V3D_ASSERT(m_bActive);

	if( m_pScene.IsConnected() )
		m_pScene->UpdateAndCull(*m_pCamera);
}

void VSimpleShooting::Render()
{
	V3D_ASSERT(m_bActive);
	V3D_ASSERT(m_pDevice != 0);

	if( ! m_pScene.IsConnected() )
		return;

	if( m_RenderSteps.size() > 0 )
	{
		IVDevice* activeDevice = m_RenderSteps.front()->GetOutputDevice();

		activeDevice->BeginScene();

		//if( m_RenderSteps.front()->GetOutputDevice() != activeDevice )
		//{
		//	activeDevice->EndScene(IVDevice::NoFlip);
		//	activeDevice = m_RenderSteps.front()->GetOutputDevice();
		//	activeDevice->BeginScene();
		//}

		if( m_pCamera != 0 )
			m_pCamera->ApplyTo(*activeDevice);

		for(vuint stepNum = 0; stepNum < m_RenderSteps.size(); ++stepNum)
		{
			IVRenderStepPart* renderStep = m_RenderSteps[stepNum];

			if( activeDevice != renderStep->GetOutputDevice() )
			{
				activeDevice->EndScene();
				activeDevice = renderStep->GetOutputDevice();
				activeDevice->BeginScene();
			}

			renderStep->Render(m_pScene.Get());
		}

		//if( activeDevice != m_pDevice )
		//{
			activeDevice->EndScene();
		//}
	}
	else
	{
		VRangeIterator<const IVShapePart> shape = m_pScene->GetVisibleMeshes();
		while( shape.HasNext() )
		{
			const IVMaterial& material = shape->GetMaterial();

			for(vuint pass = 0; pass < material.PassCount(); ++pass)
			{
				math::VRBTransform transform = shape->GetModelTransform();

				m_pDevice->SetMatrix(IVDevice::ModelMatrix, transform.AsMatrix());

				ApplyMaterial(*m_pDevice, &material.GetPass(pass));
				shape->SendGeometry(*m_pDevice);
			}

			++shape;
		}
	}
}

void VSimpleShooting::SetupRenderSteps()
{
	if( m_RenderSteps.size() <= 0 )
		return;

	// last step renders to final device
	m_RenderSteps.back()->SetOutputDevice(m_pDevice);

	// each step renders to "input" device of previous step
	for(vuint stepNum = static_cast<vuint>(m_RenderSteps.size())-1; stepNum > 0; --stepNum)
	{
		IVRenderStepPart* prev = m_RenderSteps[stepNum-1];
		IVRenderStepPart* next = m_RenderSteps[stepNum];

		prev->SetOutputDevice(next->GetPredecessorDevice());
	}
}

void VSimpleShooting::Add(IVRenderStepPart* in_pRenderStep)
{
	V3D_ASSERT(in_pRenderStep != 0);

	m_RenderSteps.push_back(in_pRenderStep);
	SetupRenderSteps();
}

void VSimpleShooting::Remove(IVRenderStepPart* in_pRenderStep)
{
	RenderStepArray::iterator step = std::find(m_RenderSteps.begin(), 
		m_RenderSteps.end(), in_pRenderStep);

	if( step != m_RenderSteps.end() )
		m_RenderSteps.erase(step);
}

void VSimpleShooting::Activate()
{
	m_bActive = true;
	SetupRenderSteps();
}

void VSimpleShooting::Deactivate()
{
	m_bActive = false;
}

vbool VSimpleShooting::IsActive() const
{
	return m_bActive;
}

namespace {
	entity::VPartParser<VSimpleShooting> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
