#ifndef V3D_IVSYSTEMMANAGER_H
#define V3D_IVSYSTEMMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
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

//-----------------------------------------------------------------------------
} // namespace system
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSYSTEMMANAGER_H
