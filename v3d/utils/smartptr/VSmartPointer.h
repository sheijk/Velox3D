///////////////////////////////////////////////////////////
//
//  VSmartPointer.h
//  Implementation of the Class VSmartPointer
//  Generated by Enterprise Architect
//  Created on:      28-Feb-2003 23:14:09
//  Original author: sheijk
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////
#if !defined(VSmartPointer_694F609A_3759_4346_A113_6232A9BE803B__INCLUDED_)
#define VSmartPointer_694F609A_3759_4346_A113_6232A9BE803B__INCLUDED_

#include "VSmartHandleBase.h"

template
	<
	typename T,
	class OwnerPolicy, // = VExclusiveOwnerPol<VPointerStorage<T>>,
	class ReadCheckPolicy, // = VNoCheckPol<T>,
	class WriteCheckPolicy // =ReadCheckPolicy
	>
class VSmartPointer
{
public:
	typedef VSmartHandleBase<T*, OwnerPolicy, ReadCheckPolicy, WriteCheckPolicy>
		Handle;

	Handle m_Handle;

	VSmartPointer();
public:
	/** for convience */
	typedef VSmartPointer<T, OwnerPolicy, ReadCheckPolicy, WriteCheckPolicy> PtrType;
	typedef T TargetType;

	VSmartPointer(T* in_pTarget);
	VSmartPointer(PtrType& in_Other);
	~VSmartPointer();

	void operator=(T* in_pTarget);
	void operator=(PtrType& in_Other);
	void Release();
	void Reset(T* in_pNewTarget);
	T* Get();
	T* operator->();
	T& operator*();
};

#include "VSmartPointer.inl"

#endif // !defined(VSmartPointer_694F609A_3759_4346_A113_6232A9BE803B__INCLUDED_)
