#ifndef V3D_VMEMORY_H
#define V3D_VMEMORY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

	template<typename T> void SafeDelete(T*& ptr)
	{
		if( 0 != ptr )
		{
			delete ptr;
			ptr = 0;
		}
	}

	template<typename T> void SafeDeleteArray(T*& arr)
	{
		if( 0 != arr )
		{
			delete[] arr;
			arr = 0;
		}
	}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMEMORY_H
