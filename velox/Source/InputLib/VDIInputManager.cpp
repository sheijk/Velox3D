#include "VDIInputManager.h"
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/Wrappers/VSTLDerefIteratorPol.h> 
#include <v3d/Input/VInputException.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
VDIInputManager::VDIInputManager()
: m_hWnd(0), m_pDI(0), m_bRegistered(false), m_pStandardMouse(0),
  m_pStandardKeyboard(0)
{

}

VDIInputManager::VDIInputManager( HWND in_hWnd )
: m_hWnd(in_hWnd), m_pDI(0), m_bRegistered(false), m_pStandardMouse(0),
  m_pStandardKeyboard(0)
{
	V3D_ASSERT(in_hWnd != 0);
	
	// Create the DirectInput8 object
	Create();
}

/**
 * The destructor just releases the IDirectInput8 object. All other work
 * is done by other classes
 *
 * @author AcrylSword
 */
template<class Iter> void deleteAll(Iter begin, Iter end)
{ 
	for( ; begin != end; ++begin)
	{
		delete *begin;
		*begin = 0;
	}
}

VDIInputManager::~VDIInputManager()
{
	//Only release objects if *this is valid
	if (m_pDI)
	{
		//delete standard mouse        
		delete m_pStandardMouse;
	    m_pStandardMouse = 0;

		//delete standard keyboard
		delete m_pStandardKeyboard;
		m_pStandardKeyboard = 0;

		//Call DeleteAll to make sure that all 
		//IDirectInputDevice8 objects are release before we delete
		// the parent object.
		deleteAll(m_DeviceList.begin(), m_DeviceList.end());
		m_DeviceList.clear();
		m_InputDeviceList.clear();
		m_KeyboardList.clear();
		m_MouseList.clear();
		
		//Now we can release m_pDI safely
		m_pDI->Release();
		m_pDI = 0;
	}
}

void VDIInputManager::Create()
{
	HRESULT hr;

    // Create DirectInput interface
	vout << "Init DirectInput8..." << vendl;
	if ( DI_OK != (hr=DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL)) )
	{
		vout << "failed: DirectInput8Create() says: " << hr << vendl;
		V3D_THROW( VCreationException, "Could not create DirectInput8" );
	}

	vout << "Create standard keyboard device..." << vendl;
	// Create standard keyboard and mouse device
	if ( !InitStandardKeyboardDevice() )
		V3D_THROW( VCreationException, "Could not create standard keyboard device");

	vout << "Create standard mouse device..." << vendl;
	if ( !InitStandardMouseDevice() )
		V3D_THROW( VCreationException, "Could not create standard mouse device" );

	IVUpdateable::Register();

	// enumerate devices
	if ( !EnumerateDevices() )
		V3D_THROW( VCreationException, "Could not enumerate devices");
}
/**
 * The creation of the standard keyboard device is a small hack.
 * The standard keyboard is represented through a VDIKeyboardDevice 
 * object. Under DirectInput the standard device are represented trough
 * a special GUID. So we have to set up the DIDEVICEINSTANCE structure by
 * ourself.
 *
 * @author AcrylSword
 */
vbool VDIInputManager::InitStandardKeyboardDevice()
{
	//Set up the DIDEVICEINSTANCE structure
	DIDEVICEINSTANCE deviceInstance;
	ZeroMemory( &deviceInstance, sizeof(DIDEVICEINSTANCE) );
	deviceInstance.dwSize = sizeof(DIDEVICEINSTANCE);
	//We only need to set to attributes
	//TODO:
	//deviceInstance.tszInstanceName = "Standard DirectInput Keyboard Device";
	deviceInstance.guidInstance = GUID_SysKeyboard;

	try {
		m_pStandardKeyboard = new VDIKeyboardDevice(deviceInstance, m_pDI, m_hWnd);
	}
	catch (VInputException& e)
	{
		return false;
	}

	return true;
}
/**
* The creation of the standard mouse device is a small hack.
* The standard mouse is represented through a VDIMouseDevice 
* object. Under DirectInput the standard device are represented trough
* a special GUID. So we have to set up the DIDEVICEINSTANCE structure by
* ourself.
*
* @author AcrylSword
*/
vbool VDIInputManager::InitStandardMouseDevice()
{
	//Set up the DIDEVICEINSTANCE structure
	DIDEVICEINSTANCE deviceInstance;
	ZeroMemory( &deviceInstance, sizeof(DIDEVICEINSTANCE) );
	deviceInstance.dwSize = sizeof(DIDEVICEINSTANCE);
	//We only need to set to attributes
//	deviceInstance.tszInstanceName = "Standard DirectInput Mouse Device";
	deviceInstance.guidInstance = GUID_SysMouse;

	try {
		m_pStandardMouse = new VDIMouseDevice(deviceInstance, m_pDI, m_hWnd);
	}
	catch (VInputException& e)
	{
		return false;
	}

	return true;
}

/**
 * Returns the standard keyboard device
 *
 * @return The standard keyboard device
 * @auhtor AcrylSword
 */
IVKeyboardDevice& VDIInputManager::GetStandardKeyboard()
{
	return *m_pStandardKeyboard;
}

/**
* Returns the standard mouse device
*
* @return The standard mouse device
* @auhtor AcrylSword
*/
IVMouseDevice& VDIInputManager::GetStandardMouse()
{
	return *m_pStandardMouse;
}
/**
 * This method starts enumeration of all kinds of attatched input devices
 * For each device the method EnumDevicesCallback() is called.
 *
 * @author AcrylSword
 */
vbool VDIInputManager::EnumerateDevices()
{
	// enumerate all devices with 
	if ( DI_OK != m_pDI->EnumDevices( DI8DEVCLASS_ALL,
		StaticDIEnumDevicesCallback,
		(LPVOID) this,
		DIEDFL_ATTACHEDONLY ) )
	{
		vout << "DI: devices enumeration failed" << vendl;
		return false;
	}

	return true;
}

vbool VDIInputManager::EnumDevicesCallback(const DIDEVICEINSTANCE* in_pdiDeviceInstance)
{
	IVInputDevice* device = 0;

	try {
		switch ( GET_DIDEVICE_TYPE(in_pdiDeviceInstance->dwDevType) )
		{
            case DI8DEVTYPE_JOYSTICK:	
			case DI8DEVTYPE_GAMEPAD:
				device = new VDIInputDevice(*in_pdiDeviceInstance, m_pDI, m_hWnd, IVInputDevice::Undefined);
				break;
            case DI8DEVTYPE_KEYBOARD:
				device = new VDIKeyboardDevice(*in_pdiDeviceInstance, m_pDI, m_hWnd);
				break;
			case DI8DEVTYPE_MOUSE:
				device = new VDIMouseDevice(*in_pdiDeviceInstance, m_pDI, m_hWnd);
				break;
			default:
				return true;
		}
	}
	catch(VCreationException& e) {
		vout << "Failed to create direct input device object" << vendl;
		return true;
	}

	V3D_ASSERT(device != 0);
	m_DeviceList.push_back(device);

	return true;
}

// from IVUpdateable
void VDIInputManager::Update(vfloat32 in_fSeconds)
{
	// update standard devices
	m_pStandardKeyboard->Update();
    m_pStandardMouse->Update();

	// update mouse devices
	for ( std::list<VDIMouseDevice*>::iterator Iter = m_MouseList.begin();
		  Iter != m_MouseList.end();
		  ++Iter)
	{
		(*Iter)->Update();
	}

	// update keyboard devices
	for ( std::list<VDIKeyboardDevice*>::iterator Iter = m_KeyboardList.begin();
		  Iter != m_KeyboardList.end();
		  ++Iter)
	{
		(*Iter)->Update();
	}

	// update other devices
	for ( std::list<VDIInputDevice*>::iterator Iter = m_InputDeviceList.begin();
		  Iter != m_InputDeviceList.end();
		  ++Iter )
	{
		(*Iter)->Update();
	}
}

void VDIInputManager::Activate()
{
}

void VDIInputManager::Deactivate()
{
}

void VDIInputManager::SetActive(vbool in_bStatus)
{
	if(in_bStatus)
	{
		if(!m_bRegistered)
		{
			IVUpdateable::Register();
			m_bRegistered = true;
		}
	}
	else
	{
		if(m_bRegistered)
		{
			
			IVUpdateable::Unregister();
			m_bRegistered = false;
//			ClearInputData();
		}
	}
}

/**
* Returns a VForwardIterator pointing to the beginning of the device list
*
* @return A iterator pointing to the beginning of the device list
* @author AcrylSword
*/
IVInputManager::DeviceIterator VDIInputManager::DeviceBegin()
{
	typedef VSTLDerefIteratorPol<std::list<IVInputDevice*>::iterator, IVInputDevice> DeviceIterPol;
	return DeviceIterator( new DeviceIterPol(m_DeviceList.begin()));
}
/**
* Returns a VForwardIterator pointing to the end of the device list
* @return A iterator pointing to the end of the device list
* @author AcrylSword
*/
IVInputManager::DeviceIterator VDIInputManager::DeviceEnd()
{
	typedef VSTLDerefIteratorPol<std::list<IVInputDevice*>::iterator, IVInputDevice> DeviceIterPol;
	return DeviceIterator( new DeviceIterPol(m_DeviceList.end()));
}

/**
* Non-static callback methods does not work. This static callback
* function redirects a method call to the EnumDevicesCallback()
* method.
*
* @param lpddi The device that is enumerated
* @param pvRef	 Pointer to user data. In this case pvRef is the this
*               pointer of the class that performs the enumeration
* @author AcrylSword
*/
BOOL CALLBACK VDIInputManager::StaticDIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef )
{
	return ((VDIInputManager*) pvRef)->EnumDevicesCallback(lpddi);
}

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
