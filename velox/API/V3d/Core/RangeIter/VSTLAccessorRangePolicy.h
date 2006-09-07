/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSTLACCESSORRANGEPOLICY_2005_05_21_H
#define V3D_VSTLACCESSORRANGEPOLICY_2005_05_21_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/VSTLRangePolicyBase.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * Range Iterator policy for accessing objects in a collection through an
 * accessor object. Use this if you need to "convert", for example if you have
 * a map<int, Foo> and need an iterator for Foo
 * @see CreateAccessorIterator
 *
 * @author sheijk
 */
template<
	typename STLIterator, 
	typename Accessor,
	typename T = Accessor::Type
>
class VSTLAccessorRangePolicy : public VSTLRangePolicyBase<STLIterator, T>
{
public:
	VSTLAccessorRangePolicy(const STLIterator& in_Begin, const STLIterator& in_End)
		: VSTLRangePolicyBase<STLIterator, T>(in_Begin, in_End)
	{}

	virtual Type* Get() const
	{
		return Accessor::Convert(m_Current);
	}

	virtual IVRangeIteratorPolicy<Type>* Clone() const
	{
		return new VSTLAccessorRangePolicy(m_Current, m_End);
	}
};

/**
 * container<T> -> VRangeIterator<T>
 *
 * @author sheijk
 */
template<typename STLIterator, typename T>
struct VDefaultAccessor
{
	typedef T Type;

	static Type* Convert(const STLIterator& iter)
	{
		return &*iter;
	}
};

/**
 * container<T*> -> VRangeIterator<T>
 *
 * @author sheijk
 */
template<typename STLIterator, typename T>
struct VDerefAccessor
{
	typedef T Type;

	static Type* Convert(const STLIterator& iter)
	{
		return &**iter;
	}
};

/**
 * map<T1, T2> -> VRangeIterator<T2>
 *
 * @author sheijk
 */
template<typename STLIterator, typename T>
struct VPair2ndAccessor
{
	typedef T Type;

	static Type* Convert(const STLIterator& iter)
	{
		return &(iter->second);
	}
};

/**
 * map<T1,T2> -> VRangeIterator<const T1>
 * Remember: the key value of an associative container cannot be altered
 *
 * @author sheijk
 */
template<typename STLIterator, typename T>
struct VPair1stAccessor
{
	typedef T Type;

	static Type* Convert(const STLIterator& iter)
	{
		return &(iter->first);
	}
};

/**
 * map<T1, T2*> -> VRangeIterator<T2>
 *
 * @author sheijk
 */
template<typename STLIterator, typename T>
struct VPair2ndDerefAccessor
{
	typedef T Type;

	static Type* Convert(const STLIterator& iter)
	{
		return &*(iter->second);
	}
};

/**
 * Creates a VRangeIterator<T> from an stl iterator and an accessor
 *
 * Example:
 *	std::map<int, VFoo> m;
 *	VRangeIterator<VFoo> itf = CreateAccessorIterator<VPair2ndAccessor, VFoo>(
 *			m.begin(), m.end());
 *
 *	VRangeIterator<const int> iti = 
 *		CreateAccessorIterator<VPair1stAccessor, const int>(m.begin(), m.end());
 *
 *	std::list<vbool*> l;
 *	VRangeIterator<vbool> itb = CreateAccessorIterator<VDerefAccessor, vbool>(
 *		l.begin(), l.end());
 *
 * @author sheijk
 */
template<
	template<typename Iter, typename Tp> class Accessor,
	typename T,
	typename STLIterator
>
VRangeIterator<typename Accessor<STLIterator, T>::Type> 
CreateAccesssorIterator(STLIterator begin, STLIterator end)
{
	VSTLAccessorRangePolicy<STLIterator, Accessor<STLIterator, T> > pol(begin, end);
	return VRangeIterator<typename Accessor<STLIterator, T>::Type>(pol);
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLACCESSORRANGEPOLICY_2005_05_21_H

