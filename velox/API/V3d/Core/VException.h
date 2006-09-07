/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_EXCEPTION_H
#define V3D_EXCEPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>

#include <sstream>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

//TODO: beide Kommentare zu einem verbinden (sheijk)

/**
 * Base class for all Velox exceptions
 * Derive your own velox related exceptions from this class
 */
class VException
{
protected:
	vuint	m_Line;
	VString	m_FileName;
	VString	m_ErrorString;

public:
	VException();
	VException(VStringParam Error, VStringParam File, vuint Line);

	/** returns the line where the exception was thrown */
	vuint GetErrorLine() const;

	/** returns the file where the exception was thrown */
	VStringRetVal GetErrorFile() const;

	/** returns info about the error */
	VStringRetVal GetErrorString() const;

	/** returns an extended error description */
	virtual VStringRetVal GetExtendedErrorString() const;

	/** Creates a short report from file, line and error message */
	VStringRetVal ToString() const;
};

/** Throw an exception and send file and line */
#define V3D_THROW(excep, cause) throw excep(cause, __FILE__, __LINE__)

/** Throw an exception with an extra parameter */
#define V3D_THROWX(excep, cause, xparam)	throw excep(cause, __FILE__, __LINE__, xparam)

/** 
 * Throw an exception and generate the error message using a stringstream:
 * V3D_THROWMSG(VException, "the integer " << i << " is invalid);
 */
#define V3D_THROWMSG(exceptionType, message) \
{ std::stringstream cause; cause << message; throw exceptionType(cause.str().c_str(), __FILE__, __LINE__); }

/**
 * Macro for declaring a new, trivial exception type
 */
#define V3D_DECLARE_EXCEPTION(name, parent) class name : public parent\
{\
public:\
	name(VStringParam error, VStringParam file, vuint line)\
		: parent(error, file, line) {}\
};\

// Start of documentation

/*! \file VException.h
    \brief Exception Stuff.
*/



/*! \class VException
    \brief A base class for easier exception throwing.

	To throw an exception with extended error information, derive a class from VException
	and overload GetExtendedErrorString().
*/

/*! \var vuint VException::m_Line
	\brief Contains the source line in which the exception was thrown
*/

/*! \var std::string VException::m_FileName;
	\brief Contains the source file in which the exception was thrown
*/

/*! \var std::string VException::m_ErrorString
	\brief Contains the error string associated with this exception

	m_ErrorString should contain useful information for debugging.
	m_ErrorString hold the string passed as second parameter to the V3D_THROW makro.
*/

/*! \fn VException::VException()
	\brief Defaul Constructor

	You should not use the default constructor, because the thrown exception will
	not contain any informatio
*/

/*! \fn VException::VException(std::string Error, std::string File, vuint Line)
	\brief Constructor used by V3D_THROW
	\param Error The useful error message
	\param File The filename in which the exception was thrown
	\param Line The line number in which the exception was thrown

	This constructor is used by V3D_THROW. 
	You should use the V3D_THROW macro to create an exception
*/

/*! \fn vuint	VException::GetErrorLine() const
	\brief Returns the line number in which the exception was thrown
	\return The line number
*/

/*! \fn std::string	VException::GetErrorFile() const
	\brief Return the filename in which the exception was thrown
	\return The file name
*/

/*! \fn std::string	 VException::GetErrorString() const
	\brief Returns the errorstring associated with this exception
	\return The error string

	This function return the errorstring passed to the V3D_THROW macro as
	second parameter.
*/

/*! \fn virtual std::string	VException::GetExtendedErrorString() const
	\brief Return extended error information
	\return The extended error string

	This function can be overloaded in derived classes to supply extended error infomation
*/

/*! \def V3D_THROW(excep, cause)
	\brief The macro for throwing Velox3D Exceptions
*/
/*	
	\param excep Type of Exception. Use VException for default.
	\param cause Reason why this exception was thrown. Should contain useful debug information.
*/

//-----------------------------------------------------------------------------
} // namespace v3d
#endif // V3D_VEXCEPTION_H

