template<typename T>
void VSharedPtr<T>::Release()
{
	m_BoostPtr.reset();
}

template<typename T>
void VSharedPtr<T>::Assign(T* in_pSubject)
{
	m_BoostPtr.reset(in_pSubject);
}

//template<typename T>
//T* VSharedPtr<T>::DropOwnership()
//{
//	V3D_ASSERT(false);
//	//V3D_ASSERT(m_pStore->nReferenceCount <= 1);
//
//	//T* ptr = Get();
//	//m_pStore->pSubject = 0;
//	//m_pStore->nReferenceCount = 0;
//	//return ptr;
//}

template<typename T>
T* VSharedPtr<T>::Get() const
{
	return m_BoostPtr.get();
}

template<typename T> template<typename Derived>
void VSharedPtr<T>::Clone(const VSharedPtr<Derived>& in_Other)
{
	m_BoostPtr = VSharedPtrFriend::GetInternalPtr(in_Other);
}

template<typename T>
VSharedPtr<T>::VSharedPtr()
{
}

template<typename T> template<typename Derived>
VSharedPtr<T>::VSharedPtr(const VSharedPtr<Derived>& in_Other)
{
	m_BoostPtr = VSharedPtrFriend::GetInternalPtr(in_Other);
}

template<typename T>
VSharedPtr<T>::VSharedPtr(const VSharedPtr& in_Other)
{
	m_BoostPtr = VSharedPtrFriend::GetInternalPtr(in_Other);
}

template<typename T>
VSharedPtr<T>::VSharedPtr(T* in_pSubject)
{
	m_BoostPtr.reset(in_pSubject);
}

template<typename T>
VSharedPtr<T>::~VSharedPtr()
{
	m_BoostPtr.reset();
}

template<typename T> template<typename Derived>
void VSharedPtr<T>::operator=(const VSharedPtr<Derived>& in_Other)
{
	m_BoostPtr = VSharedPtrFriend::GetInternalPtr(in_Other);
}

template<typename T>
void VSharedPtr<T>::operator=(const VSharedPtr& in_Other)
{
	m_BoostPtr = in_Other.m_BoostPtr;
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

template<typename T>
vbool operator==(const VSharedPtr<T>& left, void* right)
{
	return left.Get() == right;
}

template<typename T>
vbool operator!=(const VSharedPtr<T>& left, void* right)
{
	return left.Get() != right;
}
