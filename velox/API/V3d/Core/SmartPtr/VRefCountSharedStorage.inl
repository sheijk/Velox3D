template<class StoragePolicy> 
VRefCountSharedStorage<StoragePolicy>::
	VRefCountSharedStorage()
{
}

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
