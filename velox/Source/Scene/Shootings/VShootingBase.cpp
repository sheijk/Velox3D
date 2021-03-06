/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Shootings/VShootingBase.h>
//-----------------------------------------------------------------------------
#include <V3d/Scene/IVShapePart.h>
#include <V3d/Graphics/Misc/MiscUtils.h>
#include <V3d/Scene/VDefaultRenderStepPart.h>
#include <V3d/Scene/IVLightManager.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VShootingBase::VShootingBase() : 
	m_pLightManager(
		entity::VNodeDependency::Optional, 
		RegisterTo()),
	m_pParentShooting(
		entity::VNodeDependency::Optional,
		RegisterTo())
{
	m_bActive = false;
}

/**
 * d'tor
 */
VShootingBase::~VShootingBase()
{
}

void VShootingBase::Add(IVRenderStepPart* in_pRenderStep)
{
	V3D_ASSERT(in_pRenderStep != 0);

	m_RenderSteps.push_back(in_pRenderStep);
	SetupRenderSteps();
}

void VShootingBase::Remove(IVRenderStepPart* in_pRenderStep)
{
	RenderStepArray::iterator step = std::find(m_RenderSteps.begin(), 
		m_RenderSteps.end(), in_pRenderStep);

	if( step != m_RenderSteps.end() )
		m_RenderSteps.erase(step);
}

void VShootingBase::AddPreShooting(IVShooting* in_pPreShooting)
{
	m_PreShootings.push_back(in_pPreShooting);
}

void VShootingBase::RemovePreShooting(IVShooting* in_pPreShooting)
{
	ShootingArray::iterator preShooting = std::find(
		m_PreShootings.begin(), m_PreShootings.end(), in_pPreShooting);

	if( preShooting != m_PreShootings.end() )
		m_PreShootings.erase(preShooting);
}

void VShootingBase::SetupRenderSteps()
{
	if( m_RenderSteps.size() <= 0 )
		return;

	// last step renders to final device
	m_RenderSteps.back()->SetOutputDevice(GetRenderTarget());

	// each step renders to "input" device of previous step
	for(vuint stepNum = static_cast<vuint>(m_RenderSteps.size())-1; stepNum > 0; --stepNum)
	{
		IVRenderStepPart* prev = m_RenderSteps[stepNum-1];
		IVRenderStepPart* next = m_RenderSteps[stepNum];

		prev->SetOutputDevice(next->GetPredecessorDevice());
	}
}

void VShootingBase::UpdateAndCullPreShootings()
{
	VRangeIterator<IVShooting> preShooting = CreateDerefBeginIterator<IVShooting>(m_PreShootings);

	while( preShooting.HasNext() )
	{
		preShooting->UpdateAndCull();
		++preShooting;
	}
}

void VShootingBase::UpdateAndCull()
{
	//V3D_ASSERT(m_bActive);

	//UpdateAndCullPreShootings();

	if( GetScene() != 0 && GetCamera() != 0 )
		GetScene()->UpdateAndCull(*GetCamera());
}

void VShootingBase::RenderPreShootings()
{
	VRangeIterator<IVShooting> preShooting = CreateDerefBeginIterator<IVShooting>(m_PreShootings);

	while( preShooting.HasNext() )
	{
		preShooting->UpdateAndCull();
		preShooting->Render();
		++preShooting;
	}
}

void VShootingBase::Render()
{
	if( GetState() != Active )
		V3D_THROW(VException, "VShootingBase.Render called while shooting part not active");

	graphics::IVDevice* pDevice = GetRenderTarget();
	if( pDevice == 0 )
		V3D_THROW(VException, "Shooting has no device, cannot render");

	RenderPreShootings();
	UpdateAndCull();

	if( GetScene() == 0 )
		return;

	VRangeIterator<IVRenderStepPart> renderStep = CreateDerefBeginIterator<IVRenderStepPart>(m_RenderSteps);

	if( m_RenderSteps.size() == 0 )
	{
		static VDefaultRenderStepPart defaultRenderStep;
		defaultRenderStep.SetOutputDevice(pDevice);

		renderStep = CreateSingleValueIterator<IVRenderStepPart>(&defaultRenderStep);
	}

	graphics::IVDevice* activeDevice = renderStep->GetOutputDevice();

	activeDevice->BeginScene();

	if( GetCamera() != 0 )
		GetCamera()->ApplyTo(*activeDevice);

	if( m_pLightManager.IsConnected() )
		m_pLightManager->ApplyLights(activeDevice, NULL);

	while( renderStep.HasNext() )
	{
		if( activeDevice != renderStep->GetOutputDevice() )
		{
			activeDevice->EndScene();
			activeDevice = renderStep->GetOutputDevice();
			activeDevice->BeginScene();

			if( m_pLightManager.IsConnected() )
				m_pLightManager->ApplyLights(activeDevice, NULL);
		}

		renderStep->Render(GetScene());

		++renderStep;
	}

	activeDevice->EndScene();
}

void VShootingBase::OnActivate()
{
	m_bActive = true;
	SetupRenderSteps();

	V3D_ASSERT(m_pParentShooting.Get() != this);

	if( m_pParentShooting.IsConnected() )
		m_pParentShooting->AddPreShooting(this);
}

void VShootingBase::OnDeactivate()
{
	m_bActive = false;

	if( m_pParentShooting.IsConnected() )
		m_pParentShooting->RemovePreShooting(this);
}

vbool VShootingBase::IsActive() const
{
	return m_bActive;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

