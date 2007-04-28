#ifndef GEOMCLIPTERRAIN_TYPES_H_INCLUDED
#define GEOMCLIPTERRAIN_TYPES_H_INCLUDED

#include <iostream>
#include <sstream>

/**
 * Common types for cross compiler compatibility
 * and convenience + helper macros/functions
 */

// for convenience
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef signed char schar;
typedef unsigned char uchar;

// for compatibility
#ifdef _MSC_VER // ms visual c++

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef min
#undef max

typedef signed __int8 s8;
typedef unsigned __int8 u8;

typedef signed __int16 s16;
typedef unsigned __int16 u16;

typedef signed __int32 s32;
typedef unsigned __int32 u32;

typedef signed __int64 s64;
typedef unsigned __int64 u64;

#ifdef _DEBUG
#define GCT_LOG(msg)\
	{\
		std::stringstream str;\
		str << msg;\
		std::string s = str.str();\
		OutputDebugString( s.c_str() );\
		std::cout << s;\
	}
#else
#define GCT_LOG(msg) std::cout << msg;
#endif

#else // gcc
#include <stdint.h>

typedef int8_t s8;
typedef uint8_t u8;

typedef int16_t s16;
typedef uint16_t u16;

typedef int32_t s32;
typedef uint32_t u32;

typedef int64_t s64;
typedef uint64_t u64;

#define GCT_LOG(msg)\
	std::cout << msg;

#endif

#define GCT_PRINT GCT_LOG

#define GEOMCLIP_ERROR(x)\
	{\
		std::cout << "foo" << std::endl;\
		std::stringstream str;\
		str << "Fatal error in [" << __FILE__ << ":" << __LINE__ << "] ";\
		str << x;\
		std::string msg = str.str();\
		GCT_LOG( msg.c_str() );\
		char c; std::cin >> c;\
		exit( -1 );\
	}

//#define GEOMCLIP_ERROR(x)\
//    std::cerr << "Fatal error in [" << __FILE__ << ":" << __LINE__ << "] "\
//    << x << std::endl;\
//    exit(-1);

#ifdef _DEBUG
#define GCT_ASSERT(x) { if( !(x) ) { __asm { int 3 }; GEOMCLIP_ERROR("Assertion failure: " #x "\n"); } }
#else
#define GCT_ASSERT(x) { if( !(x) ) { GEOMCLIP_ERROR("Assertion failure: " #x "\n"); } }
#endif

#endif
