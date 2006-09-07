/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSINGLEVALUERANGEPOLICY_2005_09_23_H
#define V3D_VSINGLEVALUERANGEPOLICY_2005_09_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/IVRangeIteratorPolicy.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Creates an iterator which will return the value of an existing variable one
 * or more times
 *
 * @author sheijk
 */
template<typename T>
VRangeIterator<T> CreateSingleValueIterator(T* in_pValue, vuint in_nCount = 1);

/**
 * A range iterator policy to create an iterator which will return a single
 * value multiple times. Use this if you want to return an iterator which
 * iterates over a member variable, etc.
 *
 * @author sheijk
 */
template<typename T>
class VSingleValueRangePolicy : public IVRangeIteratorPolicy<T>
{
	T* m_pValue;
	vuint m_nRemaining;

public:
	VSingleValueRangePolicy(T* ptr, vuint count) : 
	  m_pValue(ptr), 
		  m_nRemaining(count) 
	  {}

	  virtual void Proceed() { --m_nRemaining; }

	  virtual T* Get() const
	  {
		  if( HasNext() ) 
			  return m_pValue;
		  else
			  V3D_THROW(VException, "accessed past-the-end iterator");
	  }

	  virtual vbool HasNext() const { return m_nRemaining > 0; }

	  virtual IVRangeIteratorPolicy<T>* Clone() const
	  {
		  return new VSingleValueRangePolicy(m_pValue, m_nRemaining);
	  }

	  virtual vbool IsEqual(const IVRangeIteratorPolicy<T>& other) const
	  {
		  const VSingleValueRangePolicy<T>* pOther = 
			  reinterpret_cast<const VSingleValueRangePolicy<T>*>(&other);

		  return pOther->m_pValue == m_pValue &&
			  pOther->m_nRemaining == m_nRemaining;
	  }
};

template<typename T>
VRangeIterator<T> CreateSingleValueIterator(T* in_pValue, vuint in_nCount)
{
	return VRangeIterator<T>(VSingleValueRangePolicy<T>(in_pValue, in_nCount));
}


//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSINGLEVALUERANGEPOLICY_2005_09_23_H

