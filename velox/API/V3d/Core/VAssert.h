/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VASSERT_H
#define V3D_VASSERT_H
//-----------------------------------------------------------------------------
#include <V3D/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

void _V3DAssert( vbool bExp, const vchar* cFile, const vuint iLine, const vchar* cExp );

// empty makros for release
#ifndef V3D_DEBUG
	#define V3D_ASSERT(exp) (void(0))
	#define V3D_VERIFY(exp) (exp)
#endif


#ifdef V3D_DEBUG
	#define V3D_ASSERT(exp) (_V3DAssert(exp, __FILE__, __LINE__, #exp))
	#define V3D_VERIFY(exp) (V3D_ASSERT(exp))
#endif

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif
