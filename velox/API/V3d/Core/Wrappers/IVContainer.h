#ifndef V3D_IVCONTAINER_H
#define V3D_IVCONTAINER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * A general purpose interface for a container. Can be used for interfaces
 * where containers are needed, instead of stl containers
 */
template<typename SubjectType>
class IVContainer
{
public:
	/** the container's iterator type */
	typedef IVIterator<SubjectType> Iterator;

	/** use an auto ptr to assure iterator destruction */
	typedef VPointer<Iterator>::AutoPtr IteratorPtr;

	virtual ~IVContainer() {};

	/** add an element, pos. is undefinded */
	virtual void Add(const SubjectType& in_NewObject) = 0;

	/** remove element at position in_Pos */
	virtual void Remove(Iterator in_Pos) = 0;

	/** insert an element before in_Pos */
	virtual void Insert(const SubjectType& in_NewObject, Iterator in_Pos) = 0;
	
	/** iterator to first element */
	virtual IteratorPtr Begin() const = 0;

	/** iterator to last element */
	virtual IteratorPtr End() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVCONTAINER_H
