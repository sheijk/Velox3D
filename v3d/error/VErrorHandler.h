#ifndef V3D_VERRORHANDLER_H
#define V3D_VERRORHANDLER_H

#include <string>
#include <Core/VTypes.h>

class VErrorHandler
{
private:
	VRESULT		m_LastError;
	vbool		m_bShowMessage;
	vbool		m_bLog;
	std::string m_sErrorstring;

public:
				VErrorHandler();

	vbool		Check( const VRESULT Result );
	VRESULT		GetLastError() const;
	std::string	GetErrorMessage() const;

	void		ShowMessageBox( vbool Enabled );
	void		Log( vbool Enabled );
};
#endif

/*! \class VErrorHandler
	\brief A class for basic error handling
*/

/*! \var VRESULT VErrorHandler::m_LastError
	\brief Contains the last checked error code

	Contains the last checked error code (checked with VErrorHandler::Check()).
*/

/*! \var vbool VErrorHandler::m_bShowMessage
	\brief Show messagebox true/false

	Contains status information wheter a messagebox should be shown or not, when an error occurs
*/

/*! \var vbool VErrorHandler::m_bLog
	\brief Log errors to DebugLogger true/false
*/

/*! \var std::string VErrorHandler::m_sErrorstring
	\brief Contains last error message
*/

/*! \fn VErrorHandler::VErrorHandler()
	\brief Default constructor

	Initializes member variables
*/

/*! \fn vbool VErrorHandler::Check( const VRESULT Result )
	\brief Checks an error code
	\param Result Error code to check

	Checks an error code and stores error code in m_LastError
*/

/*! \fn VRESULT VErrorHandler::GetLastError() const
	\brief Returns the last error code
	\return The error code
*/

/*! \fn std::string	VErrorHandler::GetErrorMessage() const
	\brief Returns the error message of the last error
	\return The error message
*/

/*! \fn void VErrorHandler::ShowMessageBox( vbool Enabled )
	\brief ??? 
*/

/*! \fn void VErrorHandler::Log( vbool Enabled )
	\brief ???
*/