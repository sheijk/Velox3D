#ifndef V3D_VREFCOUNTPOL_H
#define V3D_VREFCOUNTPOL_H
//-----------------------------------------------------------------------------
#include "VRefCountSharedStorage.h"

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * Teilt sich das gleiche Target mit mehreren Pointern, wenn kein Pointer mehr auf
 * das Objekt verweist wird es freigegeben
 * 
 * set: erstellt einen neue VRefCountSharedStorage
 * clone: erhoeht den RefCount der Storage des geklonten Objekts um eins
 * @author sheijk
 * @version 1.0
 * @updated 19-Mar-2003 03:02:21
 */
template<class StoragePolicy>
class VRefCountPol
{
public:
	typedef typename StoragePolicy::AssignParam AssignParam;
	typedef typename StoragePolicy::PointerType PointerType;
	typedef typename StoragePolicy::ValueType ValueType;
	typedef typename StoragePolicy::RefType RefType;

	PointerType Get() const;
	void Assign(AssignParam in_NewVal);
	void Release();
	void Clone(const VRefCountPol<StoragePolicy>& in_Other);

protected:
	VRefCountPol();

private:
	typedef VRefCountPol<StoragePolicy> Type;
	typedef VRefCountSharedStorage<StoragePolicy> SharedStorage;

	/** hold the ptr and the ref. count */
	SharedStorage* m_pSharedStorage;

	/** create the object which hold the ptr and ref count */
	void CreateSharedStorage(PointerType in_Subject);

	// no copying etc.
	void operator=(const VRefCountPol<SharedStorage>&);
	VRefCountPol(const VRefCountPol<SharedStorage>&);
};

//-----------------------------------------------------------------------------
#include "VRefCountPol.inl"
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VREFCOUNTPOL_H
