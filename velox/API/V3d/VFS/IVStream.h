#ifndef V3D_IVSTREAM_H
#define V3D_IVSTREAM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include <v3d/Vfs/IVLegalOperations.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
* Streaming Interface
* Provides methods to read and write data. A stream is anything that can receive
* and/or provide data.
* @author sheijk
* @version 1.0
* @updated 26-May-2003 13:31:08
*/
class IVStream
{
public:
	typedef vlong ByteCount;
	typedef vlong StreamPos;
	typedef const IVLegalOperations* LegalOpsPtr;

	virtual ~IVStream() {};

	/** anchors for changing the stream's r/w position */
	enum Anchor { Begin, End, CurrentPos };

	/** write data to stream */
	virtual void Write(const void* in_pSource, ByteCount in_nByteCount) = 0;

	/** read data from stream. returns number of read bytes */
	virtual ByteCount Read(void* out_pDest, ByteCount in_pBytesToRead) = 0;

	/** reset r/w position */
	virtual void SetPos(Anchor in_Anchor, ByteCount in_nDistance) = 0;

	/** get r/w position */
	virtual StreamPos GetPos() const = 0;

	/** get a list of legal operations */
	virtual LegalOpsPtr GetLegalOps() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVSTREAM_H
