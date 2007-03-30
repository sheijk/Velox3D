/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Updater/IVTimer.h>
#include <windows.h>
//-----------------------------------------------------------------------------
#include "VPerformanceCounter.h"
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace updater{
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */

VPerformanceCounter::VPerformanceCounter()
{
	// register updateable
	IVUpdateable::Register();

	QueryPerformanceFrequency((LARGE_INTEGER*)&(m_iFrequency));
	QueryPerformanceCounter((LARGE_INTEGER*)&m_iLastTick);

	m_fFrameDuration = 0;
}

/**
 * d'tor
 */
VPerformanceCounter::~VPerformanceCounter()
{
}

void VPerformanceCounter::GetTimeDifference()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_iCurrentTick);

	vint64 iDifference = m_iCurrentTick - m_iLastTick;
	
	m_iLastTick = m_iCurrentTick;

	m_fFrameDuration = ( (vfloat32)iDifference / (vfloat32)m_iFrequency);
	
}

void VPerformanceCounter::Update(vfloat32 in_fSeconds)
{
	GetTimeDifference();
}
vfloat64 VPerformanceCounter::GetFrameDuration()
{
	return m_fFrameDuration;
}

void VPerformanceCounter::Activate()
{
}


void VPerformanceCounter::Deactivate()
{
}
//-----------------------------------------------------------------------------
} // namespace updater
} // namespace v3d
//-----------------------------------------------------------------------------


