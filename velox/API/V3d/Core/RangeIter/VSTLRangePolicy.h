#ifndef V3D_VSTLRANGEPOLICY_H_2005_01_20_H
#define V3D_VSTLRANGEPOLICY_H_2005_01_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/VSTLRangePolicyBase.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting
	
template<typename STLIterator>
	class VSTLRangePolicy : public VSTLRangePolicyBase<STLIterator>
{
public:
	VSTLRangePolicy(const STLIterator& in_Begin, const STLIterator& in_End)
		: VSTLRangePolicyBase<STLIterator>(in_Begin, in_End)
	{}
		
	virtual Type* Get() const
	{
		return &(*m_Current);
	}
		
	virtual IVRangeIteratorPolicy<Type>* Clone() const
	{
		return new VSTLRangePolicy(m_Current, m_End);
	}
};
	
//-----------------------------------------------------------------------------
} // namespace v3d
  //-----------------------------------------------------------------------------
#endif // V3D_VSTLRANGEPOLICY_H_2005_01_20_H
