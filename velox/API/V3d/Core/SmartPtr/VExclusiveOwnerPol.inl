template<class StoragePolicy> 
VExclusiveOwnerPol<StoragePolicy>::VExclusiveOwnerPol()
{
}

/*!
	returns the stored value
*/
template<class StoragePolicy> 
typename VExclusiveOwnerPol<StoragePolicy>::PointerType
	VExclusiveOwnerPol<StoragePolicy>
	::Get() const
{
	return this->StoragePolicy::Get();
	//return m_Storage.Get();
}

/*!
	releases old target and saves new one
*/
template<class StoragePolicy> 
void VExclusiveOwnerPol<StoragePolicy>
	::Assign(AssignParam in_NewVal)
{
	this->StoragePolicy::Release();
	this->StoragePolicy::Assign(in_NewVal);
	//m_Storage.Release();
	//m_Storage.Assign(in_NewVal);
}

/*!
	loescht das Ziel
*/
template<class StoragePolicy> 
void VExclusiveOwnerPol<StoragePolicy>
	::Release()
{
	this->StoragePolicy::Release();
	this->StoragePolicy::Assign(0);
	//m_Storage.Release();
	//m_Storage.Assign(0);
}

/*!
	erstellt eine Kopie
*/
template<class StoragePolicy> 
void VExclusiveOwnerPol<StoragePolicy>
	::Clone(VExclusiveOwnerPol<StoragePolicy>& in_Other)
{
	this->Assign(in_Other.StoragePolicy::Get());
	in_Other.StoragePolicy::Assign(0);
	//m_Storage.Assign(in_Other.m_Storage.Get());
	//in_Other.m_Storage.Assign(0);
}


