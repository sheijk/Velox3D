#ifndef V3D_IVITERATOR_H
#define V3D_IVITERATOR_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * Interface for an iterator. Conatins methods for iterating forward and 
 * backward through a collection, getting the value it currently points at and 
 * checking whether it has reached the end of the collection.
 * Should be interface compatible with STL Iterators for use with STL template
 * algorithms
 * @author sheijk
 */
template<typename TargetType>
class IVIterator
{
public:
	typedef typename TargetType ValueType;

	virtual ~IVIterator() {};

	// overload these functions to implement a custom iterator
	virtual vbool Proceed() = 0;
	virtual vbool MoveBack() = 0;
	virtual vbool HasSubject() = 0;
	virtual ValueType& Get() const = 0;

	// operators, etc. for convenience
	ValueType& operator->() const;
	ValueType* operator*() const;
	vbool operator==(const IVIterator<ValueType>& in_Other);
	vbool operator!=(const IVIterator<ValueType>& in_Other);
	vbool operator==(const ValueType* in_pVal);
	vbool operator!=(const ValueType* in_pVal);
};

//-----------------------------------------------------------------------------
#include "IVIterator.inl"
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVITERATOR_H
