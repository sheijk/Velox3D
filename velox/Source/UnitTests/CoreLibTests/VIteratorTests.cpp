#include "VIteratorTests.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <iterator>
#include <algorithm>
#include <list>

#include <v3d/Core/Wrappers/VIterator.h>
#include <v3d/Core/Wrappers/VSTLDerefIteratorPol.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

VIteratorTests::VIteratorTests()
{
	IVTestManager* pTestManager = 0;

	// register unit test
	pTestManager = QueryObject<IVTestManager>("testmngr");

	if( ! pTestManager ) 
	{
		V3D_THROW(VException, "test manager could not be found");
	}

	pTestManager->AddCommonTest(this);
}

VIteratorTests::~VIteratorTests()
{
}

//TODO: add info
void VIteratorTests::GetTestInfo(
	VString& out_TestName, 
	VString& out_SubjectName)
{
	// set the name
	out_TestName = "VIteratorTests";

	// specifiy the subject of the whole thing
	out_SubjectName = "Iterators";
}

//-----------------------------------------------------------------------------
template<typename T>
class VArrayIterImpl : public IVIteratorPol<T>
{
	T* m_pPos;
public:
	VArrayIterImpl(T* pos) : m_pPos(pos) {};

	virtual vbool IsEqual(const IVIteratorPol<T>& in_Other) const 
	{
		return m_pPos == in_Other.Get();
	}

	virtual IVIteratorPol<T>* CreateCopy() const
	{
		return new VArrayIterImpl(m_pPos);
	}

	virtual void Proceed() 
	{
		MoveBy(1);
	}

	virtual void MoveBy(vint in_nDistance) 
	{
		m_pPos += in_nDistance;
	}

	virtual void MoveBack() 
	{
		MoveBy(-1);
	}

	virtual Pointer Get() const
	{
		return m_pPos;
	}
};

template<typename T>
VOutputIterator<T> arrOI(T* pt)
{
	return VOutputIterator<T>(new VArrayIterImpl<T>(pt));
}

template<typename T>
VInputIterator<T> arrII(T* pt)
{
	return VInputIterator<T>(new VArrayIterImpl<T>(pt));
}

template<typename T>
VForwardIterator<T> arrFI(T* pt)
{
	return VForwardIterator<T>(new VArrayIterImpl<T>(pt));
}

template<typename IterType>
IterType arrI(typename IterType::Pointer pt)
{
	return IterType(new VArrayIterImpl<typename IterType::Value>(pt));
}

template<typename OutIter>
void testOutIter()
{
	typedef std::iterator_traits<OutIter>::value_type Value;

	Value src[] = { 0, 1, 2, 3, 4, 5, 99 };
	Value vals[] = { 0, 0, 0, 0, 0, 0, 99 };

	OutIter beg(arrI<OutIter>(vals));

	// output iter test
	std::copy(src, src + 6, beg);

	if( ! std::equal(vals, vals + 6, src) )
	{
		V3D_UNITTEST_ERROR_STATIC("output iter malfunction");
	}
}

template<typename InIter>
void testInIter()
{
	typedef std::iterator_traits<InIter>::value_type Value;

	Value src[] = { 0, 1, 2, 3, 4, 5, 99 };
	Value vals[] = { 0, 1, 2, 3, 4, 5, 99 };

	InIter beg(arrI<InIter>(vals)), end(arrI<InIter>(vals + 6));

	// input iter test
	if( ! equal(beg, end, src) )
	{
		V3D_UNITTEST_ERROR_STATIC("input iter malfunction");
	}
}

template<typename FwdIter>
void testFwdIter()
{
	typedef std::iterator_traits<FwdIter>::value_type Value;

	Value vals[] = { 0, 1, 2, 3, 4, 5, 99 };

	// forward iterator test
	FwdIter it(arrI<FwdIter>(vals));
	FwdIter end(arrI<FwdIter>(vals + 6));

	// test deref
	if( *it != 0 )
	{
		V3D_UNITTEST_ERROR_STATIC("fwd iter op*() malfunction");
	}

	if( it.operator->() != vals )
	{
		V3D_UNITTEST_ERROR_STATIC("fwd iter op->() malfunction");
	}

	// test ++it
	Value i = 0;
	Value t = 0;

	for( ; it != end; ++it, ++i)
	{
		t = *it;

		if( t != i )
		{
			V3D_UNITTEST_ERROR_STATIC("fwd ++it malfunction");
		}
	}

	// test it++
	FwdIter it2(arrI<FwdIter>(vals));

	i = 0;
	t = 0;
	for( ; it2 != end; it2++, i++)
	{
		t = *it2;
		if( t != i )
		{
			V3D_UNITTEST_ERROR_STATIC("fwd ++it malfunction");
		}
	}

	// test compare
	{
		FwdIter a(arrI<FwdIter>(vals+4));
		FwdIter	b(arrI<FwdIter>(vals+4));
		FwdIter c(arrI<FwdIter>(vals));

		if( a != b || !( a == b) )
		{
			V3D_UNITTEST_ERROR_STATIC("fwd iter compare malfunction");
		}

		if( a == c || !( a != c) )
		{
			V3D_UNITTEST_ERROR_STATIC("fwd iter compare malfunction");
		}
	}


	// test iterator copy
	FwdIter it3(arrI<FwdIter>(vals));
	FwdIter it4(it3);

	it3++;

	if( *it4 != 0 )
	{
		V3D_UNITTEST_ERROR_STATIC("fwd iter copy c'tor malfunction");
	}

	// test assignment
	it4 = it3;
	it3++;

	if( *it4 != 1 )
	{
		V3D_UNITTEST_ERROR_STATIC("fwd iter op=(it) malfunction");
	}	

	// test with standard algorithm
	{
		Value src[] = { 0, 1, 2, 3, 4, 5, 99 };
		Value vals[] = { 0, 1, 2, 3, 4, 5, 99 };

		FwdIter begVals(arrI<FwdIter>(vals));
		FwdIter endVals(arrI<FwdIter>(vals + 6));

		// test forward iterator
		Value* pos = std::search(vals, vals + 6, src + 2, src + 4);

		FwdIter p = std::search(begVals, endVals, 
			arrI<FwdIter>(src+2), arrI<FwdIter>(src+4));

		if( p != arrI<FwdIter>(pos) )
		{
			Value* pTmp = &(*p);
			V3D_UNITTEST_ERROR_STATIC("forward iter malfunction");
		}
	}
}

template<typename BidirIter>
void testBidirIter()
{
	typedef typename BidirIter::Value Value;

	const int nValCount = 6;
	Value vals[] = { 0, 1, 2, 3, 4, 5, 99 };
	int i = 0;
	int t = 0;

	BidirIter it(arrI<BidirIter>(vals));
	const BidirIter beg(arrI<BidirIter>(vals));
	const BidirIter end(arrI<BidirIter>(vals + nValCount));

	// test if ++ and -- (prefix + postfix) work correctly
	i = 0;
	for( ; it != end; ++it, ++i )
	{
		t = *it;

		if( t != i )
		{
			V3D_UNITTEST_ERROR_STATIC("bidirect iter: ++it malfunction");
		}
	}

	do 
	{
		it--;
		i--;

		t = *it;

		if( t != i )
		{
			V3D_UNITTEST_ERROR_STATIC("bidirect iter: it-- malfunction");
		}		
	} while( it != beg );

	i = nValCount - 1;
	it = end;
	it--;
	for( ; it != beg; --it, --i)
	{
		t = *it;
		if( t != i )
		{
			V3D_UNITTEST_ERROR_STATIC("bidirect iter: --it malfunction");
		}
	}

	std::reverse_iterator<BidirIter> rit(end);

	i = nValCount - 1;
	for( ; rit != std::reverse_iterator<BidirIter>(beg); ++rit, --i )
	{
		t = *rit;
		if( t != i )
		{
			V3D_UNITTEST_ERROR_STATIC("bidirect iter: rev. iter malfunction");
		}
	}
}

template<typename RandAccIter>
void testRandAccIter()
{
	typedef typename RandAccIter::Value Value;

	// test [] operator
	{
		const int nValCount = 6;
		Value vals[] = { 0, 1, 2, 3, 4, 5, 99 };

		RandAccIter it(arrI<RandAccIter>(vals));

		int t = 0;
		for(int i = 0; i < nValCount; ++i)
		{
			t = it[i];

			if( t != vals[i] )
			{
				V3D_UNITTEST_ERROR_STATIC("RndAccIter: [] malfunction");
			}			
		}
	}

	// test adding/substracting an int
	{
		const int nValCount = 6;
		Value vals[] = { 0, 1, 2, 3, 4, 5, 99 };
		int t;

		const RandAccIter beg(arrI<RandAccIter>(vals));
		const RandAccIter end(arrI<RandAccIter>(vals+nValCount));
		RandAccIter it(arrI<RandAccIter>(vals));

		it += 4;
		t = *it;
		if( t != 4 )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: +=(int) malfunction");
		}

		it -= 3;
		t = *it;
		if( t != 1 )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: -=(int) malfunction");
		}

		it = beg + 3;
		t = *it;
		if( t != 3 )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: it + int malfunction");
		}

		it = end - 1;
		t = *it;
		if( t != nValCount - 1)
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: it - int malfunction");
		}
	}

	// adding and substracting iterators
	{
		const int nValCount = 6;
		Value vals[] = { 0, 1, 2, 3, 4, 5, 99 };
		int t;
		std::iterator_traits<RandAccIter>::difference_type diff;

		const RandAccIter beg(arrI<RandAccIter>(vals));
		const RandAccIter end(arrI<RandAccIter>(vals+nValCount));

		diff = end - beg;
		if( diff != nValCount )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: it - it malfunction");
		}
	}

	// comparing
	{
		const int nValCount = 6;
		Value vals[] = { 0, 1, 2, 3, 4, 5, 99 };
		int t;

		const RandAccIter beg(arrI<RandAccIter>(vals));
		const RandAccIter end(arrI<RandAccIter>(vals));
		const RandAccIter big(arrI<RandAccIter>(vals+nValCount-1));
		const RandAccIter sml(arrI<RandAccIter>(vals+1));
		const RandAccIter val(arrI<RandAccIter>(vals+3));
		const RandAccIter val2(arrI<RandAccIter>(vals+3));

		// test ==/!= for different values
		if( big == sml || !(big != sml) )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: ==/!= malfunction");
		}

		// test ==/!= for equal values
		if( val != val2 || !(val == val2) )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: !=/== malfunction");
		}

		// test >=/<= for different values
		if( sml >= big || !(big >= sml) )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: >= malfunction");
		}

		if( big <= sml || !(sml <= big) )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: <= malfunction");
		}

		// test >=/<= for equal values
		if( !(val >= val2) || !(val2 >= val) )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: >= malfunction");
		}

		if( !(val <= val2) || !(val2 <= val) )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: <= malfunction");
		}

		// test </> for different values
		if( big < sml || !(sml < big) )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: < malfunction");
		}

		if( sml > big || !(big > sml) )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: > malfunction");
		}

		// test </> for equal values
		if( val < val2 || val2 < val )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: < malfunction");
		}

		if( val > val2 || val2 > val )
		{
			V3D_UNITTEST_ERROR_STATIC("RndAccIter: > malfunction");
		}
	}

	//TODO: test with an STL algorithm
}

template<typename Iter, typename STLIter>
Iter listI(STLIter it)
{
	typedef typename Iter::Value Value;
	return Iter(new VSTLDerefIteratorPol<STLIter, Value>(it));
}

void constructList(int* begin, int* end, std::list<int*>& lst)
{
	for( ; begin != end; ++begin)
	{
		lst.push_back(begin);
	}
}

template<typename Iter>
void testWithList()
{
	typedef typename Iter::Value Value;

	vuint valCount = 6;
	int vals[] = { 0, 1, 2, 3, 4, 5, 99 };

	std::list<int*> theList;
	typedef std::list<int*>::iterator ListIter;

	constructList(vals, vals + valCount, theList);

	if( ! std::equal( 
		listI<Iter, ListIter>(theList.begin()), 
		listI<Iter, ListIter>(theList.end()),
		vals ) )
	{
		V3D_UNITTEST_ERROR_STATIC("VSTLDerefIterator failure");
	}
}

//-----------------------------------------------------------------------------

void VIteratorTests::ExecuteTest()
{
	typedef VOutputIterator<int> IntOI;
	typedef VInputIterator<int> IntII;
	typedef VForwardIterator<int> IntFI;
	typedef VBidirectionalIterator<int> IntBI;
	typedef VRandomAccessIterator<int> IntRI;

	testOutIter<IntOI>();

	testInIter<IntII>();

	testOutIter<IntFI>();
	testInIter<IntFI>();
	testFwdIter<IntFI>();

	testOutIter<IntBI>();
	testInIter<IntBI>();
	testFwdIter<IntBI>();
	testBidirIter<IntBI>();

	testOutIter<IntRI>();
	testInIter<IntRI>();
	testFwdIter<IntRI>();
	testBidirIter<IntRI>();
	testRandAccIter<IntRI>();

	testWithList<IntBI>();
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
