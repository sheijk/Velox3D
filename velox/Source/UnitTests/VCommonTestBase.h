#ifndef V3D_VCOMMONTESTBASE_H
#define V3D_VCOMMONTESTBASE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "IVUnitTest.h"
#include "VUnitTestException.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

/*!
	the base class for common unit tests.
	common unit tests are tests that are regularely processed
	to ensure the correctness of all existing code
*/
class VCommonTestBase : public IVUnitTest  
{
private:
	VCommonTestBase(const VCommonTestBase&);
	void operator=(const VCommonTestBase&);

protected:
	/** registers the test to the test manager */
	VCommonTestBase();

	virtual ~VCommonTestBase();
public:
	/** @see IVUnitTest::GetTestInfo */
	virtual void GetTestInfo(
		std::string& out_TestName, 
		std::string& out_SubjectName) = 0;

	/** @see IVUnitTest::ExecuteTest */
	virtual void ExecuteTest() = 0;
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCOMMONTESTBASE_H