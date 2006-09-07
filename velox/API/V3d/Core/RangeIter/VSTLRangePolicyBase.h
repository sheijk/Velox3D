/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSTLRANGEPOLICYBASE_H_2005_01_20_H
#define V3D_VSTLRANGEPOLICYBASE_H_2005_01_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/IVRangeIteratorPolicy.h>

#include <typeinfo>
#include <iterator>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

template<
	typename STLIterator, 
	typename T = typename std::iterator_traits<STLIterator>::value_type
>
class VSTLRangePolicyBase : public IVRangeIteratorPolicy<T>
{
protected:
	STLIterator m_Current;
	STLIterator m_End;
	
	VSTLRangePolicyBase(STLIterator begin, STLIterator end)
		: m_Current(begin), m_End(end)
	{}
	
	typedef T Type;
public:
		
	virtual void Proceed()
	{
		++m_Current;
	}
	
	virtual vbool HasNext() const
	{
		return !(m_Current == m_End);
	}
	
	virtual vbool IsEqual(const IVRangeIteratorPolicy<T>& in_Other) const
	{
		if( typeid(*this) == typeid(in_Other) )
		{
			const VSTLRangePolicyBase<STLIterator, T>& other(
				reinterpret_cast< const VSTLRangePolicyBase<STLIterator, T>& >(
					in_Other));
			
			return m_Current == other.m_Current;
		}
		else
		{
			return false;
		}
	}
};
	
//-----------------------------------------------------------------------------
} // namespace v3d
  //-----------------------------------------------------------------------------
#endif // V3D_VSTLRANGEPOLICYBASE_H_2005_01_20_H

