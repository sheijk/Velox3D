#include <v3d/Core/VException.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VException::VException()
{
	m_Line = 0;
	m_FileName = "VException File\n";
	m_ErrorString ="VException Error\n";
}

VException::VException(std::string Error, std::string File, vuint Line)
{
	m_Line = Line;
	m_FileName = File;
	m_ErrorString = Error;
}

vuint
VException::GetErrorLine() const
{
	return m_Line;
}

std::string
VException::GetErrorFile() const
{
	return m_FileName;
}

std::string
VException::GetErrorString() const
{
	return m_ErrorString;
}


std::string
VException::GetExtendedErrorString() const
{
	return std::string("No extended error string avaible\n");
}

//-----------------------------------------------------------------------------
} // namespace v3d
