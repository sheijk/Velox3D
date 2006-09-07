/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVOFFLINESTREAM_H
#define V3D_IVOFFLINESTREAM_H
//-----------------------------------------------------------------------------
#include <V3d\VFS\IVStream.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * A stream which can go offline/disconnect. While disconnected no data can be
 * read or written. (Base class of file stream, etc.)
 */
class IVOfflineStream : public IVStream
{
public:
	/** Disconnect the stream. No operations can be performed until 
		Connect() is called */
	virtual void Disconnect() = 0;

	/** (Re-)connect the stream. Operations like read/write/setpos/getpos
		can be performed again after calling it */
	virtual void Connect() = 0;

	/** Returns whether operations like read/write/setpos/getpos may be
		performed on the stream */
	virtual vbool IsConnected() const  = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVOFFLINESTREAM_H

