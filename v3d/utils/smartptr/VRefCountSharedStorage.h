///////////////////////////////////////////////////////////
//
//  VRefCountSharedStorage.h
//  Implementation of the Class VRefCountSharedStorage
//  Generated by Enterprise Architect
//  Created on:      19-Mar-2003 02:59:53
//  Original author: sheijk
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(VRefCountSharedStorage_96C50186_11F7_453b_9043_394C3C822B5B__INCLUDED_)
#define VRefCountSharedStorage_96C50186_11F7_453b_9043_394C3C822B5B__INCLUDED_

/**
 * Helper Class for VRefCountPol
 * keeps track of the number of references to a pointer, and will automatically
 * delete it and itself if no more references are needed
 */
template<class StoragePolicy>
class VRefCountSharedStorage
{
public:
	typedef VRefCountSharedStorage<StoragePolicy> MyType;

private:
	int m_nRefCount;
	StoragePolicy m_Storage;

	/** object may only be constructed via CreateNew */
	VRefCountSharedStorage();

	/** no copy constructor */
	VRefCountSharedStorage(const MyType&);
	/** no assignment operator */
	void operator=(const MyType&);

	/** deleting prohibited. object deletes itself through Release() */
	~VRefCountSharedStorage();

public:
	/** create a new shared storage which points to in_Subject */
	static MyType* CreateNew(StoragePolicy::TargetType in_Subject)
	{
		VRefCountSharedStorage<StoragePolicy>* pInstance 
			= new VRefCountSharedStorage<StoragePolicy>();

		// assign subject
		pInstance->m_Storage.Set(in_Subject);
		pInstance->m_nRefCount = 1;

		return pInstance;
	}

	/** decrease ref count by one. self delets on zero */
	void Release();

	/** inreases ref count by one */
	void AddRef();

	/** returns the subject */
	StoragePolicy::TargetType Get()
	{
		return m_Storage.Get();
	}
};

#include "VRefCountSharedStorage.inl"

#endif // !defined(VRefCountSharedStorage_96C50186_11F7_453b_9043_394C3C822B5B__INCLUDED_)