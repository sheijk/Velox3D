/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVUPDATEABLE_H
#define V3D_IVUPDATEABLE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Updater/IVUpdateManager.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace updater {
//-----------------------------------------------------------------------------

/**
 * Interface for objects which require regular updates
 */
class IVUpdateable
{
public:

	/**
	 * Updates the object.
	 * @param in_fSeconds Seconds since last update
	 */
	virtual void Update(vfloat32 in_fSeconds) = 0;

	/**
	 * Tells the object that the mainloop has been entered
	 * and it can expect calls to Update from now on.
	 * Objects should register themselves to any externel
	 * managers now
	 */
	virtual void Activate() = 0;

	/**
	 * Tells the object that the mainloop ended and it cannont
	 * expect any further updates.
	 * Object should unregister themselves from any external
	 * managers now and prepare to be deleted
	 */
	virtual void Deactivate() = 0;

protected:
	IVUpdateable() 
	{
		m_bRegistered = false;
	}

	void Register()
	{
		// query update manager
		IVUpdateManager& updateMngr = 
			* QueryObject<IVUpdateManager>("updater.service");

		// register object
        updateMngr.Register(this);

		// store that object is registered
		m_bRegistered = true;
	}

	void Unregister()
	{
		// query update manager
		IVUpdateManager& updateMngr = 
			* QueryObject<IVUpdateManager>("updater.service");
		
		updateMngr.Unregister(this);

		m_bRegistered = false;
	}

	virtual ~IVUpdateable()
	{
		if( m_bRegistered )
		{
			try
			{
				// query update manager
				IVUpdateManager& updateMngr = 
					* QueryObject<IVUpdateManager>("updater.service");

				// unregister object
				updateMngr.Unregister(this);
			}
			catch(VObjectRegistryException&)
			{
			}
		}
	}

private:
	vbool m_bRegistered;
};

//-----------------------------------------------------------------------------
} // namespace updater
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVUPDATEABLE_H

