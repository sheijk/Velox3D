template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy> 
VSmartHandleBase<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>
	::VSmartHandleBase()
{

}


template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy> 
VSmartHandleBase<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>::
	~VSmartHandleBase()
{
}

template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy> 
T VSmartHandleBase<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>
	::GetTarget() const
{
	// get value
	T t = m_Owner.Get();

	// check value
	m_ReadGuard.Check(t);

	return t;
}

template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy> 
void VSmartHandleBase<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>
	::SetTarget(T in_NewTarget)
{
	// check value
	m_WriteGuard.Check(in_NewTarget);

	// store it
	m_Owner.Set(in_NewTarget);
}

template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy> 
void VSmartHandleBase<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>
	::Clone(const SmartHandleBaseType& in_Other)
{
	// clone owner strategy object
	m_Owner.Clone(in_Other.m_Owner);
}

template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy> 
void VSmartHandleBase<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>
	::ReleaseTarget()
{
	// let the owner release the target
	m_Owner.Release();
}


