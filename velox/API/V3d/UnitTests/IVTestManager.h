#ifndef V3D_IVTESTMANAGER_H
#define V3D_IVTESTMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VNamedObject.h>
#include <v3d/Core/Wrappers/IVIterator.h>
#include <v3d/Core/SmartPtr/VGuards.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

class IVUnitTest;

/**
 * The unit test manager. manages a list of all available unit tests and
 * enables tests to register themselves
 */
class IVTestManager : public VNamedObject
{
public:
	IVTestManager(VStringParam in_strName, const VNamedObject* in_pParent) :
	  VNamedObject(in_strName, in_pParent) {};

	/**
	 * adds a common test to the internal list
	 */
	virtual void AddCommonTest(IVUnitTest* in_pTest) = 0;

	///**
	// * warning level for messages.
	// */
	//enum MessageLevel
	//{
	//	/** simple messages */
	//	Message,
	//	/** a warning: should be fixed but is not critical */
	//	Warning,
	//	/** an error: needs to be fixed */
	//	Error
	//};

	///**
	// * outputs a message at the given level
	// */
	//void OutputDebugMessage(VMessageLevel in_eLevel, const char* in_pszMessage);

	/** enumeration of tests: */
	typedef IVIterator<IVUnitTest*> TestIterator;
	typedef VPointer<TestIterator>::AutoPtr TestIteratorPtr;

	/**
	 * get iterator to first common test
	 */
	virtual TestIteratorPtr CommonTestsBegin() = 0;

	/**
	 * get iterator to last common test
	 */
	virtual TestIteratorPtr CommonTestsEnd() = 0;
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVTESTMANAGER_H
