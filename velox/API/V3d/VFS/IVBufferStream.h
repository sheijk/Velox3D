/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVBUFFERSTREAM_H
#define V3D_IVBUFFERSTREAM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVOfflineStream.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Adds functions for streams which operate on buffers which have a limited size
 */
class IVBufferStream : public IVOfflineStream
{
public:
	/** return the size of the buffer in bytes */
	virtual ByteCount GetSize() = 0;

	/** change the size of the buffer */
	virtual void SetSize(ByteCount in_nNewSize) = 0;
};
		
//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVBUFFERSTREAM_H

