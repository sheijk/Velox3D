template<typename T> VArrayStorage<T>::VArrayStorage()
{
	m_pTarget = 0;
}

template<typename T> VArrayStorage<T>::~VArrayStorage()
{
	m_pTarget = 0;
}

template<typename T> void VArrayStorage<T>::Set(T* in_pNewTarget)
{
	m_pTarget = in_pNewTarget;
}

template<typename T> T* VArrayStorage<T>::Get() const
{
	return m_pTarget;
}

template<typename T> void VArrayStorage<T>::Release()
{
	delete[] m_pTarget;
	m_pTarget = 0;
}


