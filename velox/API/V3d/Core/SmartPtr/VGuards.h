#ifndef V3D_GUARDS_H
#define V3D_GUARDS_H
//-----------------------------------------------------------------------------
#include "VSmartPtr.h"
#include "VExclusiveOwnerPol.h"
#include "VRefCountPol.h"
#include "VPointerStorage.h"
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * Workaround for lack of templated typedefs (ala typedef ... VPointer<T>).
 * Use VPointer<TypeName>::PointerType
 *
 * @author sheijk
 */
template<typename T>
struct VPointer 
{
	/**
	 * a smart pointer which behaves like std::auto_ptr
	 * ownership changes on copy, old owner is set to 0. 
	 * subject will be deleted when the pointer releases 
	 * it
	 */
	typedef VSmartPtrMutable<
		T, 
		VExclusiveOwnerPol< VPointerStorage<T> >
		> AutoPtr;

	/**
	 * shared pointer. multiple pointer can share a subject.
	 * subject will be deleted when last pointer refering to
	 * it releases the subject or is set to a new subject
	 */
	typedef VSmartPtr<
		T,
		VRefCountPol< VPointerStorage<T> >
		> SharedPtr;

private:
	// prevent user from accidently writing VPointer<Blah> 
	// instead of VPointer<Blah>::AutoPtr etc.
	VPointer(int);
};

/**
 * Convience function to create a shared pointer.
 *
 * @author sheijk
 */
template<typename Subject>
typename VPointer<Subject>::SharedPtr SharedPtr(Subject* in_pValue)
{
	return VPointer<Subject>::SharedPtr(in_pValue);
}

/**
 * Convience function to create an auto pointer.
 *
 * @author sheijk
 */
template<typename Subject>
typename VPointer<Subject>::AutoPtr AutoPtr(Subject* in_pValue)
{
	return VPointer<Subject>::AutoPtr(in_pValue);
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_GUARDS_H
