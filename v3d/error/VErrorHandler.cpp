#include <Error/VErrorHandler.h>
#include <Error/VDebugLogger.h>
#include <Error/VErrorStrings.h>
#include <windows.h>
#include <sstream>

VErrorHandler::VErrorHandler()
{
	m_LastError = VOK;
	m_bShowMessage = false;
	m_bLog = true;
}

vbool VErrorHandler::Check(VRESULT in_eResult)
{
	// Check if there was an error
	if (in_eResult == VOK)
	{
		return true;
	}

	// Handle error
	m_LastError = in_eResult;

	// Build error string
	// [File.cpp|20].Error:
	std::ostringstream StrError;
	StrError << "[" << __FILE__ << "|" << __LINE__ << "]." << GetErrorMessage().c_str() << "\0";

	if (m_bLog == true)
	{
		VDebugLogger::CreateInstance()->Message(StrError.str(), VDebugLogger::V3D_ERROR);
	}
	if (m_bShowMessage)
	{
		MessageBox(NULL, StrError.str().c_str(), "Velox3D Error", MB_OK);
	}

	return false;
}

VRESULT VErrorHandler::GetLastError() const
{
	return m_LastError;
}

std::string VErrorHandler::GetErrorMessage() const
{
	return VErrorStrings[m_LastError];
}

void VErrorHandler::ShowMessageBox(const vbool in_bEnabled)
{ 
	m_bShowMessage = in_bEnabled;
}

void VErrorHandler::Log(const vbool in_bEnabled)
{
	m_bLog = in_bEnabled;
}