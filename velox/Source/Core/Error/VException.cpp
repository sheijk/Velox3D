#include <v3d/Core/VException.h>
//-----------------------------------------------------------------------------
#include <windows.h>

#include <sstream>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VException::VException()
{
	m_Line = 0;
	m_FileName = "VException File\n";
	m_ErrorString = "VException Error\n";
}

VException::VException(
	VStringParam in_strError, VStringParam in_strFile, vuint in_nLine)
{
	m_Line = in_nLine;
	m_FileName = in_strFile;
	m_ErrorString = in_strError;


	std::stringstream message;
	message << "Throwing Exception from [" << in_strFile << "|"
		<< in_nLine << "]: '" << in_strError << "'\n";
	
	OutputDebugString(message.str().c_str());
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

VStringRetVal VException::ToString() const
{
	std::stringstream report;
	report << "[" << GetErrorFile() << "|" << GetErrorLine() << "] "
		<< GetErrorString();

	std::string reportmsg = report.str();

	return VString(reportmsg.c_str());
}

//-----------------------------------------------------------------------------
} // namespace v3d
