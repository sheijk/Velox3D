#ifndef V3D_VDIBUTTON_H
#define V3D_VDIBUTTON_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Input/IVButton.h>

#include <dinput.h>
//-----------------------------------------------------------------------------
namespace v3d {
	namespace input {
	
//-----------------------------------------------------------------------------

/**
 * DirectInput implementation of a button
 * @author AcrylSword
 * @version 1.1
 */
		class VDIButton : public IVButton
		{
            VDIButton();

            DIDEVICEOBJECTINSTANCE	m_diDeviceObject;
			LPDIRECTINPUTDEVICE8	m_pdiDevice;

		public:
            			VDIButton(DIDEVICEOBJECTINSTANCE in_diDeviceObject, LPDIRECTINPUTDEVICE8 in_pdiDevice);
			virtual		~VDIButton();

			virtual VStringRetVal	GetName();
			virtual vbool			IsDown();
		};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIBUTTON_H
