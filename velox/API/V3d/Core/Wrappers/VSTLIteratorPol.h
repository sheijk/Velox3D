#ifndef V3D_VSTLITERATORPOL_H
#define V3D_VSTLITERATORPOL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/IVIteratorPol.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

//TODO: move implementation to .inl

/**
 * an iterator policy for STL containers
 */

template<
	typename Iter,
	typename T = Iter::value_type
>
class VSTLIteratorPolBase : public IVIteratorPol<T>
{
protected:
	Iter m_Iter;

public:
	typedef T Value;
	typedef T* Pointer;

	VSTLIteratorPolBase(Iter in_Iter) : m_Iter(in_Iter) {}

	virtual void MoveBy(vint in_nDistance)
	{
		advance(m_Iter, in_nDistance);
	}

	virtual Pointer Get() const
	{
		return &(*m_Iter);
	}
};

template<
	typename Iter,
	typename T = Iter::value_type
>
class VSTLIteratorPol : public VSTLIteratorPolBase<Iter, T>
{
public:
	VSTLIteratorPol(Iter in_Iter) : VSTLIteratorPolBase<Iter,T>(in_Iter) {}

	virtual VSTLIteratorPol* CreateCopy() const
	{ 
		return new VSTLIteratorPol(m_Iter);
	}

	virtual int Compare(const IVIteratorPol<T>& in_Other) const
	{
		V3D_THROW(
			VUnsupportedIterOperation, 
			""
			);
	}
};

template<
typename Iter,
typename T = Iter::value_type
>
class VSTLIteratorPolFW : public VSTLIteratorPolBase<Iter, T>
{
public:
	VSTLIteratorPolFW(Iter in_Iter) : VSTLIteratorPolBase<Iter,T>(in_Iter) {}

	virtual VSTLIteratorPolFW* CreateCopy() const
	{ 
		return new VSTLIteratorPolFW(m_Iter);
	}

	virtual int Compare(const IVIteratorPol<T>& in_Other) const
	{
		VSTLIteratorPolFW& other = static_cast<VSTLIteratorPolFW&>(in_Other);

		return (m_Iter == other.m_Iter);
	}
};
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLITERATORPOL_H