#ifndef V3D_VSTLDEREFITERATORPOL_H
#define V3D_VSTLDEREFITERATORPOL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/IVIteratorPol.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

//TODO: move implementation to .inl

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
private:
	Iter m_Iter;

public:
	typedef T Value;
	typedef T* Pointer;

	VSTLDerefIteratorPol(Iter in_Iter) : m_Iter(in_Iter) {}

	virtual vbool IsEqual(const IVIteratorPol<T>& in_Other) const
	{ 
		//TODO: "korrekte" Version machen

		return m_Iter == ((VSTLDerefIteratorPol&)in_Other).m_Iter;

		//return *m_Iter == in_Other.Get(); 
	}

	virtual VSTLDerefIteratorPol* CreateCopy() const
	{ return new VSTLDerefIteratorPol(m_Iter); }

	virtual void MoveBy(vint in_nDistance)
	{
		advance(m_Iter, in_nDistance);
	}

	virtual Pointer Get() const
	{
		return *m_Iter;
	}

	virtual void Proceed() { MoveBy(1); }
	virtual void MoveBack() { MoveBy(-1); }
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLDEREFITERATORPOL_H
