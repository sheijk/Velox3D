#ifndef V3D_VDEBUG_H
#define V3D_VDEBUG_H

/**
 *	Build without assertions.
 */

#undef	V3DASSERT

#if V3D_DEBUG_LEVEL < 2
	#define V3DASSERT(CONDITION) {}
#else
	// TODO: Not implement now
	#define V3DASSERT(CONDITION)
#endif

/**
 * V3DVERIFY is nearly equal to V3DASSERT, except that the test is being performed in release builds as well.
 * Make sure you use this macro instead when things are getting dangerous.
 */

#define V3DVERIFY(CONDITION){}

#define V3D_QUOTE(x) # x
#define V3DQUOTE(x) V3D_QUOTE(x)
#define V3D__FILE__LINE__ __FILE__ "(" QUOTE(__LINE__) ") : "

#define V3DNOTE( x )  message( x )
#define V3DFILELINE  message( V3D__FILE__LINE__ )
#define V3DTODO( x )  message( V3D__FILE__LINE__" TODO :   " #x "\n" ) 
#define V3DFIXME( x )  message( V3D__FILE__LINE__" FIXME:   " #x "\n" ) 


#endif