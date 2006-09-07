/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSTLRANGEDEREFPOLICY_H_2005_01_20_H
#define V3D_VSTLRANGEDEREFPOLICY_H_2005_01_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/VSTLRangeDerefPolicy.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

template<typename T, typename STLIterator>
	class VSTLRangeDerefPolicy : public VSTLRangePolicyBase<STLIterator, T>
{
public:
	VSTLRangeDerefPolicy(const STLIterator& in_Begin, const STLIterator& in_End)
		: VSTLRangePolicyBase<STLIterator, T>(in_Begin, in_End)
	{}
		
	virtual T* Get() const
	{
		return &*(*m_Current);
	}
		
	virtual IVRangeIteratorPolicy<Type>* Clone() const
	{
		return new VSTLRangeDerefPolicy(m_Current, m_End);
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLRANGEDEREFPOLICY_H_2005_01_20_H

