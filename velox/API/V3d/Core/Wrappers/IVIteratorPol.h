#ifndef V3D_IVITERATORPOL_H
#define V3D_IVITERATORPOL_H
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
class IVIteratorPol
{
public:
	typedef typename TargetType Value;
	typedef typename TargetType* Pointer;

	virtual ~IVIteratorPol() {};

	// overload these functions to implement a custom iterator
	/** checks if both iterators are equal */
	virtual vbool IsEqual(const IVIteratorPol& in_Other) const = 0;

	/** creates a copy of itself */
	virtual IVIteratorPol* CreateCopy() const = 0;
	
	/** proceed to next element in sequence */
	virtual void Proceed() = 0;

	/** move n elements forward or backward */
	virtual void MoveBy(vint in_nDistance) = 0;

	/** moves to previous element in sequence */
	virtual void MoveBack() = 0;

	/** returns a pointer to the element it points to */
	virtual Pointer Get() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVITERATORPOL_H
