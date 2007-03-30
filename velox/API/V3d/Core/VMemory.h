/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMEMORY_H
#define V3D_VMEMORY_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

	/**
	 * Use this instead of delete.
	 * @author sheijk
	 */
	template<typename T> void SafeDelete(T*& ptr)
	{
		if( 0 != ptr )
		{
			delete ptr;
			ptr = 0;
		}
	}
	
	/**
	 * Safe deleting arrays. Use this instead of delete[]
	 * @author sheijk
	 */
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

