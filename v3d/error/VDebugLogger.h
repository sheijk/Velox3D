#ifndef V3D_VDEBUGLOGGER_H
#define V3D_VDEBUGLOGGER_H
//
// *** VDebugLogger ***
//
// Synopsis:
//
//
// Description:
//
//
// See also:
//
//
#include <list>
#include <Core/VTypes.h>
#include <Core/VSingleton.h>
#include "IVLogDevice.h"


class VDebugLogger : public VSingleton<VDebugLogger>
{
private:
	std::list<IVLogDevice*>				m_LogDevices;
	std::list<IVLogDevice*>::iterator	m_Iter;

public:

	enum eLogMode
	{
		V3D_OK,
		V3D_WARNING,
		V3D_ERROR
	};
			VDebugLogger() {};
			~VDebugLogger();

	vbool	RegisterLogDevice( IVLogDevice* MyLogDevice );
	void	UnregisterLogDevice( IVLogDevice* MyLogDevice );
	void	UnregisterAll();
	void	UnregisterAndFreeAll();

	void	Message( const std::string Message, const eLogMode LogMode = VDebugLogger::V3D_OK );

	void	BeginProgressbar();
	void	UpdateProgressbar( const vfloat32 fIndex );
	void	EndProgressbar();

	void	AddState( const std::string StateName, const std::string StateText );
	void	UpdateState( const std::string StateName, const std::string StateText );
	void	DeleteState( const std::string StateName );

	void	InfoText( const vuint iIndex, const std::string Text );
};
#endif

/*! \class VDebugLogger
	\brief Helper class for easier debugging
*/

/*! \var std::list<VILogDevice*> VDebugLogger::m_LogDevices
	\brief List of all registered VILogDevices.
*/

/*! \var std::list<VILogDevice*>::iterator VDebugLogger::m_Iter
	\brief Iterator for m_LogDevices list
*/

/*! \enum VDebugLogger::eLogMode
	\brief Different types of message logging.
*/

/*! \var VDebugLogger::eLogMode VDebugLogger::V3D_OK
	\brief OK, no error message
*/

/*! \var VDebugLogger::eLogMode VDebugLogger::V3D_WARNING
	\brief WARNING, no error message, but maybe a hint for a future error
*/

/*! \var VDebugLogger::eLogMode VDebugLogger::V3D_ERROR
	\brief ERROR, a error message
*/
			
/*! \fn VDebugLogger::VDebugLogger()
	\brief Default constructor
*/

/*! \fn VDebugLogger::~VDebugLogger()
	\brief Destructor

	The destructor calls UnregisterAndFreeAll()
*/

/*! \fn vbool VDebugLogger::RegisterLogDevice( VILogDevice* MyLogDevice )
	\brief Registers a new VILogDevice
	\param MyLogDevice Pointer to the VILogDevice to be registered
	\return True if LogDevice is registered, false if an error occurs

	RegisterLogDevice checks if MyLogDevice is a valid pointer and if it is already in the list.
	RegisterLogDevice returns false if ether the pointer is invalid or is alread in the list.
	RegisterLogDevice returns true if registration was sucessful.
*/

/*! \fn void VDebugLogger::UnregisterLogDevice( VILogDevice* MyLogDevice )
	\brief Unregisters a VILogDevice
	\param MyLogDevice Pointer to the VILogDevice to be unregistered.

	UnregisterLogDevice erases \MyLogDevice from the list. It does not call the destructor for \MyLogDevice.
*/

/*! \fn void VDebugLogger::UnregisterAll()
	\brief Unregisters all VILogDevices.

	UnregisterAll clears the list. It does not call destructors.
*/

/*! \fn void VDebugLogger::UnregisterAndFreeAll()
	\brief Unregisters all VILogDevices and frees memory.

	\a UnregisterAndFreeAll clears the list and calls the destructor for every VILogDevice.
*/

/*! \fn void VDebugLogger::Message( const std::string Message, const eLogMode LogMode = VDebugLogger::V3D_OK )
	\brief Sends a message to every registerd VILogDevice
	\param Message The message
	\param LogMode A member of the eLogMode enumeration
*/

/*! \fn void VDebugLogger::BeginProgressbar()
	\brief Notifies every registered VILogDevice to begin the progressbar
*/

/*! \fn void VDebugLogger::UpdateProgressbar( const vfloat32 fIndex )
	\brief Notifies every registered VILogDevice to update the progressbar
	\param fIndex Progressbar index between 0.0f and 1.0f
*/

/*! \fn void VDebugLogger::EndProgressbar()
	\brief Notifies every registered VILogDevice to end the progressbar
*/

/*!	\fn void VDebugLogger::AddState( const std::string StateName, const std::string StateText )
	\brief Notifies every registered VILogDevice that they should add a new state
	\param StateName Name of the new state. This is used as an identifier
	\param StateText Text of the new state
*/

/*! \fn void VDebugLogger::UpdateState( const std::string StateName, const std::string StateText )
	\brief Notifies every registered VILogDevice that they should update a state
	\param StateName Name of the state that should be updated.
	\param StateText New text for the state.
*/

/*! \fn	void VDebugLogger::DeleteState( const std::string StateName )
	\brief Notifies every registered VILogDevice that the should delete a state
	\param StateName Name of the state that should be deleted.
*/

/*! \fn void VDebugLogger::InfoText( const vuint iIndex, const std::string Text )
	\brief Notifies every registered VILogDevice that they get a new InfoText
	\param iIndex Index between 0 and 7.
	\param Text Infotext
*/