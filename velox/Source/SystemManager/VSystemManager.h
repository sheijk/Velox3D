#ifndef V3D_VSYSTEMMANAGER_H
#define V3D_VSYSTEMMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/System/IVSystemManager.h>
#include <v3d/Core/VNamedObject.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace system {
//-----------------------------------------------------------------------------

/**
 * Provides a system to close velox	
 */

class VSystemManager : public IVSystemManager, public VNamedObject
{
public:
	VSystemManager(VStringParam in_Name);
	virtual ~VSystemManager();

	virtual void SetStatus(vbool in_Param); //true for running false for quit
	virtual vbool GetStatus(); //returs true for running false for quit
	virtual void GetCPU(); // vout's cpu info

private:

	vbool m_bIsRunning;
};

//-----------------------------------------------------------------------------
} // namespace system
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSYSTEMMANAGER_H
