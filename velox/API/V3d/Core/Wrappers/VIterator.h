#ifndef V3D_VITERATOR_H
#define V3D_VITERATOR_H
//-----------------------------------------------------------------------------
#include "VIteratorBases.h"

#include <iterator>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
// iterator classes

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

template<typename T, typename SmartPtr>
struct std::iterator_traits< v3d::VOutputIterator<T, SmartPtr> > 
	: public v3d::VIterTraitsBase< v3d::VOutputIterator<T, SmartPtr> >
{
	typedef std::output_iterator_tag iterator_category;
};

template<typename T, typename SmartPtr>
struct std::iterator_traits< v3d::VInputIterator<T, SmartPtr> > 
	: public v3d::VIterTraitsBase< v3d::VInputIterator<T, SmartPtr> >
{
	typedef std::input_iterator_tag iterator_category;
};

template<typename T, typename SmartPtr>
struct std::iterator_traits< v3d::VForwardIterator<T, SmartPtr> > 
	: public v3d::VIterTraitsBase< v3d::VForwardIterator<T, SmartPtr> >
{
	typedef std::forward_iterator_tag iterator_category;
};

template<typename T, typename SmartPtr>
struct std::iterator_traits< v3d::VBidirectionalIterator<T, SmartPtr> > 
	: public v3d::VIterTraitsBase< v3d::VBidirectionalIterator<T, SmartPtr> >
{
	typedef std::bidirectional_iterator_tag iterator_category;
};

template<typename T, typename SmartPtr>
struct std::iterator_traits< v3d::VRandomAccessIterator<T, SmartPtr> > 
	: public v3d::VIterTraitsBase< v3d::VRandomAccessIterator<T, SmartPtr> >
{
	typedef std::random_access_iterator_tag iterator_category;
};
//-----------------------------------------------------------------------------
#endif // V3D_VITERATOR_H
