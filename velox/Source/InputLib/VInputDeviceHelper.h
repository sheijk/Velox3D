#ifndef V3D_VINPUTDEVICEHELPER_2004_08_18_H
#define V3D_VINPUTDEVICEHELPER_2004_08_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VIterator.h>
#include <v3d/Input/IVInputDevice.h>
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

	std::map<vlong, VDIButton*>		  m_ButtonMap;
	std::map<vlong, VDIRelativeAxis*> m_RelativeAxisMap;
	std::map<vlong, VDIAbsoluteAxis*> m_AbsoluteAxisMap;

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