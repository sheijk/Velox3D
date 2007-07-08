/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVSYSTEMMANAGER_H
#define V3D_IVSYSTEMMANAGER_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace system {
//-----------------------------------------------------------------------------

/**
 * Provides a system to close velox	
 */
// sollte eigentlich von VNamedObject abgeleitet sein (sheijk)
class IVSystemManager
{
public:
	
	virtual ~IVSystemManager(){};

	//TODO: "Status" true/false ist verwirrend.. (sheijk)
	// wie waers mit enum State { Running, Quit }; SetStatus(State) ?
	// alternativ einfach Shutdown(), mehr tut die Fkt doch nicht, oder?
	virtual void SetStatus(vbool in_Param) = 0; //true for running false for quit
	virtual vbool GetStatus() = 0; //returs true for running false for quit
};

typedef VServicePtr<IVSystemManager> VSystemManagerPtr;
//-----------------------------------------------------------------------------
} // namespace system
} // namespace v3d
//-----------------------------------------------------------------------------
template<>
inline v3d::system::IVSystemManager* v3d::QueryService<v3d::system::IVSystemManager>()
{
	return QueryObject<v3d::system::IVSystemManager>("system.service");
}
//-----------------------------------------------------------------------------
#endif // V3D_VSYSTEMMANAGER_H

