#ifndef V3D_VUNITTESTEXCEPTION_H
#define V3D_VUNITTESTEXCEPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVUnitTest.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

//TODO: leserlich machen (sheijk)
//TODO: kommentare aktualisieren (sheijk)

/**
 * Exception Klasse fuer Unit Tests, soll geworfen werden wenn ein Unit
 * Test einen Fehler feststellt
 */
class VUnitTestException : public VException
{
public:
	//! result of a unit test
	enum ErrorLevel
	{
		// warning, minor problems which wont affect the functionality
		Warning,
		//! error, a tested functionality did not work
		Error,
		/*! an error which would affect the stability of other system, 
		crashes, illegal memory operations etc. */
		CriticalError
	};

	VUnitTestException( VStringParam in_strReason, 
						VStringParam in_strFileName, 
						vint in_nLineNumber, 
						const IVUnitTest* in_pUnitTest,
						ErrorLevel in_ErrorLevel)
						:
						VException(in_strReason, in_strFileName, in_nLineNumber)
	{
		m_pFailedTest = in_pUnitTest;
		m_ErrorLevel = in_ErrorLevel;
	}

	//TODO: Konv. c'tor von VException

	virtual ~VUnitTestException() {};

	const IVUnitTest* GetUnitTest() const
	{
		return m_pFailedTest;
	}

	ErrorLevel GetErrorLevel() const
	{
		return m_ErrorLevel;
	}

private:
	const IVUnitTest* m_pFailedTest;
	ErrorLevel m_ErrorLevel;
};

/** use this macro to throw a unit test exception */
#define V3D_THROW_UNITTEST_ERROR(error_string, error_type) \
	throw VUnitTestException(error_string, __FILE__, __LINE__, this, error_type);

/** use this macro to throw an unit test exception from a static function */
#define V3D_THROW_UNITTEST_ERROR_STATIC(errorString, errorType) \
	throw VUnitTestException(errorString, __FILE__, __LINE__, 0, errorType);
//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VUNITTESTEXCEPTION_H
