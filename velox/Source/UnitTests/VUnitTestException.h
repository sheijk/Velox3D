#ifndef V3D_VUNITTESTEXCEPTION_H
#define V3D_VUNITTESTEXCEPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>

#include "IVUnitTest.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

/**
 * Exception Klasse fuer Unit Tests, soll geworfen werden wenn ein Unit
 * Test einen Fehler feststellt
 */
class VUnitTestException : public VException
{
private:
	VUnitTestException();

public:
	VUnitTestException( std::string in_strReason, 
						std::string in_strFileName, 
						vint in_nLineNumber, 
						IVUnitTest* in_pUnitTest,
						IVUnitTest::VErrorType in_ErrorType);

	virtual ~VUnitTestException();

	const IVUnitTest * GetUnitTest() const;
	IVUnitTest::VErrorType GetErrorType() const;
	std::string GetExtendedErrorString() const ;

private:
	IVUnitTest* m_pFailedTest;
	IVUnitTest::VErrorType m_ErrorType;
};

/** use this macro to throw a unit test exception */
#define V3D_THROW_UNITTEST_ERROR(error_string, error_type) \
	throw VUnitTestException(error_string, __FILE__, __LINE__, this, error_type);

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VUNITTESTEXCEPTION_H
