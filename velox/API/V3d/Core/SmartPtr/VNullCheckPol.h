#ifndef V3D_VNULLCHECKPOL_H
#define V3D_VNULLCHECKPOL_H
//-----------------------------------------------------------------------------

// Warnung fuer gekappte Template Methoden Namen ausschalten
#pragma warning( disable : 4786)

#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

template<typename T>
class VNullCheckPol
{

public:
	VNullCheckPol() {}
	~VNullCheckPol() {}

public:
	static inline vbool IsValid(T in_Val)
	{
		return 0 != in_Val;
	}

	static inline void Check(T in_Val)
	{
		if( ! IsValid(in_Val) )
		{
			V3D_THROW(VException, "NullPointer Access");
		}
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
#endif // V3D_VNULLCHECKPOL_H
