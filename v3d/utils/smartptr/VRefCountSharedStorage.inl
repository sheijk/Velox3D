///////////////////////////////////////////////////////////
//
//  VRefCountSharedStorage.cpp
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

#include "VRefCountSharedStorage.h"

template<class StoragePolicy> 
VRefCountSharedStorage<StoragePolicy>::
	VRefCountSharedStorage()
{
}

/**
 * Constructor. Creates a shared storage which points to in_Subject
 *
template<class StoragePolicy> 
//void* VRefCountSharedStorage<StoragePolicy>::
VRefCountSharedStorage<StoragePolicy>* VRefCountSharedStorage<StoragePolicy>::
//	CreateNew(void* in_Subject)
	CreateNew(StoragePolicy::TargetType in_Subject)
{
	VRefCountSharedStorage<StoragePolicy>* pInstance = new VRefCountSharedStorage<StoragePolicy>();

	// assign subject
	pInstance->m_Storage.Set(in_Subject);
	pInstance->m_nRefCount = 1;

	return pInstance;
}*/

/**
 * will delete the subject
 */
template<class StoragePolicy> 
VRefCountSharedStorage<StoragePolicy>::
	~VRefCountSharedStorage()
{
	// delete subject
	m_Storage.Release();
}

/**
 * will decrease the ref count by one. If the ref count reaches zero
 * it will delete the object
 */
template<class StoragePolicy> 
void VRefCountSharedStorage<StoragePolicy>::
	Release()
{
	m_nRefCount--;

	if( m_nRefCount <= 0 )
	{
		m_Storage.Release();
		delete this;
	}
}

/**
 * increases the ref count by one
 */
template<class StoragePolicy> 
void VRefCountSharedStorage<StoragePolicy>::
	AddRef()
{
	m_nRefCount++;
}

/**
 * returns the subject
 *
template<class StoragePolicy> 
StoragePolicy::TargetType VRefCountSharedStorage<StoragePolicy>::
	Get()
{
	return m_Storage.Get();
}


/**/