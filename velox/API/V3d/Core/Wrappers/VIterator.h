#ifndef V3D_VITERATOR_H
#define V3D_VITERATOR_H
//-----------------------------------------------------------------------------
#include "VIteratorBases.h"

#include <iterator>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
// iterator classes

template<
	typename T,
	typename IterBase
>
class VOutputIteratorCustomBase
	: public iterutil::VProceedIterInterface<T, VOutputIteratorCustomBase,
	iterutil::VWriteOnlyIterInterface<
		T, 
		IterBase
	>	>,
	// allow iterator type based template specialisations
	std::output_iterator_tag
{
};

/**
 * output iterator
 * parents: VProceedIterInterface -> VMutableIterInterface -> VIteratorBase
 */
template<
	typename T, 
	typename SmartPtr = typename iterutil::VIteratorDefault<T>::SmartPtr
>
class VOutputIterator 
	: public iterutil::VProceedIterInterface<T, VOutputIterator,
		iterutil::VWriteOnlyIterInterface<T, 
			iterutil::VIteratorBase<T, SmartPtr>
	>	>,
	// allow iterator type based template specialisations
	std::output_iterator_tag
{
	typedef iterutil::VIteratorBase<T, SmartPtr> IterBase;
	
public:
	typedef typename IterBase::IterPointer IterPointer;

	VOutputIterator(IterPointer in_pIter)
	{
		Assign(in_pIter);
	}
};

template<
	typename T, 
	typename IterBase
>
class VInputIteratorCustomBase
	: public
	iterutil::VProceedIterInterface<T, VInputIteratorCustomBase,
		iterutil::VReadOnlyIterInterface<T,
			iterutil::VEqCompIterInterface<T,
				IterBase
	>	>	>,
	// allow iterator type based template specialisations
	std::input_iterator_tag
{
};

/**
 * input iterator
 * parents: VProceedIterInterface -> VConstantIterInterface -> VIteratorBase
 */
template<
	typename T, 
	typename SmartPtr = typename iterutil::VIteratorDefault<T>::SmartPtr
>
class VInputIterator 
	: public
	iterutil::VProceedIterInterface<T, VInputIterator,
		iterutil::VReadOnlyIterInterface<T,
			iterutil::VEqCompIterInterface<T,
				iterutil::VIteratorBase<T, SmartPtr>
	>	>	>,
	// allow iterator type based template specialisations
	std::input_iterator_tag		
{
	typedef iterutil::VIteratorBase<T, SmartPtr> IterBase;

public:
	typedef typename IterBase::IterPointer IterPointer;

	VInputIterator(IterPointer in_pIter)
	{
		Assign(in_pIter);
	}
};

template<
	typename T, 
	typename IterBase
>
class VForwardIteratorCustomBase
	: public 
	iterutil::VProceedIterInterface<T, VForwardIteratorCustomBase,
		iterutil::VMutableIterInterface<T,
			iterutil::VEqCompIterInterface<T,
				IterBase
	>	>	>,
	// allow iterator type based template specialisations
	std::forward_iterator_tag
{
};

/**
 * a forward iterator
 * parents: VProceedIterInterface -> VMutableIterInterface -> VIteratorBase
 */
template<
	typename T, 
	typename SmartPtr = typename iterutil::VIteratorDefault<T>::SmartPtr
>
class VForwardIterator 
	: public 
	iterutil::VProceedIterInterface<T, VForwardIterator,
		iterutil::VMutableIterInterface<T,
			iterutil::VEqCompIterInterface<T,
				iterutil::VIteratorBase<T, SmartPtr>
	>	>	>,
	// allow iterator type based template specialisations
	std::forward_iterator_tag
{
	typedef iterutil::VIteratorBase<T, SmartPtr> IterBase;

public:
	typedef typename IterBase::IterPointer IterPointer;

	VForwardIterator(IterPointer in_pIter)
	{
		Assign(in_pIter);
	}
};

template<
	typename T,
	typename IterBase
>
class VBidirectionalIteratorCustumBase
	: public
	iterutil::VMoveBackIterInterface<T,	VBidirectionalIteratorCustumBase,
		iterutil::VProceedIterInterface<T, VBidirectionalIteratorCustumBase,
			iterutil::VMutableIterInterface<T,
				iterutil::VEqCompIterInterface<T,
					IterBase
	>	>	>	>,
	std::bidirectional_iterator_tag
{
};

/**
 * A bidirectional iterator
 */
template<
	typename T, 
	typename SmartPtr = typename iterutil::VIteratorDefault<T>::SmartPtr
>
class VBidirectionalIterator
	: public 
	iterutil::VMoveBackIterInterface<T,	VBidirectionalIterator,
		iterutil::VProceedIterInterface<T, VBidirectionalIterator,
			iterutil::VMutableIterInterface<T,
				iterutil::VEqCompIterInterface<T,
					iterutil::VIteratorBase<T, SmartPtr>
	>	>	>	>,
	// allow iterator type based template specialisations
	std::bidirectional_iterator_tag
{
	typedef iterutil::VIteratorBase<T, SmartPtr> IterBase;

public:
	typedef typename IterBase::IterPointer IterPointer;

	VBidirectionalIterator(IterPointer in_pIter)
	{
		Assign(in_pIter);
	}
};

template<
	typename T, 
	typename IterBase
>
class VRandomAccessIteratorCustomBase
	: public
	iterutil::VMoveBackIterInterface<T, VRandomAccessIteratorCustomBase,
		iterutil::VProceedIterInterface<T, VRandomAccessIteratorCustomBase,
			iterutil::VRandomMoveIterInterface<T, VRandomAccessIteratorCustomBase,
				iterutil::VMutableIterInterface<T,
					iterutil::VEqCompIterInterface<T,
						IterBase
	>	>	>	>	>,
	// allow iterator type based template specialisations
	std::random_access_iterator_tag
{
};

//TODO: doku
template<
	typename T, 
	typename SmartPtr = typename iterutil::VIteratorDefault<T>::SmartPtr
>
class VRandomAccessIterator
	: public
	iterutil::VMoveBackIterInterface<T, VRandomAccessIterator,
		iterutil::VProceedIterInterface<T, VRandomAccessIterator,
			iterutil::VRandomMoveIterInterface<T, VRandomAccessIterator,
				iterutil::VMutableIterInterface<T,
					iterutil::VEqCompIterInterface<T,
						iterutil::VIteratorBase<T, SmartPtr>
	>	>	>	>	>,
	// allow iterator type based template specialisations
	std::random_access_iterator_tag
{
	typedef iterutil::VIteratorBase<T, SmartPtr> IterBase;

public:
	typedef typename IterBase::IterPointer IterPointer;

	VRandomAccessIterator(IterPointer in_pIter)
	{
		Assign(in_pIter);
	}
};

//TODO: vollstaendige Iterator Anforderungen
//TODO: .inl files erstellen

/**
 * base class for iterator traits for velox iterators
 */
template<typename Iter>
struct VIterTraitsBase
{
	typedef typename Iter::Value value_type;
	typedef typename Iter::Pointer pointer;
	typedef typename Iter::Reference reference;
	typedef typename Iter::DifferenceType difference_type;
	typedef difference_type distance_type;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------

/**
 * template specialisations for iterator_traits for velox iterators
 */

#define V3D_DECLARE_ITER_TRAITS(IterType, IterCategory)			\
	template<typename T, typename SmartPtr>						\
	struct std::iterator_traits< IterType <T, SmartPtr> >		\
		: public v3d::VIterTraitsBase< IterType<T, SmartPtr> >	\
	{															\
		typedef std::IterCategory iterator_category;			\
	};

V3D_DECLARE_ITER_TRAITS(v3d::VOutputIterator, output_iterator_tag)
V3D_DECLARE_ITER_TRAITS(v3d::VInputIterator, input_iterator_tag)
V3D_DECLARE_ITER_TRAITS(v3d::VForwardIterator, forward_iterator_tag)
V3D_DECLARE_ITER_TRAITS(v3d::VBidirectionalIterator, bidirectional_iterator_tag)
V3D_DECLARE_ITER_TRAITS(v3d::VRandomAccessIterator, random_access_iterator_tag)

V3D_DECLARE_ITER_TRAITS(v3d::VOutputIteratorCustomBase, output_iterator_tag)
V3D_DECLARE_ITER_TRAITS(v3d::VInputIteratorCustomBase, input_iterator_tag)
V3D_DECLARE_ITER_TRAITS(v3d::VForwardIteratorCustomBase, forward_iterator_tag)
V3D_DECLARE_ITER_TRAITS(v3d::VBidirectionalIteratorCustumBase, bidirectional_iterator_tag)
V3D_DECLARE_ITER_TRAITS(v3d::VRandomAccessIteratorCustomBase, random_access_iterator_tag)

#undef V3D_DECLARE_ITER_TRAITS
//-----------------------------------------------------------------------------
#endif // V3D_VITERATOR_H
