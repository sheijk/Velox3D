#ifndef V3D_VPERFORMANCECOUNTER_H
#define V3D_VPERFORMANCECOUNTER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Updater/IVTimer.h>
#include <v3d/Updater/IVUpdateable.h>
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