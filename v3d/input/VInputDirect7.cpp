//
// *** VInputDirect7 ***
//
// Synopsis:
//    - DirectInput implementation
//
// Description:
//    - 
//
// See also:
//    - 
//

#include <Input/VInputDirect7.h>

VInputDirect7::VInputDirect7()
{
	m_lpDInputObject = NULL;
	m_lpKeyboard	 = NULL;
	m_lpMouse	 	 = NULL;
}


VRESULT VInputDirect7::Initialize(HINSTANCE hInstanceHandle, HWND hWindowHandle)
{
	memset(m_bMouseBufferHold, 0, sizeof(bool)*NumButtons);
	memset(m_bKeyBufferHold, 0,   sizeof(bool)*NumKeys);
	
	HANDLE hEvent = NULL;
	
	hEvent = CreateEvent(0, 0, 0, 0);
	
	DIPROPDWORD DeviceProperties =
	{ { sizeof(DIPROPDWORD), sizeof(DIPROPHEADER), 0, DIPH_DEVICE }, BufferSize };


	// DInput Object
	if(DirectInputCreateEx(hInstanceHandle, DIRECTINPUT_VERSION, IID_IDirectInput7, (void **)&m_lpDInputObject, NULL) != DI_OK)
		return VERROR_INPUT_DXOBJECT;
	
	//Keyboard
	if(m_lpDInputObject->CreateDeviceEx(GUID_SysKeyboard, IID_IDirectInputDevice7, (void **)&m_lpKeyboard, NULL) != DI_OK)
		return VERROR_INPUT_KEYBOARDDEVICE;
	
	if(m_lpKeyboard->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
		return VERROR_INPUT_KEYBOARDFORMAT;
		
	if(m_lpKeyboard->SetCooperativeLevel(hWindowHandle, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE) != DI_OK)
		return VERROR_INPUT_KEYBOARDCOOPERATIVE;
		
	if(m_lpKeyboard->SetEventNotification(hEvent) != DI_OK)
		return VERROR_INPUT_KEYBOARDEVENT;
		
	if(m_lpKeyboard->SetProperty(DIPROP_BUFFERSIZE, &DeviceProperties.diph) != DI_OK)
		return VERROR_INPUT_KEYBOARDPROPERTY;
			
	if(m_lpKeyboard->Acquire() != DI_OK)
		return VERROR_INPUT_KEYBOARDACQUIRE;
		
	// Mouse
	if(m_lpDInputObject->CreateDeviceEx(GUID_SysMouse, IID_IDirectInputDevice7, (void **)&m_lpMouse, NULL) != DI_OK)
		return VERROR_INPUT_MOUSEDEVICE;
			
	if(m_lpMouse->SetDataFormat(&c_dfDIMouse) != DI_OK)
		return VERROR_INPUT_MOUSEFORMAT;
	
	if(m_lpMouse->SetCooperativeLevel(hWindowHandle, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE) != DI_OK)
		return VERROR_INPUT_MOUSECOOPERATIVE;
		
	if(m_lpMouse->SetEventNotification(hEvent) != DI_OK)
        return VERROR_INPUT_MOUSEEVENT;
		
	if(m_lpMouse->SetProperty(DIPROP_BUFFERSIZE, &DeviceProperties.diph) != DI_OK)
		return VERROR_INPUT_MOUSEPROPERTY;
	
	if(m_lpMouse->Acquire() != DI_OK)
		return VERROR_INPUT_MOUSEACQUIRE;

/*	// Has the mouse got a wheel attached?
	DIDEVICEOBJECTINSTANCE  didoi; 
 	didoi.dwSize = sizeof(DIDEVICEOBJECTINSTANCE); 

	HRESULT hr = m_lpDInputObject->GetObjectInfo(&didoi,DIMOFS_Z, DIPH_BYOFFSET);
	m_bWheelAvailable = SUCCEEDED(hr);

	////////////////////////////////////////////////////////////
	//
	// Is the mouse is available, get the Granularity of the
	// Mouse Wheel
	//
	////////////////////////////////////////////////////////////
	if(m_bWheelAvailable)
	{
		// If A Wheel Mouse, Get the Granularity if any
		DIPROPDWORD dipdw=
		{
			// The Header
			{
				sizeof(DIPROPDWORD),	// diph.dwSize
				sizeof(DIPROPHEADER),	// diph.dwHeaderSize
				DIMOFS_Z,			// diph.dwObj - By Offset
				DIPH_BYOFFSET,			// diph.dwHow - Offset
			},
			// The Data
			NULL
		};

		hr=m_lpDIInputObject->GetProperty(DIPROP_GRANULARITY, &dipdw.diph);
		if(FAILED(hr))
			return VERROR_INPUT_MOUSEWHEEL;
		
		m_Granularity=dipdw.dwData;
	}
	
	if(!m_Granularity)m_Granularity=1;*/
	
	return VOK;

}

VRESULT VInputDirect7::Shutdown()
{
	if(m_lpMouse)
		m_lpMouse->Release();
	if(m_lpKeyboard)
		m_lpKeyboard->Release();
	if(m_lpDInputObject)
		m_lpDInputObject->Release();

	return VOK;
}

void VInputDirect7::Clear()
{
	memset(m_bMouseBufferPressed, 0, sizeof(bool)*NumButtons);
	memset(m_bKeyBufferPressed, 0, sizeof(bool)*NumKeys);
}

void VInputDirect7::GetKeyboardInput()
{
	vulong lElements = 1;
	vulong lKey = 0;
	
	m_lpKeyboard->Poll();
	
	while(1)
	{
		if(m_lpKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &m_diInputData, &lElements, 0) == DIERR_INPUTLOST)
		{
			if(SUCCEEDED(m_lpKeyboard->Acquire()))
				m_lpKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &m_diInputData, &lElements, 0);
		}
		
		if(!lElements) break;
		
		for(lKey; lKey < NumKeys; lKey++)
		{
			if(m_diInputData.dwOfs == lKey)
			{
				m_bKeyBufferPressed[lKey] = m_diInputData.dwData & 0x80 ? true : false; 
				break; 
			}
		}
	}
	
}

void VInputDirect7::GetMouseInput()
{
	vulong lElements = 1;
	
	m_lpMouse->Poll();
	
	while(1)
	{
		if(m_lpMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &m_diInputData, &lElements, 0) == DIERR_INPUTLOST)
		{
			if(SUCCEEDED(m_lpMouse->Acquire()))
				m_lpKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &m_diInputData, &lElements, 0);
		}
		
		if(!lElements) break;
		
		switch(m_diInputData.dwOfs)
		{
		case DIMOFS_BUTTON0:
			m_bMouseBufferPressed[0] = m_diInputData.dwData & 0x80 ? true : false; 
			break;
			
		case DIMOFS_BUTTON1: 
			m_bMouseBufferPressed[1] = m_diInputData.dwData & 0x80 ? true : false; 
			break;
			
		case DIMOFS_BUTTON2: 
			m_bMouseBufferPressed[2] = m_diInputData.dwData & 0x80 ? true : false; 
			break;
			
		case DIMOFS_BUTTON3: 
			m_bMouseBufferPressed[3] = m_diInputData.dwData & 0x80 ? true : false; 
			break;
			
		case DIMOFS_BUTTON4: 
			m_bMouseBufferPressed[4] = m_diInputData.dwData & 0x80 ? true : false; 
			break;
			
		case DIMOFS_BUTTON5: 
			m_bMouseBufferPressed[5] = m_diInputData.dwData & 0x80 ? true : false; 
			break;
			
		case DIMOFS_BUTTON6: 
			m_bMouseBufferPressed[6] = m_diInputData.dwData & 0x80 ? true : false; 
			break;
			
		case DIMOFS_BUTTON7: 
			m_bMouseBufferPressed[7] = m_diInputData.dwData & 0x80 ? true : false; 
			break;
		}
	}

	
}

void VInputDirect7::GetImmediateInput()
{
	DIMOUSESTATE Mouse;
	
	m_lpMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&Mouse);
	
	m_lMousePosition[0] = Mouse.lX;
	m_lMousePosition[1] = Mouse.lY;
	m_lMousePosition[2] = Mouse.lZ;
	
/*	int i = 0;
	for(i; i < NumButtons; i++)
		m_bMouseBufferHold[i] = Mouse.rgbButtons[i];

	if(m_bWheelAvailable)
	{
		if(m_lpMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &m_diInputData, &lElements, 0) == DIERR_INPUTLOST)
		{
		
			if(m_lpMouse->GetDeviceState(sizeof(m_diMouseState),(LPVOID)&m_diMouseState) != DI_OK)
				return VERROR_INPUT_MOUSEWHEELSTATE;
			
			if(!m_iZr)
			{
				if(m_MouseState.lZ)
				{
					m_iZr=(m_MouseState.lZ/m_Granularity);
				}
			}

			m_WheelUp=(m_iZr < 0)? true : false;
			m_WheelDown=(m_iZr>0) ? true : false;
		}
	}*/



	m_lpKeyboard->GetDeviceState(sizeof(m_bKeyBufferHold), (LPVOID)&m_bKeyBufferHold);
}

void VInputDirect7::GetInput()
{
	Clear(); 
	GetKeyboardInput(); 
	GetMouseInput(); 
	GetImmediateInput();
}

vbool VInputDirect7::IsKeyHold(vulong iKey)
{
	return m_bKeyBufferHold[iKey];
}


vbool VInputDirect7::IsKeyPressed(vulong iKey)
{
	return m_bKeyBufferPressed[iKey];
}

vbool VInputDirect7::IsMouseButtonHold(vuint MouseButton)
{
	return m_bMouseBufferHold[MouseButton];
}

vbool VInputDirect7::IsMouseButtonPressed(vuint MouseButton)
{
	return m_bMouseBufferPressed[MouseButton];
}

vlong* VInputDirect7::GetMousePosition()
{
	return m_lMousePosition;
}



/*

Wie vielleicht manche schon wissen, baut 6S eine neue 3D Engine für zukünftige Projekte.
Wir stecken momentan im core development. Dies bedeutet, dass wir gerade die Systemstrukturen
festlegen und ein SDK für 3D Game Development im engeren Sinne schreiben (d.h. was wir für ein Spiel brauchen;
diese Engine soll kein Unreal2 Renderer schlagen sondern halt nur flüssig und gut funktionieren ;).
Wir fokusieren das Gameplay auf Multiplayer Action und stimmen die Engine darauf ab.
Aus diesem Grund suchen wir Spieleentwickler, die mit Engagement, gemeinsam ein efolgreiches Projekt
durchziehen wollen. Wer Lust und vor allem ZEIT hat, kann sich gerne bei uns melden, um in die Coding Specs zu 
schauen oder sich mit den Projektleitern zu unterhalten. Du solltest demnach mit C++ vertraut sein und
flexible sein, neue Dinge zu lernen oder anderen zu erklären ;).


		Project			  : Velox3D
		Team			  : Sechsta Sinn |6S
		Coding Language	  : C++
		Discription		  : Multiplayer 3D Game Engine
		System			  : Currently only Mircorsoft Windows x platform
		Current Dev. Step : Implementing core functunality
		Current developers: Nufan (coder) , Insane (coder)


													-insane@sechsta-sinn.de

PS.: Bitte keine Anfragen wie: ist das Projekt komerziell etc.
	 Wir sind alle "Freizeit - Coder" ;)

													*/







