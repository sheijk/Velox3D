template<typename T> VPointerStorage<T>::VPointerStorage()
{
	m_pTarget = 0;
}

template<typename T> VPointerStorage<T>::~VPointerStorage()
{
	m_pTarget = 0;
}

template<typename T> void VPointerStorage<T>::Assign(AssignParam in_pNewTarget)
{
	m_pTarget = in_pNewTarget;
}

template<typename T> T* VPointerStorage<T>::Get() const
{
	return m_pTarget;
}

template<typename T> void VPointerStorage<T>::Release()
{
	delete m_pTarget;
	m_pTarget = 0;
}

template<typename T> void VPointerStorage<T>::Clone(const VPointerStorage<T>& in_Other)
{
	m_pTarget = new T(*(in_Other.m_pTarget));
}

