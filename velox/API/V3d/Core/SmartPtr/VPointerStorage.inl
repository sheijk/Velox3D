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

template<typename T> bool VPointerStorage<T>
	::IsEqual(const VPointerStorage& in_Other) const
{
	return m_pTarget == in_Other.m_pTarget;
}
