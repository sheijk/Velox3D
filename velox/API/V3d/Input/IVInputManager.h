#ifndef V3D_IVINPUTMANAGER_H
#define V3D_IVINPUTMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//#include <v3d/Core/VNamedObject.h>
#include <v3d/Core/Wrappers/VIterator.h>
#include <v3d/Updater/IVUpdateable.h>
#include <v3d/Input/IVInputDevice.h>
#include <v3d/Input/IVButton.h>
#include <v3d/Input/IVRelativeAxis.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {

//-----------------------------------------------------------------------------
/**
 * Inputmanager interface.
 * Provides access to standard keyboard/mouse devices and provides interator for all
 * attached input controllers
 * @author AcrylSword
 * @version 1.0
 */
class IVInputManager : public updater::IVUpdateable //: public VNamedObject
{
	//IVInputManager() {;};

	public:
/*
		IVInputManager(VStringParam in_strName, VNamedObject* in_pParent) 
			: VNamedObject(in_strName, in_pParent)
		{
		}
*/
	
	enum KeyCode
	{
		Escape,
		Enter,
		Space,
		CursorLeft,
		CursorRight,
		CursorUp,
		CursorDown,
	};

	typedef VForwardIterator<IVInputDevice>		DeviceIterator;

	virtual						~IVInputManager() {};

	virtual DeviceIterator		DeviceBegin() = 0;
	virtual DeviceIterator		DeviceEnd() = 0;

	virtual IVButton&			GetStandardKey( KeyCode Key ) = 0;
	
	virtual IVRelativeAxis&		GetMouseXAxis() = 0;
	virtual IVRelativeAxis&		GetMouseYAxis() = 0;
	virtual IVButton&			GetMouseButton( vuint in_iButton ) = 0;

	virtual void				Update(vfloat32 in_fSeconds) = 0;
	virtual void				Activate() = 0;
	virtual void				Deactivate() = 0;
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVINPUTMANAGER_H
