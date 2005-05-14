#ifndef V3D_GUARDS_H
#define V3D_GUARDS_H
//-----------------------------------------------------------------------------
#include "VSharedPtr.h"
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
	 * shared pointer. multiple pointer can share a subject.
	 * subject will be deleted when last pointer refering to
	 * it releases the subject or is set to a new subject
	 */
	typedef VSharedPtr<T> SharedPtr;

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

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_GUARDS_H
