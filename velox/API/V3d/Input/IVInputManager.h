/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVINPUTMANAGER_2004_08_09_H
#define V3D_IVINPUTMANAGER_2004_08_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Updater/IVUpdateable.h>
#include <v3d/Input/IVInputDevice.h>
#include <v3d/Input/IVKeyboardDevice.h>
#include <v3d/Input/IVMouseDevice.h>
#include <v3d/Input/IVButton.h>
#include <v3d/Input/IVRelativeAxis.h>
#include <v3d/Input/VKeyCode.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
 * Inputmanager interface.
 * Provides access to standard keyboard/mouse devices and provides interator for all
 * attached input controllers
 * @author sheijk
 * @version 2.0
 */
class IVInputManager : public updater::IVUpdateable
{
public:
	typedef VRangeIterator<IVInputDevice> DeviceIterator;
	//typedef VForwardIterator<IVInputDevice>		DeviceIterator;

	virtual						~IVInputManager() {};

	virtual DeviceIterator		DeviceBegin() = 0;
	virtual DeviceIterator		DeviceEnd() = 0;

	virtual IVKeyboardDevice&	GetStandardKeyboard() = 0;
	virtual IVMouseDevice&		GetStandardMouse() = 0;

	virtual IVButton&			GetStandardKey(VKeyCode in_Key) = 0;
	virtual IVRelativeAxis&		GetMouseXAxis() = 0;
	virtual IVRelativeAxis&		GetMouseYAxis() = 0;
	virtual IVButton&			GetLeftMouseButton() = 0;
	virtual IVButton&			GetRightMouseButton() = 0;

	virtual void				Update(vfloat32 in_fSeconds) = 0;
	virtual void				Activate() = 0;
	virtual void				Deactivate() = 0;
	virtual void				SetActive(vbool in_bStatus) = 0;
};
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVINPUTMANAGER_2004_08_09_H

