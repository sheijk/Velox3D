#ifndef VTestManager_h
#define VTestManager_h

#include <unittests/VCommonTestBase.h>
#include <list>
#include <memory>

class IVUnitTest;
class VCommonTestBase;
class VTestExecuter;

/*!
	the unit test manager. manages a list of all available unit tests
	enables tests to register themselves and to output messages
*/
class VTestManager  
{
protected:
	// enable deletion of singleton object by the auto ptr
	friend std::auto_ptr<VTestManager>;

	// it's a singleton, baby ;)
	VTestManager();
	VTestManager(const VTestManager&);
	operator=(const VTestManager&);
	virtual ~VTestManager();

	//! static instance of VTestManager
	static std::auto_ptr<VTestManager> s_pTestManager;

	//! a list of unit tests
	typedef std::list<IVUnitTest*> UnitTestList;

	//! list of common tests
	UnitTestList m_CommonTests;
public:
	/*!
		return the singleton instance
	*/
	static VTestManager& GetInstance();

	/*!
		adds a common test to the internal list
	*/
	void AddCommonTest(VCommonTestBase *in_pTest);

	/*!
		warning level for messages.
		VMessage - simple messages
		VWarning - warnings
		VError - information about an error
	*/
	enum VMessageLevel
	{
		VMessage,
		VWarning,
		VError
	};

	/*!
		outputs a message at the given level
	*/
	void OutputDebugMessage(VMessageLevel in_eLevel, const char* in_pszMessage);

	// enumeration of tests:
	typedef UnitTestList::iterator TestIterator;

	/*!
		get iterator to first common test
	*/
	TestIterator CommonTestsBegin();

	/*!
		get iterator to last common test
	*/
	TestIterator CommonTestsEnd();
};

#endif // !defined(AFX_VTESTMANAGER_H__67337D26_0C87_4BE3_96BA_9C809A00FA50__INCLUDED_)
