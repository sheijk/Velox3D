/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_MEMLOCALSETTINGS_2004_08_26_H
#define V3D_MEMLOCALSETTINGS_2004_08_26_H
//-----------------------------------------------------------------------------
// Some defines to change the behaviour of the memory manager
//
// This file should never be committed to the cvs. Changes should be kept
// locally to allow every developer using his own mem manager settings (and
// keeping them when updating from cvs
//-----------------------------------------------------------------------------

// enable memory logging
//#define V3D_MEM_ENABLE_LOGGING

// show every allocation/release
//#define V3D_MEM_SHOW_ALLOCRELEASE

// print .a. for allocations and .r. for releases
//#define V3D_MEM_SHOW_SHORTALLOCRELEASE

//-----------------------------------------------------------------------------
#endif // V3D_MEMLOCALSETTINGS_2004_08_26_H

