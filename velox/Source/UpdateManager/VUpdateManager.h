#ifndef V3D_VUPDATEMANAGER_H
#define V3D_VUPDATEMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Updater/IVUpdateManager.h>
#include <v3d/Updater/IVTimer.h>
//-----------------------------------------------------------------------------
#include "VPerformanceCounter.h"
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace updater {
//-----------------------------------------------------------------------------

/**
 * Implementation of an update manager
 */
class VUpdateManager : public IVUpdateManager
{
	typedef std::list<IVUpdateable*> UpdateList;

	UpdateList my_Subjects;
public:
	VUpdateManager(VStringParam in_strId);
	virtual ~VUpdateManager();

	virtual void StartNextFrame();
	virtual void Start();
	virtual void Stop();
	virtual void Mainloop();
	vfloat64 GetFrameDuration();

	vuint32 GetMilliSecondsSinceStart();
protected:
	virtual void Register(IVUpdateable* in_pObject);
	virtual void Unregister(IVUpdateable* in_pObject);

	IVTimer* m_pTimer;

	// will overflow after ~1100 hours..
	vuint32 m_nMilliSecondsSinceStart;
};

//-----------------------------------------------------------------------------
} // namespace updater
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VUPDATEMANAGER_H
