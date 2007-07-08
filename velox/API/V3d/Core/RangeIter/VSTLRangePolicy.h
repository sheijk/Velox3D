/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSTLRANGEPOLICY_H_2005_01_20_H
#define V3D_VSTLRANGEPOLICY_H_2005_01_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/VSTLRangePolicyBase.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting
	
template<
	typename STLIterator, 
	typename T = typename std::iterator_traits<STLIterator>::value_type
>
class VSTLRangePolicy : public VSTLRangePolicyBase<STLIterator, T>
{
public:
        typedef T Type;
	VSTLRangePolicy(const STLIterator& in_Begin, const STLIterator& in_End)
		: VSTLRangePolicyBase<STLIterator, T>(in_Begin, in_End)
	{}
	virtual ~VSTLRangePolicy(){};
        // access through this to signal protected variables as dependant type
	virtual Type* Get() const
	{
		return &(*this->m_Current);
	}
		
	virtual IVRangeIteratorPolicy<Type>* Clone() const
	{
		return new VSTLRangePolicy(this->m_Current, this->m_End);
	}
};
	
//-----------------------------------------------------------------------------
} // namespace v3d
  //-----------------------------------------------------------------------------
#endif // V3D_VSTLRANGEPOLICY_H_2005_01_20_H

