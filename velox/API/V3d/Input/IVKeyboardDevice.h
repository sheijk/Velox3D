#ifndef V3D_IVKEYBOARDDEVICE_2004_08_09_H
#define V3D_IVKEYBOARDDEVICE_2004_08_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Input/IVInputDevice.h>
#include <v3d/Input/KeyEnumeration.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/**
 * Interface for an attached keyboard
 * @author sheijk
 * @version 1.0
 */
class IVKeyboardDevice : public IVInputDevice
{
public:
	virtual				~IVKeyboardDevice() {};

	virtual IVButton&	GetKey(const KeyCodes in_KeyCode) = 0;
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVKEYBOARDDEVICE_2004_08_09_H
