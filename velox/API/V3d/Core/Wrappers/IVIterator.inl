template<typename TargetType>
typename IVIterator<TargetType>::ValueType&
IVIterator<TargetType>
	::operator->() const
{
	return Get();
}

template<typename TargetType>
typename IVIterator<TargetType>::ValueType* 
	IVIterator<TargetType>
	::operator*() const
{
	return *Get();
}

/**
 * Two iterators are identical if they point to the same target
 //TODO: allow custom behavior for child classes?
 */
template<typename TargetType>
vbool IVIterator<TargetType>::operator==(const IVIterator<ValueType>& in_Other)
{
	return (this->Get() == in_Other.Get());
}

/**
 * Two iterators are different if they are not identical
 */
template<typename TargetType>
vbool IVIterator<TargetType>::operator!=(const IVIterator<ValueType>& in_Other)
{
	return !(this->operator==(in_Other));
}

template<typename TargetType>
vbool IVIterator<TargetType>::operator==(const ValueType* in_pVal)
{
	return (this->Get() == in_pVal);
}

template<typename TargetType>
vbool IVIterator<TargetType>::operator!=(const ValueType* in_pVal)
{
	return !(this->operator==(in_pVal));
}
