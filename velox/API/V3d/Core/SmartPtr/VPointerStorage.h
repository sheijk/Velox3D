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
	/** the data type which the storage stores */
	typedef T Value;
	typedef T* Pointer;
	typedef T& Reference;

	/** parameter for assignment */
	typedef T* AssignParam;

	VPointerStorage();
	virtual ~VPointerStorage();

	virtual Pointer Get() const;
	virtual void Assign(AssignParam in_pNewTarget);
	virtual void Release();
	virtual bool IsEqual(const VPointerStorage& in_Other) const;

private:
	Pointer m_pTarget;
};

//-----------------------------------------------------------------------------
// include implementation file
#include "VPointerStorage.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VPOINTERSTORAGE_H
