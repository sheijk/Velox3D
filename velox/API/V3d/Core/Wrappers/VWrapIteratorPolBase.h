#ifndef V3D_VWRAPITERATORPOLBASE_H
#define V3D_VWRAPITERATORPOLBASE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VGenericUtils.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace iterpolutil {
//-----------------------------------------------------------------------------

template<
	typename IterType,
	typename ValueType
>
class VWrapIteratorPolBase : public IVIteratorPol<ValueType>
{
protected:
	IterType m_Iter;

	typedef IterType IteratorType;
public:
	typedef ValueType Value;
	typedef ValueType	* Pointer;

	VWrapIteratorPolBase(const IterType& in_Iter) : m_Iter(in_Iter) 
	{
	}

	virtual void MoveBy(vint in_nDistance)
	{
		advance(m_Iter, in_nDistance);
	}

	virtual vbool IsEqual(const IVIteratorPol<ValueType>& in_Other) const	
	{
		const VWrapIteratorPolBase& other = 
			static_cast<const VWrapIteratorPolBase&>(in_Other);

		return m_Iter == other.m_Iter;
	}
};

template<typename Parent>
struct VNormalGet : public Parent
{
	VNormalGet(const typename Parent::IteratorType& it) : Parent(it) {}

	virtual typename Parent::Pointer Get() const
	{
		return &(*m_Iter);
	}
};

template<typename Parent>
struct VDerefGet : public Parent
{
	VDerefGet(const typename Parent::IteratorType& it) : Parent(it) {}

	virtual typename Parent::Pointer Get() const
	{
		return &(*(*m_Iter));
	}
};

template<typename Parent, typename IterType>
struct VCompareFunc : public Parent
{
	VCompareFunc(const typename Parent::IteratorType& it) : Parent(it) {}

	virtual vint Compare(const IVIteratorPol<typename Parent::Value>& in_Other) const
	{
		V3D_THROW(VUnsupportedIterOperation,
			"Tried to sort non ordered iterator type"
			);
	}
};

template<typename Parent>
struct VCompareFunc<Parent, std::random_access_iterator_tag> : public Parent
{
	VCompareFunc(const typename Parent::IteratorType& it) : Parent(it) {}

	virtual vint Compare(const IVIteratorPol<typename Parent::Value>& in_Other) const
	{
		const VCompareFunc& other = static_cast<const VCompareFunc&>(in_Other);

		return VCompare(m_Iter, other.m_Iter);
	}
};

//-----------------------------------------------------------------------------
} // namespace iterpolutil
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWRAPITERATORPOLBASE_H
