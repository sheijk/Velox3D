///////////////////////////////////////////////////////////
//
//  VExclusiveOwnerPol.h
//  Implementation of the Class VExclusiveOwnerPol
//  Generated by Enterprise Architect
//  Created on:      16-Feb-2003 14:05:49
//  Original author: sheijk
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(VExclusiveOwnerPol_2846BEDC_9FF0_487a_8844_F6DD70E9050F__INCLUDED_)
#define VExclusiveOwnerPol_2846BEDC_9FF0_487a_8844_F6DD70E9050F__INCLUDED_

// Warnung fuer gekappte Template Methoden Namen ausschalten
#pragma warning( disable : 4786)

/*!
	exclusive owner policy
	Policy fuer VSmartHandle/Pointer, welche sich wie std::auto_ptr verhaelt
	Beim kopieren wird die Quelle auf NULL gesetzt, nur ein Pointer zeigt zur
	Zeit auf das gleiche Ziel, beim Freigeben wird geloescht.
*/
template<class StoragePolicy>
class VExclusiveOwnerPol
{
public:
	typedef StoragePolicy::TargetType TargetType;
	VExclusiveOwnerPol();
	~VExclusiveOwnerPol();

	TargetType Get();
	void Set(TargetType in_NewVal);
	void Release();
	void Clone(VExclusiveOwnerPol<StoragePolicy>& in_Other);
private:
	StoragePolicy m_Storage;

	// um Fehler durch automatisch generierte Fkten zu vermeiden:
	VExclusiveOwnerPol(const VExclusiveOwnerPol<StoragePolicy>& x);
	operator=(const VExclusiveOwnerPol<StoragePolicy>& x);
};

// include implementation
#include "VExclusiveOwnerPol.inl"

#endif // !defined(VExclusiveOwnerPol_2846BEDC_9FF0_487a_8844_F6DD70E9050F__INCLUDED_)
