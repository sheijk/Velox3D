#ifndef V3D_VTESTMANAGER_H
#define V3D_VTESTMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/UnitTests/IVTestManager.h>

#include <list>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

/**
	the unit test manager. manages a list of all available unit tests
	enables tests to register themselves and to output messages
*/
class VTestManager : public IVTestManager
{
protected:
	//! a list of unit tests
	typedef std::list<IVUnitTest*> UnitTestList;

	//! list of common tests
	UnitTestList m_CommonTests;
public:
	VTestManager(VStringParam in_pName);
	virtual ~VTestManager();

	/*!
		adds a common test to the internal list
	*/
	void AddCommonTest(IVUnitTest* in_pTest);

	/*!
		outputs a message at the given level
	*/
	//void OutputDebugMessage(VMessageLevel in_eLevel, const char* in_pszMessage);

	//TODO: den doxygen Verweis richtig machen

	/** @see IVTestManager#CommonTestsBegin */
	virtual TestIterator CommonTestsBegin();

	/** @see IVTestManager#CommonTestsEnd */
	virtual TestIterator CommonTestsEnd();
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTESTMANAGER_H
