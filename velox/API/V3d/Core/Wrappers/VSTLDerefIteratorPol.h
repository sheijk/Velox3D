#ifndef V3D_VSTLDEREFITERATORPOL_H
#define V3D_VSTLDEREFITERATORPOL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/IVIteratorPol.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

//TODO: move implementation to .inl

// ACHTUNG: fuer random_access_iteratoren (z.bsp von std::vector) 
// VSTLDerefIteratorPolFW benutzen, sonst wird kein Vergleich unterstuetzt

/**
 * an iterator policy for STL container which store pointers
 * (i.e. std::list<int*>, std::vector<VPointer<VString>::AutoPtr>
 */
template<
	typename Iter,
	typename T
>
class VSTLDerefIteratorPol : public IVIteratorPol<T>
{
protected:
	Iter m_Iter;

public:
	typedef T Value;
	typedef T* Pointer;

	VSTLDerefIteratorPol(Iter in_Iter) : m_Iter(in_Iter) {}

	virtual IVIteratorPol<T>* CreateCopy() const
	{ 
		return new VSTLDerefIteratorPol(m_Iter);
	}
	
	virtual int Compare(const IVIteratorPol<T>& in_Other) const
	{
		V3D_THROW(
			VUnsupportedIterOperation, 
			""//V3D_TEMP_CAUSE(Iter)
			);
	}

	virtual void MoveBy(vint in_nDistance)
	{
		advance(m_Iter, in_nDistance);
	}

	virtual Pointer Get() const
	{
		return *m_Iter;
	}

//#define V3D_TEMP_CAUSE(x) "Iterator type" #x " is not comparable"

//#undef V3D_TEMP_CAUSE
};

template<
	typename Iter,
	typename T
	>
class VSTLDerefIteratorPolFW : public IVIteratorPol<T>
{
protected:
	Iter m_Iter;

public:
	typedef T Value;
	typedef T* Pointer;

	VSTLDerefIteratorPolFW(Iter in_Iter) : m_Iter(in_Iter) {}

	virtual VSTLDerefIteratorPolFW* CreateCopy() const
	{ return new VSTLDerefIteratorPolFW(m_Iter); }

	virtual void MoveBy(vint in_nDistance)
	{
		advance(m_Iter, in_nDistance);
	}

	virtual Pointer Get() const
	{
		return *m_Iter;
	}

	virtual int Compare(const IVIteratorPol<T>& in_Other) const
	{
		VSTLDerefIteratorPolFW& other = static_cast<VSTLDerefIteratorPolFW&>(in_Other);

        return (m_Iter == other.m_Iter);
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLDEREFITERATORPOL_H
