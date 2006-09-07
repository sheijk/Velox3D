/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//  InputExample
//  @author AcrlySword
// 
//  In this example I will describe the use of the velox input service.      //  
//  In the beginning we will query the input manager and gain access to the  //
//  standard keyboard and mouse device.                                      //
//  After that I will introduce the enumeration methods that provides access //
//  every real hardware buttons and axises.
//
//  At the end I will show how to print every input action to vout           //
#include "VInputExample.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VLogging.h>
#include <v3d/Core/VIOStream.h>
#include <v3d/Updater/IVUpdateManager.h>
#include <v3d/Window/IVWindow.h>
#include <v3d/Window/IVWindowManager.h>
#include <v3d/System/IVSystemManager.h>
#include <v3d/Input/IVInputManager.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
namespace example{
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::updater;
using namespace v3d::console;
using namespace v3d::window;
using namespace v3d::system;
using namespace v3d::input;

vint VInputExample::Main()
{
//	Velox Apps need some initialisation. So we get a service pointer the the //
//  system, update and window manager and the console service.               //
//  We need the system and update manager to be able to react on the         //
//	different input events. The window manager provides access the the input //
//	manager. The console service is used to print the input data.            //

	VServicePtr<IVSystemManager>	pSystemManager;
	VServicePtr<IVWindowManager>	pWindowManager;
	VServicePtr<IVConsoleService>	pConsole;
	VServicePtr<IVUpdateManager>	pUpdateManager;

	//m_pUpdateManager = QueryObject<IVUpdateManager>("updater.service");
	
	IVWindowManager::IVWindowPtr pWindow = pWindowManager->QueryWindow("app");

//  We have a valid window pointer with Window and can query the input       //
//  manager. After this step the input service is ready to use.              //

	IVInputManager& InputManager = pWindow->QueryInputManager();

//	Now we want to gain access to the standard keyboard device. The method   //
//	to do this is IVInputManager::GetStandardKeyboard()                      //

	IVKeyboardDevice& Keyboard = InputManager.GetStandardKeyboard();

//	We are ready to use the method declared in the IVKeyboardDevice to get   //
//	the state of certain buttons.                                            //
//  The Velox input service uses virtual keycodes declared in                //
//	Input/VKeyCodes.h. Every virtual keycode has an associated IVButton. So  //
//	lets declare some IVButtons to gain acess to the escape and cursor       //
//	buttons.

	IVButton& EscapeKey = Keyboard.GetKey(KeyEscape);
	IVButton& UpKey = Keyboard.GetKey(KeyUp);
	IVButton& DownKey = Keyboard.GetKey(KeyDown);
	IVButton& LeftKey = Keyboard.GetKey(KeyLeft);
	IVButton& RightKey = Keyboard.GetKey(KeyRight);

//  With the IVButton::IsDown() method you can check wether to button is     //
//  currently pressed or not.                                                //
//  We will see this later in the example. For now we go on with the stan-   //
//  dard mouse device which is very similiar to the keyboard device.         //
//  First we get the mouse device with the IVInputManager::GetStandardMouse()//
//  method.                                                                  //

	IVMouseDevice& Mouse = InputManager.GetStandardMouse();

//  Now we get the mouse buttons and axes like we did it before with the     //
//  keyboard buttons.                                                        //

	IVButton& LeftButton = Mouse.GetLeftButton();
	IVButton& RightButton = Mouse.GetRightButton();

	IVRelativeAxis& XAxis = Mouse.GetXAxis();
	IVRelativeAxis& YAxis = Mouse.GetYAxis();

//  The IVRelativeAxis::GetLastMovement() returns - as you can guess - the   //
//  last movement the mouse did in axis direction.                           //
//                                                                           //
//  Additionaly, the IVMouseDevice interface provides more methods to acess  //
//  the mouse device. If the mouse has more than a left and right button,    //
//  there this the GetButton(vuint in_Button) to get a certain mouse button. //
//  The total number of buttons can be retrieved using the GetButtonCount()  //
//  method.                                                                  //

//  Until now we only had access to the standard mouse and keyboard devices  //
//  The IVInputManager interface provides also enumeration methods to get    //
//  a more generall acess to the connected input devices.                    //
//  As example I will show how to use this enumeration methods to print the  //
//  name of the enumerated device to vout.                                   //

	for ( IVInputManager::DeviceIterator DeviceIter = InputManager.DeviceBegin();
	      DeviceIter != InputManager.DeviceEnd();
		  ++DeviceIter )
		vout << (*DeviceIter).GetName() << vendl;
 
//  With the help of the IVInputDevice::GetType() method you can cast the    //
//  IVInputDevice to an IVKeyboard or IVMouseDevice.

	if ( (*InputManager.DeviceBegin()).GetType() == IVInputDevice::Keyboard )
		vout << "First device is a keyboard" << vendl;
        //  Cast here	    
	else
		vout << "First device is not a keyboard" << vendl;
    
//	Like the IVInputManager, the IVInputDevice provides a more general       //
//  access to an input device as IVKeyboardDevice or IVMouseDevice do.       //
//  The IVInputDevice interface provides enumeration methods for ervery      //
//  single button, relative or absolute axis.                                //
//  We will use this soon to print every input event to vout. But first we   //
//  to do sóme fucking inits.
    
	pUpdateManager->Start();
	pSystemManager->SetStatus(true);
	pWindow->SetActive();

//  We will enter the main loop now. This is the right place to use vout     //

	while(pSystemManager->GetStatus())
	{

//
// ===>> Problem siehe Ausgabe
//
		vout << XAxis.GetName() << " :" << XAxis.GetLastMovement() << vendl;
		vout << "Iterator: " << (*(Mouse.RelativeAxisBegin())).GetLastMovement() << vendl;
		vout << "Iterator2: " << (*(*InputManager.DeviceBegin()).RelativeAxisBegin()).GetLastMovement() << vendl;

//  The example terminates when Escape is pressed.                           //

		if (EscapeKey.IsDown() == true)
			pSystemManager->SetStatus(false);

//  I want to print all input date to vout in every frame. It's a little bit //
//  confusing but it will do its job.                                        //
//  We will start with a loop over every input device.                       //
/*
		for ( IVInputManager::DeviceIterator DeviceIter = 
				InputManager.DeviceBegin();
			  DeviceIter != InputManager.DeviceEnd();
			  ++DeviceIter )
		{
*/
//  For every device we will enumerate all buttons and axes and print there  //
//  current state to vout.                                                   //
//  The buttons come first:                                                  //
/*
			for ( IVInputDevice::ButtonIterator ButtonIter = 
					(*DeviceIter).ButtonBegin();
				  ButtonIter != (*DeviceIter).ButtonEnd();
				  ++ButtonIter )
			{
				if ( (*ButtonIter).IsDown() )
					vout << (*ButtonIter).GetName() << " is pressed." << vendl;
            }
*/
//  Now the relative axes:                                                   //
/*
			for ( IVInputDevice::RelativeAxisIterator RelAxIter = 
					(*DeviceIter).RelativeAxisBegin();
				  RelAxIter != (*DeviceIter).RelativeAxisEnd();
				  ++RelAxIter )
			{
				vout << (*RelAxIter).GetName() 
					 << ": " << (*RelAxIter).GetLastMovement() << vendl;
   		    }
*/
//  And finaly the absolute axes:                                            //
/*
			for ( IVInputDevice::AbsoluteAxisIterator AbsAxIter = 
				    (*DeviceIter).AbsoluteAxisBegin();
				  AbsAxIter != (*DeviceIter).AbsoluteAxisEnd();
			      ++AbsAxIter )
			{
				vout << (*AbsAxIter).GetName() 
					<< ": " << (*AbsAxIter).GetPosition() << vendl;
			}
*/
//		}

//  In the beginning of this example we had some IVButtons and               //
//  IVRelativeAxises. Lets use them!                                         //
/*
		if ( UpKey.IsDown() )
			vout << "cursor up is pressed" << vendl;
		if ( DownKey.IsDown() )
			vout << "cursor down is pressed" << vendl;
		if ( LeftKey.IsDown() )
			vout << "cursor left is pressed" << vendl;
		if ( RightKey.IsDown() )
			vout << "cursor right is pressed" << vendl;
*/
// Everything done. Go on with velox stuff to start the next frame           //

		pUpdateManager->StartNextFrame();
		pUpdateManager->GetFrameDuration();
	}

//  Exiting...

	pUpdateManager->Stop();
	return 404;

// Axê
}

//-----------------------------------------------------------------------------
} // namespace example
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
