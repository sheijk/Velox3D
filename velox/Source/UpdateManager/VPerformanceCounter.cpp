#include <v3d/Updater/IVTimer.h>
#include <windows.h>
//-----------------------------------------------------------------------------
#include "VPerformanceCounter.h"
#include <v3d/Core/MemManager.h>
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

