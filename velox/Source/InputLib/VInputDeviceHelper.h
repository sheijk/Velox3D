/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VINPUTDEVICEHELPER_2004_08_18_H
#define V3D_VINPUTDEVICEHELPER_2004_08_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>
#include <V3d/Input/IVInputDevice.h>
#include <list>
#include <map>
#include "VDIButton.h"
#include "VDIAbsoluteAxis.h"
#include "VDIRelativeAxis.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
 * VInputDeviceHelper provides a standard implementation of iterator methods
 * in the IVInputDevice interface. 
 * VInputDevice contains three std::lists for pointers to button, relative
 * and absolute axis objects. On destruction these objects are deleted and
 * the lists are cleared.
 * To use this helper, just delegate method calls to this class
 *
 * @author AcrylSword
 * @see IVInputDevice
 */
class VInputDeviceHelper
{
	vbool m_Released;
public:
	typedef std::list<VDIButton*>::iterator		  STLButtonIter;
	typedef std::list<VDIRelativeAxis*>::iterator STLRelativeIter;
	typedef std::list<VDIAbsoluteAxis*>::iterator STLAbsoluteIter;

	std::list<VDIButton*>			m_ButtonList;
	std::list<VDIRelativeAxis*>		m_RelativeAxisList;
	std::list<VDIAbsoluteAxis*>		m_AbsoluteAxisList;

	VInputDeviceHelper();
	~VInputDeviceHelper();

	void Release();

	IVInputDevice::ButtonIterator		ButtonBegin();
	IVInputDevice::ButtonIterator		ButtonEnd();

	IVInputDevice::AbsoluteAxisIterator	AbsoluteAxisBegin();
	IVInputDevice::AbsoluteAxisIterator	AbsoluteAxisEnd();

	IVInputDevice::RelativeAxisIterator	RelativeAxisBegin();
	IVInputDevice::RelativeAxisIterator	RelativeAxisEnd();
};
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VINPUTDEVICEHELPER_2004_08_18_H
