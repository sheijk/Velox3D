template<typename IterType, typename TargetType>
VSTLIteratorAdaptor<IterType, TargetType>::VSTLIteratorAdaptor(const IterType& in_Iter)
{
	m_Iter = in_Iter;
}

template<typename IterType, typename TargetType>
VSTLIteratorAdaptor<IterType, TargetType>::~VSTLIteratorAdaptor()
{
}

template<typename IterType, typename TargetType>
vbool VSTLIteratorAdaptor<IterType, TargetType>::Proceed()
{
	m_Iter++;

	return true;
}

template<typename IterType, typename TargetType>
vbool VSTLIteratorAdaptor<IterType, TargetType>::MoveBack()
{
	m_Iter--;

	return true;
}

template<typename IterType, typename TargetType>
vbool VSTLIteratorAdaptor<IterType, TargetType>::HasSubject()
{
	return (*m_Iter != 0);
}

template<typename IterType, typename TargetType>
typename VSTLIteratorAdaptor<IterType, TargetType>::ValueType& 
	VSTLIteratorAdaptor<IterType, TargetType>::Get() const
{
	//TODO: besser machen :)
	return (*m_Iter);
}
