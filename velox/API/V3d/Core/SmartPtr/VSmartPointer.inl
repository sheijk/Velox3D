/**
 * Standard constructor, initializes with 0
 */
template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy>
VSmartPointer<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>::
	VSmartPointer()
{
	m_Handle.SetTarget(0);
}

/**
 * Initialisiert das Zeiger mit einem gegebenem Pointer
 */
template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy>
VSmartPointer<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>::
	VSmartPointer(T* in_pTarget)
{
	m_Handle.SetTarget(in_pTarget);
}

/**
 * (nicht virtueller) Destruktor
 */
template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy>
VSmartPointer<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>::
	~VSmartPointer()
{
	m_Handle.ReleaseTarget();
}

template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy>
VSmartPointer<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>
	::VSmartPointer(const PtrType& in_Other)
{
	*this = in_Other;
}

template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy>
void VSmartPointer<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>::
	operator=(T* in_pTarget)
{
	Reset(in_pTarget);
}

template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy> 
void VSmartPointer<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>
	::operator=(const PtrType& in_Other)
{
	m_Handle.Clone(in_Other.m_Handle);
}

/**
 * Das Subject wird freigegeben
 */
template<typename T, class OwnerPolicy, class ReadCheckPolicy, class WriteCheckPolicy> 
void VSmartPointer<T, OwnerPolicy, ReadCheckPolicy, WriteCheckPolicy>::
	Release()
{
	m_Handle.ReleaseTarget();
}

/**
 * Das Subject wird freigegeben, danach bekommt der SmartPointer ein neues
 * Subject
 */
template<typename T, class OwnerPolicy, class ReadCheckPolicy, class WriteCheckPolicy> 
void VSmartPointer<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>::
	Reset(T* in_pNewTarget)
{
	m_Handle.SetTarget(in_pNewTarget);
}

/**
 * Liefert einen Zeiger auf das Target zurueck
 */
template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy>
T* VSmartPointer<T,OwnerPolicy,ReadCheckPolicy,WriteCheckPolicy>::
	Get()
{
	return m_Handle.GetTarget();
}

template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy>
T* VSmartPointer<T, OwnerPolicy, ReadCheckPolicy, WriteCheckPolicy>::
	operator->()
{
	return Get();
}

template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy>
T& VSmartPointer<T, OwnerPolicy, ReadCheckPolicy, WriteCheckPolicy>::
	operator*()
{
	return *Get();
}