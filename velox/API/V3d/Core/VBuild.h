/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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

#ifdef __GNUC__
#ifdef __APPLE__
#define V3D_MAC
#else
#define V3D_LX
#endif
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
