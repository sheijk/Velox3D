// *** VTimer ***
//
// Synopsis:
//    - Timer class
//
// Description:
//    - Gets the time
//
// See also:
//    - VTimer.h
//
#include <Core/VTimer.h>


VTimer::VTimer()
{
	m_fFrameRate		= 0.0f;
	m_fTickRate			= 0.0f;
	m_fSpeedFactor		= 0.0f;
	m_iCurrentTicks		= 0;
	m_iPreviousTicks	= 0;

}

void VTimer::Initialize(void)
{
	vint64 iFrequency;

	if(QueryPerformanceFrequency((LARGE_INTEGER *)&iFrequency))
		m_fTickRate = (vfloat32)iFrequency;

	else m_fTickRate = 1000.0f;
}


void VTimer::Update(void)
{
	if(!QueryPerformanceCounter((LARGE_INTEGER *)&m_iCurrentTicks))
	{
		timeBeginPeriod(1);
		m_iCurrentTicks = (vint64)timeGetTime();
		timeEndPeriod(1);
	}

	m_fFrameRate		= m_fTickRate/(vfloat32)(m_iCurrentTicks - m_iPreviousTicks);
	m_fSpeedFactor		= 100 / m_fFrameRate;		//FIXME: CONSTANT FOR TARGET FPS!!!
	m_iPreviousTicks	= m_iCurrentTicks;
}


void VTimer::GetTime(vint64 &iCurrTicks)
{
	if(!QueryPerformanceCounter((LARGE_INTEGER *)&iCurrTicks))
	{
		timeBeginPeriod(1);
		iCurrTicks = (vint64)timeGetTime();
		timeEndPeriod(1);
	}
}


void VTimer::GetTime(vfloat32 &fCurrTime)
{
	vint64 iCurrTicks = 0;

	if(!QueryPerformanceCounter((LARGE_INTEGER *)&iCurrTicks))
	{
		timeBeginPeriod(1);
		iCurrTicks = (vint64)timeGetTime();
		timeEndPeriod(1);
	}

	fCurrTime = (vfloat32)iCurrTicks/m_fTickRate;
}

void VTimer::GetTimeDifference(vint64 &iDiffTicks, vint64 &iPrevTicks)
{
	if(!QueryPerformanceCounter((LARGE_INTEGER *)&iDiffTicks))
	{
		timeBeginPeriod(1);
		iDiffTicks = (vint64)timeGetTime();
		timeEndPeriod(1);
	}

	iDiffTicks -= iPrevTicks;
}


void VTimer::GetTimeDifference(vint64 &iPrevTicks, vfloat32 fDiffTime)
{
	vint64 iCurrTicks = 0;

	if(!QueryPerformanceCounter((LARGE_INTEGER *)&iCurrTicks))
	{
		timeBeginPeriod(1);
		iCurrTicks = (vint64)timeGetTime();
		timeEndPeriod(1);
	}

	fDiffTime = (float)(iCurrTicks-iPrevTicks)/m_fTickRate;
}
