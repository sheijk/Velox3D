/**
 * Project: Velox3D
 *
 *
 * File		  :		P3DBUILD.H
 * 
 *
 * Discription:		Build Options for Velox3D
 *					
 *
 * History	  :
 *
 *			27-05.02 - CN created
 *
 * 
 */


/**
 * You can now comment your code like you wish. Only be sure it meets the doxygen
 * commenting style.
 */


#ifndef V3D_VBUILD_H
#define V3D_VBUILD_H

// version information
#define V3D_BUILD_NUMBER	1
#define V3D_VERSION_NUMBER	"1.0"

// platform constants
#define V3D_WIN32

// turn debugging-code on/off
#define V3D_DEBUG

// adjust debug level (0-4)
#define V3D_DEBUG_LEVEL		4

// automation which warrants that V3D_DEBUG_LEVEL is set to 0 if V3D_DEBUG is undefined
#ifndef V3D_DEBUG
#undef	V3D_DEBUG_LEVEL
#define V3D_DEBUG_LEVEL		0			
#endif

// automation which warrants that V3D_DEBUG is undefined if V3D_DEBUG_LEVEL is set to 0
#if V3D_DEBUG_LEVEL == 0
#undef V3D_DEBUG
#endif


#endif