#include <v3d/Core/VException.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VException::VException()
{
	m_Line = 0;
	m_FileName = "VException File\n";
	m_ErrorString = "VException Error\n";
}

VException::VException(VStringParam Error, VStringParam File, vuint Line)
{
	m_Line = Line;
	m_FileName = File;
	m_ErrorString = Error;
}

vuint VException::GetErrorLine() const
{
	return m_Line;
}

VStringRetVal VException::GetErrorFile() const
{
	return m_FileName;
}

VStringRetVal VException::GetErrorString() const
{
	return m_ErrorString;
}

VStringRetVal VException::GetExtendedErrorString() const
{
	return "No extended error string avaible\n";
}

//-----------------------------------------------------------------------------
} // namespace v3d
