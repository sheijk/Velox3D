//
// *** VTimer ***
//
// Synopsis:
//    - Timer class
//
// Description:
//    - Gets the time
//
// See also:
//    - 
//

#ifndef V3D_VTIMER_H
#define V3D_VTIMER_H


#include <windows.h>
#include <Mmsystem.h>

#include <Core/VTypes.h>

#pragma comment(lib, "winmm.lib")


class VTimer
{
public:

	VTimer();

	vfloat32 m_fFrameRate;		//Current frame rate
	vfloat32 m_fTickRate;
	vfloat32 m_fSpeedFactor;		//Multiply each movement with this factor 
							//for fps independant movement
	vint64 m_iCurrentTicks;
	vint64 m_iPreviousTicks;

	void Initialize(void);			//Init the timer
	void Update(void);				//Must be called after each frame

	void GetTime(vint64 &iCurrTicks);
	void GetTime(vfloat32 &fCurrTime);
	void GetTimeDifference(vint64 &iDiffTicks, vint64 &iPrevTicks);
	void GetTimeDifference(vint64 &iPrevTicks, vfloat32 fDiffTime);
};


#endif //VTIMER_H