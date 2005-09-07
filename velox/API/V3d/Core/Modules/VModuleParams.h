#ifndef V3D_VMODULEPARAMS_H
#define V3D_VMODULEPARAMS_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
class VObjectRegistry;
class IVMemLogger;

struct VModuleParams
{
	VObjectRegistry* pObjectRegistry;
	IVMemLogger* pMemLogger;
	//vuint moduleId;
//	IVMemoryManager* pMemoryManager;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMODULEPARAMS_H
