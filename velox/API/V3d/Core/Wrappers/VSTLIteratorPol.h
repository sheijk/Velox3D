#ifndef V3D_VSTLITERATORPOL_H
#define V3D_VSTLITERATORPOL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/IVIteratorPol.h>

#include <v3d/Core/Wrappers/VWrapIteratorPolBase.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

template<
	typename IterType,
	typename ValueType = typename IterType::value_type
>
class VSTLIteratorPol : public
	iterpolutil::VCompareFunc<
		iterpolutil::VNormalGet<
			iterpolutil::VWrapIteratorPolBase<IterType, ValueType>
		>,
		IterType
	>
{
	typedef		iterpolutil::VCompareFunc<
					iterpolutil::VNormalGet<
					iterpolutil::VWrapIteratorPolBase<IterType, ValueType>
					>,
					IterType
				>
				Parent;

public:
	typedef ValueType Value;
	typedef ValueType* Pointer;

	VSTLIteratorPol(const IterType& in_Iter) : Parent(in_Iter)
	{
	}

	virtual VSTLIteratorPol* CreateCopy() const
	{
		return new VSTLIteratorPol(this->m_Iter);
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLITERATORPOL_H