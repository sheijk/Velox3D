#include "VUnitTestException.h"
//-----------------------------------------------------------------------------

using std::string;
//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

// sollte nie erreicht werden
VUnitTestException::VUnitTestException()
{
}

VUnitTestException::VUnitTestException(
	string in_strReason,
	string in_strFileName,
	vint in_nLineNumber,
	IVUnitTest* in_pUnitTest,
	IVUnitTest::VErrorType in_ErrorType)
{
	m_Line = in_nLineNumber;
	m_FileName = in_strFileName;
	m_ErrorString = in_strReason;
	m_pFailedTest = in_pUnitTest;
	m_ErrorType = in_ErrorType;
}

VUnitTestException::~VUnitTestException()
{
}

std::string VUnitTestException::GetExtendedErrorString() const
{
	// keine erweiterten Informationen verfuegbar
	return GetErrorString();
}

const IVUnitTest * VUnitTestException::GetUnitTest() const
{
	return m_pFailedTest;
}

IVUnitTest::VErrorType VUnitTestException::GetErrorType() const
{
	return m_ErrorType;
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
