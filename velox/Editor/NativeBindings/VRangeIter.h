#ifndef V3D_VRANGEITERATOR_2005_01_17_H
#define V3D_VRANGEITERATOR_2005_01_17_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/IVRangeIteratorPolicy.h>
#include <V3d/Core/RangeIter/VSTLRangePolicy.h>
#include <V3d/Core/RangeIter/VSTLRangeDerefPolicy.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
//using namespace v3d; // prevent auto indenting


/**
	* Provides a simple java style iterator class based on a [begin, end) stl
* iterator pair. STLIterator must be a model of ForwardIterator. Note that
* not all signatures must be provided. More precicely the following functions
* must be present: <br>
* <br>
* ? operator++()						<br>
* ? operator++(int)					<br>
* vbool operator==(const STLIterator&)	<br>
* <br>
* ? means any return type is appropriate
*
* @author sheijk
*/
template<typename T>
	class VRangeIterator
{
	IVRangeIteratorPolicy<T>* m_pIteratorImpl;
	
	/**
	* May not be called. Thus no implementation provided to get linker errror when used
	 * accidently
	 */
	VRangeIterator(); 
	
public:
	explicit VRangeIterator(const IVRangeIteratorPolicy<T>& in_IterImpl)
	{
			m_pIteratorImpl = in_IterImpl.Clone();
			
			V3D_ASSERT(m_pIteratorImpl != 0);
	}
	
	~VRangeIterator()
	{
		delete m_pIteratorImpl;
		m_pIteratorImpl = 0;
	}
	
	VRangeIterator(const VRangeIterator& in_Source)
	{
		m_pIteratorImpl = in_Source.m_pIteratorImpl->Clone();
		
		V3D_ASSERT(m_pIteratorImpl != 0);
	}
	
	void operator=(const VRangeIterator& in_Source)
	{
		delete m_pIteratorImpl;
		m_pIteratorImpl = in_Source.m_pIteratorImpl->Clone();
		
		V3D_ASSERT(m_pIteratorImpl != 0);
	}
	
	void operator++()
	{
		m_pIteratorImpl->Proceed();
	}
	
	void operator++(int)
	{
		m_pIteratorImpl->Proceed();
	}
	
	vbool HasNext()
	{
		return m_pIteratorImpl->HasNext();
	}
	
	T& operator*() const
	{
		return *m_pIteratorImpl->Get();
	}
	
	T* operator->() const
	{
		return m_pIteratorImpl->Get();
	}
	
	vbool operator==(const VRangeIterator<T>& in_Other)
	{
		return m_pIteratorImpl->IsEqual(*in_Other.m_pIteratorImpl);
	}
	
	vbool operator!=(const VRangeIterator<T>& in_Other)
	{
		return ! (*this == in_Other);
	}
};

template<typename STLIterator>
VRangeIterator<typename std::iterator_traits<STLIterator>::value_type> 
CreateIterator(STLIterator begin, STLIterator end)
{
	typedef typename std::iterator_traits<STLIterator>::value_type T;
	// create iterator policy for stl iterator range
	VSTLRangePolicy<STLIterator> policy(begin, end);
	
	// create range iterator and return it
	return VRangeIterator<T>(policy);
};

template<typename STLContainer>
VRangeIterator<typename STLContainer::value_type>
CreateBeginIterator(STLContainer& in_Container)
{
	return CreateIterator(in_Container.begin(), in_Container.end());
}

template<typename STLContainer>
VRangeIterator<typename STLContainer::value_type>
CreateEndIterator(STLContainer& in_Container)
{
	return CreateIterator(in_Container.end(), in_Container.end());
}

template<typename T, typename STLIterator>
VRangeIterator<T> CreateDerefIterator(const STLIterator& in_Begin, const STLIterator& in_End)
{
	VSTLRangeDerefPolicy<T, STLIterator> pol(in_Begin, in_End);
	
	return VRangeIterator<T>(pol);
}

template<typename T, typename STLContainer>
VRangeIterator<T> CreateDerefBeginIterator(const STLContainer& in_Container)
{
	return CreateDerefIterator<T>(in_Container.begin(), in_Container.end());
}

template<typename T, typename STLContainer>
VRangeIterator<T> CreateDerefEndIterator(const STLContainer& in_Container)
{
	return CreateDerefIterator<T>(in_Container.end(), in_Container.end());
}

	
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VRANGEITERATOR_2005_01_17_H
