template<typename TargetType, typename IterType>
VSTLIterDerefAdaptor<TargetType, IterType>
	::VSTLIterDerefAdaptor(const IterType& in_Iter)
{
	m_Iter = in_Iter;
}

template<typename TargetType, typename IterType>
VSTLIterDerefAdaptor<TargetType, IterType>
	::~VSTLIterDerefAdaptor()
{
}

template<typename TargetType, typename IterType>
vbool VSTLIterDerefAdaptor<TargetType, IterType>
	::Proceed()
{
	m_Iter++;

	return true;
}

template<typename TargetType, typename IterType>
vbool VSTLIterDerefAdaptor<TargetType, IterType>
	::MoveBack()
{
	m_Iter--;

	return true;
}

template<typename TargetType, typename IterType>
vbool VSTLIterDerefAdaptor<TargetType, IterType>
	::HasSubject()
{
	// return dereferenced value
	return (*m_Iter != 0);
}

template<typename TargetType, typename IterType>
typename VSTLIterDerefAdaptor<TargetType, IterType>::ValueType& 
VSTLIterDerefAdaptor<TargetType, IterType>
	::Get() const
{
	//TODO: besser machen :)
	return *(*m_Iter);
}
