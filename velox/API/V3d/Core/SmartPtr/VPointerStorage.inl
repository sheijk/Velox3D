template<typename T> VPointerStorage<T>::VPointerStorage(){
	m_pTarget = 0;
}


template<typename T> VPointerStorage<T>::~VPointerStorage(){
	m_pTarget = 0;
}


template<typename T> void VPointerStorage<T>::Set(T* in_pNewTarget){
	m_pTarget = in_pNewTarget;
}


template<typename T> T* VPointerStorage<T>::Get(){
	return m_pTarget;
}


template<typename T> void VPointerStorage<T>::Release(){
	delete m_pTarget;
	m_pTarget = 0;
}


