/*!
	default ctor
*/
template<class StoragePolicy> 
VExclusiveOwnerPol<StoragePolicy>::VExclusiveOwnerPol()
{
}


/*!
	dtor, loescht das Target
*/
template<class StoragePolicy> 
VExclusiveOwnerPol<StoragePolicy>::~VExclusiveOwnerPol()
{
	m_Storage.Release();
}


/*!
	Zugriffsmethode
*/
template<class StoragePolicy> 
typename VExclusiveOwnerPol<StoragePolicy>::TargetType VExclusiveOwnerPol<StoragePolicy>::Get()
{
	return m_Storage.Get();
}

/*!
	Set Methode, loescht das alte Target und speichert das neue
*/
template<class StoragePolicy> 
void VExclusiveOwnerPol<StoragePolicy>::Set(TargetType in_NewVal)
{
	m_Storage.Release();
	m_Storage.Set(in_NewVal);
}

/*!
	loescht das Ziel
*/
template<class StoragePolicy> 
void VExclusiveOwnerPol<StoragePolicy>::Release()
{
	m_Storage.Release();
	m_Storage.Set(0);
}

/*!
	erstellt eine Kopie
*/
template<class StoragePolicy> 
void VExclusiveOwnerPol<StoragePolicy>::Clone(VExclusiveOwnerPol<StoragePolicy>& in_Other)
{
	m_Storage.Set(in_Other.m_Storage.Get());
	in_Other.m_Storage.Set(0);
}


