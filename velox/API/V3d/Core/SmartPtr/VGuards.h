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
	typedef VSmartPtr<
		T, 
		VExclusiveOwnerPol< VPointerStorage<T> >
		//VNoCheckPol<T*>, 
		//VNoCheckPol<T*>
		> AutoPtr;

	/**
	 * shared pointer. multiple pointer can share a subject.
	 * subject will be deleted when last pointer refering to
	 * it releases the subject or is set to a new subject
	 */
	typedef VSmartPtrMutable<
		T,
		VRefCountPol< VPointerStorage<T> >
		//VRefCountPol< VPointerStorage<T> >,
		//VNoCheckPol<T*>,
		//VNoCheckPol<T*>
		> SharedPtr;
};

/**
 * the same for arrays
 */
//template<typename T>
//struct VArrayPtr
//{
//	typedef VSmartPointer<
//		T,
//		VExclusiveOwnerPol< VArrayStorage<T> >,
//		VNoCheckPol<T*>,
//		VNoCheckPol<T*>
//		> AutoPtr;
//
//	typedef VSmartPointer<
//		T,
//		VRefCountPol< VArrayStorage<T> >,
//		VNoCheckPol<T*>,
//		VNoCheckPol<T*>
//		> SharedPtr;
//};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_GUARDS_H
