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
 * read or written.
 */
class IVOfflineStream : public IVStream
{
public:
	/** disconnect the stream */
	virtual void Disconnect() = 0;

	/** (re-)connect the stream */
	virtual void Connect() = 0;

	/** true -> read, write, set/get pos possible */
	virtual vbool IsConnected() const  = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVOFFLINESTREAM_H
