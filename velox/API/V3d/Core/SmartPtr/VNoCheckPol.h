#ifndef V3D_VNOCHECKPOL_H
#define V3D_VNOCHECKPOL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

// Warnung fuer gekappte Template Methoden Namen ausschalten
#pragma warning( disable : 4786)

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/*!
	Checking Policy fuer SmartHandle/SmartPointers
	fuehrt keine Ueberpruefung aus
*/
template<typename T>
class VNoCheckPol
{

public:
	VNoCheckPol() {}
	~VNoCheckPol() {}

public:
	/*! every value is fine :) */
	static inline vbool IsValid(T in_Val) 
	{ 
		return true;
	}

	/*! nothing to do here */
	static inline void Check(T in_Val) {}
};

//-----------------------------------------------------------------------------
} // namespace v3d
#endif // V3D_VNOCHECKPOL_H
