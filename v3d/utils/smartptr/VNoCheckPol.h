///////////////////////////////////////////////////////////
//
//  VNoCheckPol.h
//  Implementation of the Class VNoCheckPol
//  Generated by Enterprise Architect
//  Created on:      16-Feb-2003 14:05:51
//  Original author: sheijk
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(VNoCheckPol_9FFE1BA4_3B69_45f7_8C74_369A85370189__INCLUDED_)
#define VNoCheckPol_9FFE1BA4_3B69_45f7_8C74_369A85370189__INCLUDED_

/*!
	Checking Policy fuer SmartHandle/SmartPointers
	fuehrt keine Ueberpruefung aus
*/
template<typename T>
class VNoCheckPol
{

public:
	VNoCheckPol() {}
	virtual ~VNoCheckPol() {}

public:
	/*! every value is fine :) */
	static inline vbool IsValid(T in_Val) 
	{ 
		return true;
	}

	/*! nothing to do here */
	static inline void Check(T in_Val) {}
};

#endif // !defined(VNoCheckPol_9FFE1BA4_3B69_45f7_8C74_369A85370189__INCLUDED_)
