/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/IVRenderStepPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Scene/VSimpleShooting.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace entity;

IVRenderStepPart::IVRenderStepPart() :
	m_pShooting(VPartDependency::Neighbour, RegisterTo())
{
	m_pOutputDevice = 0;
}

IVRenderStepPart::~IVRenderStepPart()
{
}

graphics::IVDevice* IVRenderStepPart::GetPredecessorDevice() const
{
	return m_pOutputDevice;
}

graphics::IVDevice* IVRenderStepPart::GetOutputDevice() const
{
	return m_pOutputDevice;
}

void IVRenderStepPart::SetOutputDevice(graphics::IVDevice* in_OutputDevice)
{
	m_pOutputDevice = in_OutputDevice;
}

void IVRenderStepPart::OnActivate()
{
	if( m_pShooting.IsConnected() != 0 )
		m_pShooting->Add(this);
}

void IVRenderStepPart::OnDeactivate()
{
	if( m_pShooting.IsConnected() != 0 )
		m_pShooting->Remove(this);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

