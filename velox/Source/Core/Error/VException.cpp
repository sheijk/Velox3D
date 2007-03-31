/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Core/VException.h>
//-----------------------------------------------------------------------------
#ifdef V3D_WIN32
#include <windows.h>
#endif

#include <sstream>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
#include <V3d/Core/VIOStream.h>
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


	vout << "Throwing Exception from [" << in_strFile << "|"
		<< in_nLine << "]: '" << in_strError << "'\n";
	
}

VException::~VException()
{
    //destructor
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

