#ifndef V3D_VDIINPUTDEVICE_H
#define V3D_VDIINPUTDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VIterator.h>
#include <v3d/Input/IVInputDevice.h>
#include <v3d/Input/IVButton.h>
#include <v3d/Input/IVRelativeAxis.h>
#include <v3d/Input/IVAbsoluteAxis.h>

#include <windows.h>
#include <dinput.h>
#include <list>

#include "VDIButton.h"
#include "VDIRelativeAxis.h"
#include "VDIAbsoluteAxis.h"

//-----------------------------------------------------------------------------
namespace v3d {
	namespace input {
//-----------------------------------------------------------------------------

/**
 * DirectInput implementation of a mouse device
 */

		class VDIInputDevice : public IVInputDevice
		{
		public:
											VDIInputDevice();
											VDIInputDevice( DIDEVICEINSTANCE in_diDeviceStructure, LPDIRECTINPUT8 in_pDI, HWND in_hWnd );
			virtual							~VDIInputDevice();

			virtual VStringRetVal			GetName();

			virtual ButtonIterator			ButtonBegin();
			virtual ButtonIterator			ButtonEnd();

			virtual AbsoluteAxisIterator	AbsoluteAxisBegin();
			virtual AbsoluteAxisIterator	AbsoluteAxisEnd();

			virtual RelativeAxisIterator	RelativeAxisBegin();
			virtual RelativeAxisIterator	RelativeAxisEnd();

			void							Update();
			vbool							Create(LPDIRECTINPUT8 in_pDI, HWND in_hWnd);
			

		protected:
			void							EnumerateDeviceObjects();
			static BOOL CALLBACK			StaticDIEnumDeviceObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
			virtual vbool				    EnumDeviceObjectCallback(const DIDEVICEOBJECTINSTANCE* in_pdiDOI);
				
			LPDIRECTINPUTDEVICE8			m_pdiDevice;
			DIDEVICEINSTANCE				m_diDeviceInstance;
			DIDEVCAPS						m_diDevCaps;

			std::list<VDIButton>			m_ButtonList;
			std::list<VDIRelativeAxis>		m_RelativeAxisList;
			std::list<VDIAbsoluteAxis>		m_AbsoluteAxisList;
		};

		//-----------------------------------------------------------------------------
	} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIMOUSEDEVICE_H
