#ifndef V3D_VASSERT_H
#define V3D_VASSERT_H

#include <Core/VTypes.h>


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

#endif