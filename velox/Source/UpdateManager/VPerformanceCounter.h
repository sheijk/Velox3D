/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VPERFORMANCECOUNTER_H
#define V3D_VPERFORMANCECOUNTER_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Updater/IVTimer.h>
#include <V3d/Updater/IVUpdateable.h>
#include <windows.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace updater {
//-----------------------------------------------------------------------------

/**
 * Implementation of IVTimer
 */

class VPerformanceCounter : public IVUpdateable, public IVTimer
{
public:
	
	VPerformanceCounter();
	virtual ~VPerformanceCounter();

	vfloat64 GetFrameDuration();

	void Update(vfloat32 in_fSeconds);

	/**
	* Tells the object that the mainloop has been entered
	* and it can expect calls to Update from now on.
	* Objects should register themselves to any externel
	* managers now
	*/

	void Activate();

	/**
	* Tells the object that the mainloop ended and it cannont
	* expect any further updates.
	* Object should unregister themselves from any external
	* managers now and prepare to be deleted
	*/
	void Deactivate();


private:
	
	/* returns the last frame duration */
	void GetTimeDifference();

	vint64 m_iFrequency;
	vint64 m_iCurrentTick;
	vint64 m_iLastTick;
	vfloat64 m_fFrameDuration;	
};

//-----------------------------------------------------------------------------
} // namespace updater
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPERFORMANCECOUNTER_H

