#include "VInputDeviceHelper.h"
#include <v3d/Input/IVButton.h>
#include <v3d/Input/IVRelativeAxis.h>
#include <v3d/Input/IVAbsoluteAxis.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

VInputDeviceHelper::VInputDeviceHelper() : m_Released(false)
{
}

/**
 * The destructor performs a delete on all elements in the axis
 * and button lists, sets the pointers to 0 and clears the lists
 * @see deleteAll
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

VInputDeviceHelper::~VInputDeviceHelper()
{
	Release();
}

void VInputDeviceHelper::Release()
{
	if (!m_Released)
	{
        deleteAll(m_ButtonList.begin(), m_ButtonList.end());
		m_ButtonList.clear();

		deleteAll(m_RelativeAxisList.begin(), m_RelativeAxisList.end());
		m_RelativeAxisList.clear();

		deleteAll(m_AbsoluteAxisList.begin(), m_AbsoluteAxisList.end());
		m_AbsoluteAxisList.clear();
	}
}

/**
 * Returns a Velox iterator pointing to the beginning of an std::list
 * @return A iterator pointing to the beginning of the button list
 * @author AcrylSword
 */
IVInputDevice::ButtonIterator VInputDeviceHelper::ButtonBegin()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIButton*>::iterator, IVButton> ButtonIterPol;
	//return IVInputDevice::ButtonIterator( new ButtonIterPol(m_ButtonList.begin()) );
	return CreateDerefBeginIterator<IVButton>(m_ButtonList);
}

/**
* Returns a Velox iterator pointing to the end of an std::list
* @return A iterator pointing to the end of the button list
* @author AcrylSword
*/
IVInputDevice::ButtonIterator VInputDeviceHelper::ButtonEnd()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIButton*>::iterator, IVButton> ButtonIterPol;
	//return IVInputDevice::ButtonIterator( new ButtonIterPol(m_ButtonList.end()) );
	return CreateDerefEndIterator<IVButton>(m_ButtonList);
}

/**
* Returns a Velox iterator pointing to the beginning of an std::list
* @return A iterator pointing to the beginning of the absolute axis list
* @author AcrylSword
*/
IVInputDevice::AbsoluteAxisIterator VInputDeviceHelper::AbsoluteAxisBegin()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIAbsoluteAxis*>::iterator,
	//							 IVAbsoluteAxis> AbsoluteAxisIterPol;
	//return IVInputDevice::AbsoluteAxisIterator( new AbsoluteAxisIterPol(m_AbsoluteAxisList.begin()));
	return CreateDerefBeginIterator<IVAbsoluteAxis>(m_AbsoluteAxisList);
}

/**
* Returns a Velox iterator pointing to the end of an std::list
* @return A iterator pointing to the end of the absolute axis list
* @author AcrylSword
*/
IVInputDevice::AbsoluteAxisIterator VInputDeviceHelper::AbsoluteAxisEnd()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIAbsoluteAxis*>::iterator,
	//							 IVAbsoluteAxis> AbsoluteAxisIterPol;
	//return IVInputDevice::AbsoluteAxisIterator( new AbsoluteAxisIterPol(m_AbsoluteAxisList.end()));
	return CreateDerefEndIterator<IVAbsoluteAxis>(m_AbsoluteAxisList);
}

/**
* Returns a Velox iterator pointing to the beginning of an std::list
* @return A iterator pointing to the beginning of the relative axis list
* @author AcrylSword
*/
IVInputDevice::RelativeAxisIterator VInputDeviceHelper::RelativeAxisBegin()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIRelativeAxis*>::iterator,
	//							 IVRelativeAxis> RelativeAxisIterPol;
	//return IVInputDevice::RelativeAxisIterator( new RelativeAxisIterPol(m_RelativeAxisList.begin() ));
	return CreateDerefBeginIterator<IVRelativeAxis>(m_RelativeAxisList);
}

/**
* Returns a Velox iterator pointing to the end of an std::list
* @return A iterator pointing to the end of the relative axis list
* @author AcrylSword
*/
IVInputDevice::RelativeAxisIterator VInputDeviceHelper::RelativeAxisEnd()
{
	//typedef VSTLDerefIteratorPol<std::list<VDIRelativeAxis*>::iterator,
	//							 IVRelativeAxis> RelativeAxisIterPol;
	//return IVInputDevice::RelativeAxisIterator( new RelativeAxisIterPol(m_RelativeAxisList.end()));
	return CreateDerefEndIterator<IVRelativeAxis>(m_RelativeAxisList);
}
//-----------------------------------------------------------------------------
}; // namespace input
}; // namespace v3d
//-----------------------------------------------------------------------------
