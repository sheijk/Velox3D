///////////////////////////////////////////////////////////
//
//  VPointerStorage.h
//  Implementation of the Class VPointerStorage
//  Generated by Enterprise Architect
//  Created on:      16-Feb-2003 14:05:54
//  Original author: sheijk
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(VPointerStorage_038F7800_9B5D_4a82_8095_2326379D0025__INCLUDED_)
#define VPointerStorage_038F7800_9B5D_4a82_8095_2326379D0025__INCLUDED_

// Warnung fuer gekappte Template Methoden Namen ausschalten
#pragma warning( disable : 4786)

/*!
	StoragePolicy fuer SmartHandle/SmartPointer
	speichert einen Zeiger
*/
template<typename T>
class VPointerStorage
{
public:
	typedef T* TargetType;

	VPointerStorage();
	~VPointerStorage();

public:
	void Set(TargetType in_pNewTarget);
	TargetType Get();
	void Release();

private:
	TargetType m_pTarget;
};

// include implementation file
#include "VPointerStorage.inl"

#endif // !defined(VPointerStorage_038F7800_9B5D_4a82_8095_2326379D0025__INCLUDED_)
