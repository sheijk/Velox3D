#ifndef V3D_VMODULEBASE_H
#define V3D_VMODULEBASE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

V3D_DECLARE_EXCEPTION(VModuleLoadFailure, VException);

class VModuleBase
{
	static VModuleBase* s_pModule;
	static const vchar* s_pcModuleName;

protected:
	VModuleBase(VStringParam in_pcModuleName);
	virtual ~VModuleBase();

public:
	static VModuleBase* GetInstance();
	static const vchar* GetModuleName();

	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMODULEBASE_H
