#ifndef V3D_VSMARTPOINTER_H
#define V3D_VSMARTPOINTER_H
//-----------------------------------------------------------------------------
#include "VSmartHandleBase.h"

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

template
	<
	typename T,
	class OwnerPolicy, // = VExclusiveOwnerPol<VPointerStorage<T>>,
	class ReadCheckPolicy, // = VNoCheckPol<T>,
	class WriteCheckPolicy // =ReadCheckPolicy
	>
class VSmartPointer
{
private:
	typedef VSmartHandleBase<T*, OwnerPolicy, ReadCheckPolicy, WriteCheckPolicy>
		Handle;

	Handle m_Handle;

public:
	/** for convience */
	typedef VSmartPointer<T, OwnerPolicy, ReadCheckPolicy, WriteCheckPolicy> PtrType;
	typedef T TargetType;

	VSmartPointer();
	VSmartPointer(T* in_pTarget);
	VSmartPointer(const PtrType& in_Other);
	~VSmartPointer();

	//TODO: == operatoren
	void operator=(T* in_pTarget);
	void operator=(const PtrType& in_Other);
	void Release();
	void Reset(T* in_pNewTarget);
	T* Get() const;
	T* operator->() const;
	T& operator*() const;
};

//-----------------------------------------------------------------------------
#include "VSmartPointer.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
#endif // V3D_VSMARTPOINTER_H
