/** 
 * Standard Constructor
 */
template<class StoragePolicy> 
VRefCountPol<StoragePolicy>
	::VRefCountPol()
{
	// create a new empty shared storage
	CreateSharedStorage(0);
}

///**
// * Destructor
// */
//template<class StoragePolicy> 
//VRefCountPol<StoragePolicy>
//	::~VRefCountPol()
//{
//	// release shared storage
////	Release();
//}

/**
 * returns the subject
 */
template<class StoragePolicy> 
typename VRefCountPol<StoragePolicy>::PointerType VRefCountPol<StoragePolicy>
	::GetTarget() const
{
	return m_pSharedStorage->Get();
}

/**
 * Sets a new subject. Will release old shared storage and create
 * a new one with the new subject
 */
template<class StoragePolicy> 
void VRefCountPol<StoragePolicy>
	::AssignTarget(typename VRefCountPol<StoragePolicy>::AssignParam in_NewVal)
{
	// release old
	Release();

	// create new storage
	CreateSharedStorage(in_NewVal);
}

/**
 * Releases the subject. Decreases reference count of shared storage
 * by one
 */
template<class StoragePolicy> 
void VRefCountPol<StoragePolicy>
	::ReleaseTarget()
{
	m_pSharedStorage->Release();

	CreateSharedStorage(0);
}

/**
 * Sets subject to the one of the other owner policy. Increases the 
 * reference count of the other storage policy by one
 */
template<class StoragePolicy> 
void VRefCountPol<StoragePolicy>
	::Clone(const VRefCountPol<StoragePolicy>& in_Other)
{
	// release old shared storage
	m_pSharedStorage->Release();

	// use given shared storage
	m_pSharedStorage = in_Other.m_pSharedStorage;

	// increase ref count of storage
	m_pSharedStorage->AddRef();
}

template<class StoragePolicy> 
void VRefCountPol<StoragePolicy>
	::CreateSharedStorage(PointerType in_Subject)
{
	m_pSharedStorage = SharedStorage::CreateNew(in_Subject);
}
