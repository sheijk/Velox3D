/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VFLAGS_H
#define V3D_VFLAGS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Determines how a file/etc. shall be opened
 */
enum VCreationFlags
{
	VCreateNew,
	VCreateAlways,
	VOpenExisting,
	VOpenAlways,
	VTruncate
};

/**
 * Specifies the desired access mode when opening a data source
 */
enum VAccessModeFlags
{
	VReadAccess = 1,
	VWriteAccess = 2,
	VRWAccess = 3
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VFLAGS_H

