VSharedPtrBase::VSharedPtrBase() :
	m_pStore(0)
{
}

VSharedPtrBase::SharedStorage::SharedStorage() :
	pSubject(0), 
	nReferenceCount(0)
{
}

VSharedPtrBase::SharedStorage* VSharedPtrBase::GetStore(const VSharedPtrBase& obj)
{
	return obj.m_pStore;
}

//-----------------------------------------------------------------------------

template<typename T>
void VSharedPtr<T>::Release()
{
	// decrease reference count
	m_pStore->nReferenceCount--;

	// if the subject isn't referenced anymore, delete it
	if( m_pStore->nReferenceCount <= 0 )
	{
		T* t = reinterpret_cast<T*>(m_pStore->pSubject);
		delete t;

		delete m_pStore;
	}
	
	m_pStore = new SharedStorage();
}

template<typename T>
void VSharedPtr<T>::Assign(T* in_pSubject)
{
	Release();

	m_pStore = new SharedStorage();
	m_pStore->pSubject = in_pSubject;
	m_pStore->nReferenceCount = 1;
}

template<typename T>
T* VSharedPtr<T>::DropOwnership()
{
	V3D_ASSERT(m_pStore->nReferenceCount <= 1);

	T* ptr = Get();
	m_pStore->pSubject = 0;
	m_pStore->nReferenceCount = 0;
	return ptr;
}

template<typename T>
T* VSharedPtr<T>::Get() const
{
	return reinterpret_cast<T*>(m_pStore->pSubject);
}

template<typename T> template<typename Derived>
void VSharedPtr<T>::Clone(const VSharedPtr<Derived>& in_Other)
{
	// check whether types are 'compatible'
	T* t = (Derived*)0;

	Release();

	m_pStore = GetStore(in_Other);
	m_pStore->nReferenceCount++;
}

template<typename T>
VSharedPtr<T>::VSharedPtr()
{
	m_pStore = new SharedStorage();
}

template<typename T> template<typename Derived>
VSharedPtr<T>::VSharedPtr(const VSharedPtr<Derived>& in_Other)
{
	m_pStore = new SharedStorage();
	Clone(in_Other);
}

template<typename T>
VSharedPtr<T>::VSharedPtr(const VSharedPtr& in_Other)
{
	m_pStore = new SharedStorage();
	Clone(in_Other);
}

template<typename T>
VSharedPtr<T>::VSharedPtr(T* in_pSubject)
{
	m_pStore = new SharedStorage();
	Assign(in_pSubject);
}

template<typename T>
VSharedPtr<T>::~VSharedPtr()
{
	Release();
}

template<typename T> template<typename Derived>
void VSharedPtr<T>::operator=(const VSharedPtr<Derived>& in_Other)
{
	Clone(in_Other);
}

template<typename T>
void VSharedPtr<T>::operator=(const VSharedPtr& in_Other)
{
	Clone(in_Other);
}

template<typename T>
T& VSharedPtr<T>::operator*() const
{
	return *Get();
}

template<typename T>
T* VSharedPtr<T>::operator->() const
{
	return Get();
}

//-----------------------------------------------------------------------------
template<typename T, typename T2>
vbool operator==(const VSharedPtr<T>& left, const VSharedPtr<T2>& right)
{
	return left.Get() == right.Get();
}

template<typename T, typename T2>
vbool operator!=(const VSharedPtr<T>& left, const VSharedPtr<T2>& right)
{
	return left.Get() != right.Get();
}
