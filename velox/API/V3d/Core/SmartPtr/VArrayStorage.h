#ifndef V3D_VARRAYSTORAGE_H
#define V3D_VARRAYSTORAGE_H
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

// Warnung fuer gekappte Template Methoden Namen ausschalten
#pragma warning( disable : 4786)

//TODO: const Get() Version

/**
 * Smart pointer storage policy for arrays
 */
template<typename T>
class VArrayStorage
{
public:
	typedef T ValueType;
	typedef T* PointerType;
	typedef T& RefType;

	typedef T* AssignParam;

	VArrayStorage();
	virtual ~VArrayStorage();

	virtual PointerType Get() const;
	virtual void Assign(AssignParam in_pNewTarget);
	virtual void Release();

	/** add an array style access operator */
	RefType operator[](const unsigned int in_nIndex);

private:
	PointerType m_pTarget;
};

//-----------------------------------------------------------------------------
// include implementation file
#include "VArrayStorage.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VARRAYSTORAGE_H
