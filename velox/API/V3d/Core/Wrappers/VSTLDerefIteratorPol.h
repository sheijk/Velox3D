#ifndef V3D_VSTLDEREFITERATORPOL_H
#define V3D_VSTLDEREFITERATORPOL_H
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
class VSTLDerefIteratorPol : public
	iterpolutil::VCompareFunc<
		iterpolutil::VDerefGet<
			iterpolutil::VWrapIteratorPolBase<IterType, ValueType>
		>,
		IterType
	>
{
	typedef		iterpolutil::VCompareFunc<
					iterpolutil::VDerefGet<
						iterpolutil::VWrapIteratorPolBase<IterType, ValueType>
					>,
					IterType
				>
				Parent;

public:
	typedef ValueType Value;
	typedef ValueType* Pointer;

	VSTLDerefIteratorPol(const IterType& in_Iter) : Parent(in_Iter)
	{
	}

	virtual VSTLDerefIteratorPol* CreateCopy() const
	{
		return new VSTLDerefIteratorPol(this->m_Iter);
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLDEREFITERATORPOL_H
