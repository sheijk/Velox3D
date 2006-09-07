/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVUPDATEMANAGER_H
#define V3D_IVUPDATEMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VNamedObject.h>
#include <v3d/Core/SmartPtr/VServicePtr.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VServicePtr.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace updater {
//-----------------------------------------------------------------------------
class IVUpdateable;

/**
	* Update Manager service. Updates all registered objects
	* on a (approximately) regular time interval.
	* 
	* Needs to be called by the application service in order to
	* work:
	* just call Mainloop() which will return when the program is 
	* finished, or
	* Start();
	* while(bActive) {
	*    StartNextFrame();
	*    doYourWorkHere();
	* }
	* Stop();
	*/
class IVUpdateManager : public VNamedObject
{
public:
	/**
		* Calls the update function for all registered objects. Waits
		* until a minumum time since the last update has been passed
		*/
	virtual void StartNextFrame() = 0;

	/**
		* Calls the Activate() function for all registered objects
		*/
	virtual void Start() = 0;

	/**
		* Calls the Deactivate() function for all registered objects
		*/
	virtual void Stop() = 0;

	/**
		* Enters the mainloop.
		* Calls Start() once and then loops calling StartNextFrame()
		* until program shut down is requested. Then calls Stop()
		*/
	virtual void Mainloop() = 0;

	virtual vfloat64 GetFrameDuration() = 0;
	virtual vuint32 GetMilliSecondsSinceStart() = 0;

protected:
	/**
	* Adds an object to update list
	*/
	virtual void Register(IVUpdateable* in_pObject) = 0;

	/**
	* Removes an object from update list. Object won't be updated
	* anymore
	*/
	virtual void Unregister(IVUpdateable* in_pObject) = 0;

	// (un)registering is only allowed for IVUpdateable objects
	friend IVUpdateable;

protected:
	IVUpdateManager(VStringParam in_strName) 
		: VNamedObject(in_strName, 0)
	{
	}
};

typedef VServicePtr<IVUpdateManager> VUpdateManagerPtr;
//-----------------------------------------------------------------------------
} // namespace updater
} // namespace v3d
//-----------------------------------------------------------------------------
template<>
inline v3d::updater::IVUpdateManager* v3d::QueryService<v3d::updater::IVUpdateManager>()
{
	return QueryObject<v3d::updater::IVUpdateManager>("updater.service");
}
//-----------------------------------------------------------------------------
#endif // V3D_IVUPDATEMANAGER_H

