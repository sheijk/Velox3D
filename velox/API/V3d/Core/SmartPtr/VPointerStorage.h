#ifndef V3D_VPOINTERSTORAGE_H
#define V3D_VPOINTERSTORAGE_H
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

// Warnung fuer gekappte Template Methoden Namen ausschalten
#pragma warning( disable : 4786)

/*!
	StoragePolicy fuer SmartHandle/SmartPointer
	speichert einen Zeiger
*/
template<typename T>
class VPointerStorage
{
public:
	typedef T* TargetType;

	VPointerStorage();
	~VPointerStorage();

public:
	void Set(TargetType in_pNewTarget);
	TargetType Get();
	void Release();

private:
	TargetType m_pTarget;
};

//-----------------------------------------------------------------------------
// include implementation file
#include "VPointerStorage.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPOINTERSTORAGE_H
