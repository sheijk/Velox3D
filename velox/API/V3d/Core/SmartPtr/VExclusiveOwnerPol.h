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
class VExclusiveOwnerPol : protected StoragePolicy
{
protected:
	typedef typename StoragePolicy::AssignParam AssignParam;
	typedef typename StoragePolicy::Pointer Pointer;
	typedef typename StoragePolicy::Value Value;
	typedef typename StoragePolicy::Reference Reference;

	VExclusiveOwnerPol();

	Pointer Get() const;
	virtual void Assign(AssignParam in_NewVal);
	virtual void Release();
	virtual void Clone(VExclusiveOwnerPol<StoragePolicy>& in_Other);
	virtual bool IsEqual(const VExclusiveOwnerPol& in_Other) const;
};

//-----------------------------------------------------------------------------
// include implementation
#include "VExclusiveOwnerPol.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VEXCLUSIVEOWNERPOLICY_H
