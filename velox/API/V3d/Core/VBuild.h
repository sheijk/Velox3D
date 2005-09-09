/**
 * Build Options for Velox3D
 */

#ifndef V3D_VBUILD_H
#define V3D_VBUILD_H
//-----------------------------------------------------------------------------

// version information
#define V3D_BUILD_NUMBER	1
#define V3D_VERSION_NUMBER	"0.1"

// platform constants
#ifdef WIN32
#define V3D_WIN32
#endif

// compiler constants
#ifdef _MSC_VER
#define V3D_MSVC
#endif

// turn debugging-code on/off
#ifdef _DEBUG
#define V3D_DEBUG
#endif

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

//-----------------------------------------------------------------------------
#endif // V3D_VBUILD_H