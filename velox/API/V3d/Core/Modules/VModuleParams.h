#ifndef V3D_VMODULEPARAMS_H
#define V3D_VMODULEPARAMS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
class VObjectRegistry;
//class IVMemoryManager;

struct VModuleParams
{
	VObjectRegistry* pObjectRegistry;
//	IVMemoryManager* pMemoryManager;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMODULEPARAMS_H
