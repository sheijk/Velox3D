#ifndef V3D_VEMPTYPOLICY_2005_10_26_H
#define V3D_VEMPTYPOLICY_2005_10_26_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/IVRangeIteratorPolicy.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace  {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * An iterator policy which will "simulates" an empty container
 *
 * @author sheijk
 */
template<typename T>
class VEmptyPolicy : public IVRangeIteratorPolicy<T>
{
public:
	virtual void Proceed() {}
	virtual T* Get() const { V3D_THROW(VException, "out of range"); }
	virtual vbool HasNext() const { return false; }
	virtual IVRangeIteratorPolicy<T>* Clone() const 
	{ 
		return new VEmptyPolicy<T>(*this);
	}

	virtual vbool IsEqual(const IVRangeIteratorPolicy<T>&) const
	{
		return true;
	}
};

template<typename T>
VRangeIterator<T> CreateEmptyIterator()
{
	return VRangeIterator<T>(VEmptyPolicy<T>());
}

//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------
#endif // V3D_VEMPTYPOLICY_2005_10_26_H
