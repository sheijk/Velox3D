//
// *** VInput ***
//
// Synopsis:
//    - Input interface
//
// Description:
//    - 
//
// See also:
//    - 
//



#ifndef V3D_IVINPUT_H
#define V3D_IVINPUT_H

#include <windows.h>
#include <Core/VTypes.h>

class IVInput
{

public:
	
	virtual VRESULT Initialize(HINSTANCE hInstanceHandle, HWND hWindowHandle) = 0;
	virtual VRESULT Shutdown() = 0;

	virtual void Clear() = 0;
	virtual void GetInput() = 0;
	virtual vbool IsKeyPressed(vulong iKey) = 0;
	virtual vbool IsKeyHold(vulong iKey) = 0;
	virtual vbool IsMouseButtonHold(vuint MouseButton) = 0;
    virtual vbool IsMouseButtonPressed(vuint MouseButton) = 0;
	virtual vbool IsMouseWheelUp() = 0;
	virtual vbool IsMouseWheelDown() = 0;
	virtual vlong* GetMousePosition() = 0; //Returns a pointer to 3 long values 

};

#endif