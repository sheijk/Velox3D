#ifndef V3D_VSMARTHANDLEBASE_H
#define V3D_VSMARTHANDLEBASE_H
//-----------------------------------------------------------------------------

// Warnung fuer gekappte Template Methoden Namen ausschalten
#pragma warning( disable : 4786)

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/*!
	VSmartHandleBase
	kann von SmartPointer etc. benutzt werden, kapselt das Zusammenspiel
	zwischen den einzelnen SmartPointer/Handle Policies
	!!! keine Klassen hiervon ableiten !!!
*/
template<typename T,class OwnerPolicy,class ReadCheckPolicy,class WriteCheckPolicy>
class VSmartHandleBase
{
public:
	VSmartHandleBase();
	// gefaehrlich, aber wuerde ansonsten platz verschwenden, s.o.
	~VSmartHandleBase();

	typedef VSmartHandleBase<T, OwnerPolicy, ReadCheckPolicy, WriteCheckPolicy> 
		SmartHandleBaseType;

	T GetTarget();
	void SetTarget(T in_NewTarget);
	void Clone(const SmartHandleBaseType& in_Other);
	void ReleaseTarget();

private:
	typedef VSmartHandleBase<T, OwnerPolicy, ReadCheckPolicy, WriteCheckPolicy> MyType;

	VSmartHandleBase(const MyType& in_Other);

	OwnerPolicy m_Owner;
	ReadCheckPolicy m_ReadGuard;
	WriteCheckPolicy m_WriteGuard;
};

//-----------------------------------------------------------------------------
// implementation
#include "VSmartHandleBase.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSMARTHANDLEBASE_H
