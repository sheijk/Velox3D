#ifndef V3D_VDIABSOLUTEAXIS_H
#define V3D_VDIABSOLUTEAXIS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Input/IVAbsoluteAxis.h>

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
		class VDIAbsoluteAxis : public IVAbsoluteAxis
        {
			VDIAbsoluteAxis();
		
			DIDEVICEOBJECTINSTANCE	m_diDeviceObject;
			LPDIRECTINPUTDEVICE8	m_pdiDevice;

		public:
            VDIAbsoluteAxis( DIDEVICEOBJECTINSTANCE in_diDeviceObject, LPDIRECTINPUTDEVICE8 in_lpdiDevice );
			virtual					~VDIAbsoluteAxis();

			virtual VStringRetVal	GetName();
			virtual vfloat32		GetPosition();
		};

//-----------------------------------------------------------------------------
	} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIABSOLUTEAXIS_H
