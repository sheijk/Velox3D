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
private:
	typedef typename StoragePolicy::TargetType TargetType;
	
	typedef VRefCountPol<StoragePolicy> Type;
	typedef VRefCountSharedStorage<StoragePolicy> SharedStorage;

	SharedStorage* m_pSharedStorage;

	void CreateSharedStorage(TargetType in_Subject);
public:
	VRefCountPol();
	~VRefCountPol();

	typename TargetType Get() const;
	void Set(TargetType in_NewVal);
	void Release();
	void Clone(const Type& in_Other);
};

//-----------------------------------------------------------------------------
#include "VRefCountPol.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VREFCOUNTPOL_H
