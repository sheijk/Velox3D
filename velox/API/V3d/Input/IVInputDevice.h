/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVINPUTDEVICE_09_02_2004_H
#define V3D_IVINPUTDEVICE_09_02_2004_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//#include <v3d/Core/Wrappers/VIterator.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>
#include <v3d/Input/IVButton.h>
#include <v3d/Input/IVRelativeAxis.h>
#include <v3d/Input/IVAbsoluteAxis.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
 * Interface for an attached input controller
 * @author sheijk
 * @version 1.0
 */

class IVInputDevice
{
public:
	enum DeviceType
	{
		Keyboard,
		Mouse,
		Joystick,
		Undefined
	};

	typedef VRangeIterator<IVButton> ButtonIterator;
	typedef VRangeIterator<IVRelativeAxis> RelativeAxisIterator;
	typedef VRangeIterator<IVAbsoluteAxis> AbsoluteAxisIterator;
	//typedef VForwardIterator<IVButton>		 ButtonIterator;
	//typedef VForwardIterator<IVRelativeAxis> RelativeAxisIterator;
	//typedef VForwardIterator<IVAbsoluteAxis> AbsoluteAxisIterator;
    
	virtual							~IVInputDevice() {};

	virtual VStringRetVal			GetName() = 0;
	virtual DeviceType				GetType() = 0;

	virtual ButtonIterator			ButtonBegin() = 0;
	virtual ButtonIterator			ButtonEnd() = 0;

	virtual AbsoluteAxisIterator	AbsoluteAxisBegin() = 0;
	virtual AbsoluteAxisIterator	AbsoluteAxisEnd() = 0;

	virtual RelativeAxisIterator	RelativeAxisBegin() = 0;
	virtual RelativeAxisIterator	RelativeAxisEnd() = 0;
};
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVINPUTDEVICE_09_02_2004_H
