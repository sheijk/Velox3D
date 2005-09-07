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
        // TODO: think this over
        // was: return &(*m_Current);
		return &*(*(VSTLRangePolicyBase<STLIterator, T>::m_Current));
	}
		
	virtual IVRangeIteratorPolicy<typename VSTLRangePolicyBase<STLIterator, T>::Type>* Clone() const
	{
        // TODO: think this over
        // was: return new VSTLRangeDerefPolicy(m_Current, m_End);
		return new VSTLRangeDerefPolicy(VSTLRangePolicyBase<STLIterator, T>::m_Current, 
                                        VSTLRangePolicyBase<STLIterator, T>::m_End);
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLRANGEDEREFPOLICY_H_2005_01_20_H
