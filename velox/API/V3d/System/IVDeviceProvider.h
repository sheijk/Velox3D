#ifndef V3D_IVDeviceProvider_H
#define V3D_IVDeviceProvider_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include <v3d/Core/VNamedObject.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

class IVGraphicDevice;
//class SoundDevice;
//class InputDevice;

/**
 * Interface for querying devices which are dependent on a window / a 
 * system dependent window handle
 */
class IVDeviceProvider : public VNamedObject
{
protected:
	IVDeviceProvider(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent) 
	{
	}

public:
	virtual IVGraphicDevice& QueryGraphicDevice() = 0;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDeviceProvider_H
