#ifndef V3D_VEXCLUSIVEOWNERPOLICY_H
#define V3D_VEXCLUSIVEOWNERPOLICY_H
//-----------------------------------------------------------------------------

// Warnung fuer gekappte Template Methoden Namen ausschalten
#pragma warning( disable : 4786)

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * Policy fuer VSmartHandle/Pointer, welche sich wie std::auto_ptr verhaelt
 * Beim kopieren wird die Quelle auf NULL gesetzt, nur ein Pointer zeigt zur
 * Zeit auf das gleiche Ziel, beim Freigeben wird geloescht.
 */
template<class StoragePolicy>
class VExclusiveOwnerPol : public StoragePolicy
{
public:
	typedef typename StoragePolicy::AssignParam AssignParam;
	typedef typename StoragePolicy::PointerType PointerType;
	typedef typename StoragePolicy::ValueType ValueType;
	typedef typename StoragePolicy::RefType RefType;

	PointerType Get() const;
	virtual void Assign(AssignParam in_NewVal);
	virtual void Release();
	virtual void Clone(VExclusiveOwnerPol<StoragePolicy>& in_Other);

//protected:
	VExclusiveOwnerPol();

private:
	//StoragePolicy m_Storage;

	//// um Fehler durch automatisch generierte Fkten zu vermeiden:
	//VExclusiveOwnerPol(const VExclusiveOwnerPol<StoragePolicy>& x);
	//operator=(const VExclusiveOwnerPol<StoragePolicy>& x);
};

//-----------------------------------------------------------------------------
// include implementation
#include "VExclusiveOwnerPol.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VEXCLUSIVEOWNERPOLICY_H
