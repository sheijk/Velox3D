#ifndef V3D_VGENERICUTILS_H
#define V3D_VGENERICUTILS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

	/**
	* A generic templates for creating a c-style compare function based on
	* the < and > operators for the two types
	* returns -1 if a < b, 1 if a > b and 0 if they are equal
	*/
	template<typename TypeA, typename TypeB>
		vint VCompare(const TypeA& a, const TypeB& b)
	{
		if( a < b )
			return -1;
		else if( a > b )
			return 1;
		else 
			return 0;
	}


//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGENERICUTILS_H
