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
class VSTLIteratorPol : public IVIteratorPol<T>
{
protected:
	Iter m_Iter;

public:
	typedef T Value;
	typedef T* Pointer;

	VSTLIteratorPol(Iter in_Iter) : m_Iter(in_Iter) {}

	virtual vbool IsEqual(const IVIteratorPol<T>& in_Other) const
	{ 
		return m_Iter == ((VSTLIteratorPol&)in_Other).m_Iter;
	}

	virtual VSTLIteratorPol* CreateCopy() const
	{ return new VSTLIteratorPol(m_Iter); }

	virtual void MoveBy(vint in_nDistance)
	{
		advance(m_Iter, in_nDistance);
	}

	virtual Pointer Get() const
	{
		return &(*m_Iter);
	}

	virtual void Proceed() { MoveBy(1); }
	virtual void MoveBack() { MoveBy(-1); }
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLITERATORPOL_H