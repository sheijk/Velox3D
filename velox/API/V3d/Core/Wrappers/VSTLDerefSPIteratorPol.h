#ifndef V3D_VSTLDEREFSPITERATORPOL_H
#define V3D_VSTLDEREFSPITERATORPOL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/IVIteratorPol.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * an iterator policy for STL container which store pointers
 * (i.e. std::list<int*>, std::vector<VPointer<VString>::AutoPtr>
 */
template<
	typename Iter,
	typename T
>
class VSTLDerefSPIteratorPol : public IVIteratorPol<T>
{
	Iter m_Iter;

public:
	VSTLDerefSPIteratorPol(Iter in_Iter) 
		: m_Iter(in_Iter) {}

	virtual vbool IsEqual(const IVIteratorPol<T>& in_Other) const
	{ 
		//TODO: "korrekte" Version machen

		return m_Iter == ((VSTLDerefSPIteratorPol&)in_Other).m_Iter;

		//return *m_Iter == in_Other.Get(); 
	}

	virtual VSTLDerefSPIteratorPol* CreateCopy() const
	{ return new VSTLDerefSPIteratorPol(m_Iter); }

	virtual void MoveBy(vint in_nDistance)
	{
		advance(m_Iter, in_nDistance);
	}

	virtual Pointer Get() const
	{
		Iter::value_type val = *m_Iter;

		T* ptr = val.Get();

		return ptr;
	}

	virtual void Proceed() { MoveBy(1); }
	virtual void MoveBack() { MoveBy(-1); }	
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTLDEREFSPITERATORPOL_H
