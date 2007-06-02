/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVSTREAM_H
#define V3D_IVSTREAM_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/SmartPtr/VGuards.h>

#include <V3d/VFS/IVLegalOperations.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * A streaming interface. Provides methods for writing to and reading
 * from a stream and set/get it's read/write position.
 * Is the base class for file, memory, network, .. streams. Use it
 * whenever you have to read from/write to a buffer
 */
class IVStream
{
public:
	/** A signed number of bytes */
	typedef vlong ByteCount;

	/** Type for the read/write position of a stream */
	typedef vlong StreamPos;

	/** Pointer to the IVLegalOperations interface (-> GetLegalOps()) */
	typedef const IVLegalOperations* LegalOpsPtr;

	virtual ~IVStream() {};

	/** Anchors for changing the stream's r/w position */
	enum Anchor { Begin, End, CurrentPos };

	/** Write data to stream. Throws VIOException if data could not be written */
	virtual void Write(const void* in_pSource, ByteCount in_nByteCount) = 0;

	/** Read data from stream. Returns number of read bytes */
	virtual ByteCount Read(void* out_pDest, ByteCount in_pBytesToRead) = 0;

	/** Reset r/w position. Anchor determines from where distance is measured */
	virtual void SetPos(Anchor in_Anchor, ByteCount in_nDistance) = 0;

	/** Get read/write position */
	virtual StreamPos GetPos() const = 0;

	/** Get information about which operations may be performed on this stream */
	virtual LegalOpsPtr GetLegalOps() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVSTREAM_H

