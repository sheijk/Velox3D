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
 * @version 1.0
 * @generator Enterprise Architect
 * @created 04-Jun-2003 00:53:28
 */
template<typename SubjectType>
class IVIterator
{
public:
	virtual ~IVIterator() {};

	virtual vbool Proceed() = 0;
	virtual vbool MoveBack() = 0;
	virtual vbool HasSubject() = 0;
	virtual T* Get() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVITERATOR_H
