#ifndef V3D_VPOINTERSTORAGE_H
#define V3D_VPOINTERSTORAGE_H
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

// Warnung fuer gekappte Template Methoden Namen ausschalten
#pragma warning( disable : 4786)

/**
 * Smart pointer storage policy for pointers
 */
template<typename T>
class VPointerStorage
{
public:
	typedef T ValueType;
	typedef T* PointerType;
	typedef T& RefType;

	typedef T* AssignParam;

	VPointerStorage();
	virtual ~VPointerStorage();

	virtual PointerType Get() const;
	virtual void Assign(AssignParam in_pNewTarget);
	virtual void Release();

private:
	PointerType m_pTarget;
};

//-----------------------------------------------------------------------------
// include implementation file
#include "VPointerStorage.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPOINTERSTORAGE_H
