#include "VTestManager.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------
using namespace std;


VTestManager::VTestManager(VStringParam in_strName) :
	IVTestManager(in_strName, 0)
{
}

VTestManager::~VTestManager()
{

}

void VTestManager::AddCommonTest(IVUnitTest* in_pTest)
{
	// check for 0 pointer
	if( in_pTest != 0 )
	{
		// add tests to list
		m_CommonTests.push_back((IVUnitTest*)in_pTest);
	}
}

//void VTestManager::OutputDebugMessage(VMessageLevel in_eLevel, const char* in_pszMessage)
//{
//	// check output level
//	// if output level is allowed for output
//		// output message
//}

template<
	typename Iter,
	typename T
>
class VSTLDerefIteratorPol : public IVIteratorPol<T>
{
private:
	Iter m_Iter;

public:
	typedef T Value;
	typedef T* Pointer;

	VSTLDerefIteratorPol(Iter in_Iter) : m_Iter(in_Iter) {}

	virtual vbool IsEqual(const IVIteratorPol<T>& in_Other) const
	{ return *m_Iter == in_Other.Get(); }

	virtual VSTLDerefIteratorPol* CreateCopy() const
	{ return new VSTLDerefIteratorPol(m_Iter); }

	virtual void MoveBy(vint in_nDistance)
	{
		advance(m_Iter, in_nDistance);
	}

	virtual Pointer Get() const
	{
		return *m_Iter;
	}

	virtual void Proceed() { MoveBy(1); }
	virtual void MoveBack() { MoveBy(-1); }
};

VTestManager::TestIterator VTestManager::CommonTestsBegin()
{
	typedef VSTLDerefIteratorPol<UnitTestList::iterator, IVUnitTest> IterPol;

	TestIterator theIter(new IterPol(m_CommonTests.begin()));

	return theIter;
}

VTestManager::TestIterator VTestManager::CommonTestsEnd()
{
	typedef VSTLDerefIteratorPol<UnitTestList::iterator, IVUnitTest> IterPol;

	TestIterator theIter(new IterPol(m_CommonTests.end()));

	return theIter;
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
