//
// *** VInputDirect7 ***
//
// Synopsis:
//    - DirectInput implementation
//
// History:
//    -		Wheel not implemented
//
// See also:
//    - 
//

#ifndef V3D_VINPUTDDIRECT7_H
#define V3D_VINPUTDDIRECT7_H

#include <Core/VTypes.h>
#include <Input/IVInput.h>

#define DIRECTINPUT_VERSION 0x0700

#include <dinput.h>

//#pragma warning( disable : 4800 )

#pragma comment(lib, "dinput.lib")
#pragma comment(lib, "dxguid.lib")


class VInputDirect7 : IVInput
{
private:

	enum Settings
	{
		BufferSize = 256,
        NumKeys	   = 256,
		NumButtons = 8,
	};

	void GetKeyboardInput(); 
	void GetMouseInput();
	void GetImmediateInput();

	LPDIRECTINPUT7		 m_lpDInputObject;
	LPDIRECTINPUTDEVICE7 m_lpKeyboard;
	LPDIRECTINPUTDEVICE7 m_lpMouse;
	DIDEVICEOBJECTDATA	 m_diInputData;
	DIMOUSESTATE2		 m_diMouseState;

	vbool m_bKeyBufferPressed[NumKeys];
	vbool m_bKeyBufferHold[NumKeys];
	vbool m_bMouseBufferHold[NumButtons];
	vbool m_bMouseBufferPressed[NumButtons];
	vlong m_lMousePosition[3];
	vbool m_bWheelAvailable;
	vulong m_Granularity;

public:

	VInputDirect7(void);
	~VInputDirect7(void);

	
	VRESULT Initialize(HINSTANCE hInstanceHandle, HWND hWindowHandle);
	VRESULT Shutdown();

	vbool IsKeyPressed(vulong iKey);
	vbool IsKeyHold(vulong iKey);
	vbool IsMouseButtonHold(vuint MouseButton);
	vbool IsMouseButtonPressed(vuint MouseButton);
	vlong* GetMousePosition();
	vbool IsMouseWheelUp();
	vbool IsMouseWheelDown();

	void Clear();
	void GetInput();

};

#endif