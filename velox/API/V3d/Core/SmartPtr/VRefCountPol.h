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

	PointerType GetTarget() const;
	void AssignTarget(AssignParam in_NewVal);
	void ReleaseTarget();
	void Clone(const VRefCountPol<StoragePolicy>& in_Other);

protected:
	VRefCountPol();

private:
	typedef VRefCountPol<StoragePolicy> Type;
	typedef VRefCountSharedStorage<StoragePolicy> SharedStorage;

	SharedStorage* m_pSharedStorage;

	void CreateSharedStorage(PointerType in_Subject);

	void operator=(const VRefCountPol<SharedStorage>&);
	VRefCountPol(const VRefCountPol<SharedStorage>&);

};

//-----------------------------------------------------------------------------
#include "VRefCountPol.inl"
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VREFCOUNTPOL_H
