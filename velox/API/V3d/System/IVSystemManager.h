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

class IVSystemManager
{
public:
	
	virtual ~IVSystemManager(){};

	virtual void SetStatus(vbool in_Param) = 0; //true for running false for quit
	virtual vbool GetStatus() = 0; //returs true for running false for quit

};

//-----------------------------------------------------------------------------
} // namespace system
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSYSTEMMANAGER_H
