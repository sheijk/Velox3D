#ifndef V3D_VARRAYSTORAGE_H
#define V3D_VARRAYSTORAGE_H
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

// Warnung fuer gekappte Template Methoden Namen ausschalten
#pragma warning( disable : 4786)

/**
 * Smart Pointer Storage class for arrays
 */
template<typename T>
class VArrayStorage
{
public:
	typedef T* TargetType;

	VArrayStorage();
	~VArrayStorage();

	void Set(TargetType in_pNewTarget);
	TargetType Get() const;
	virtual void Release();

private:
	TargetType m_pTarget;
};

//-----------------------------------------------------------------------------
// include implementation file
#include "VArrayStorage.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VARRAYSTORAGE_H
