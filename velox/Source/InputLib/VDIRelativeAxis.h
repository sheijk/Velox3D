#ifndef V3D_VDIRELATIVEAXIS_H
#define V3D_VDIRELATIVEAXIS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Input/IVRelativeAxis.h>

#include <dinput.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {

//-----------------------------------------------------------------------------
/**
 * DirectInput implementation of IVRelativeAxis
 * @author AcrylSword
 * @version 1.1
 */

		class VDIRelativeAxis : public IVRelativeAxis
		{
            DIDEVICEOBJECTINSTANCE	m_diDeviceObject;
            LPDIRECTINPUTDEVICE8	m_pdiDevice;

            public:
								VDIRelativeAxis() {;};
                                VDIRelativeAxis(DIDEVICEOBJECTINSTANCE in_diDeviceObject, LPDIRECTINPUTDEVICE8 in_lpdiDevice );
				virtual			~VDIRelativeAxis();

				virtual VStringRetVal	GetName();
				virtual vfloat32		GetLastMovement();
		};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIRELATIVEAXIS_H