#ifndef V3D_VSTREAMTOOFFLINESTREAMWRAPPER_H
#define V3D_VSTREAMTOOFFLINESTREAMWRAPPER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/VFS/IVOfflineStream.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Wraps any IVStream to an IVOfflineStream
 * Manages connection state and throws exception if stream
 * is not connected when trying to read/write/setpos
 */
class VStreamToOfflineStreamWrapper : public IVOfflineStream
{
	// the wrapped stream
	VPointer<IVStream>::AutoPtr m_pStream;

	// is the stream connected?
	vbool m_bConnected;

public:
	VStreamToOfflineStreamWrapper(IVStream* in_pStream);

	virtual void Write(const void* in_pSource, ByteCount in_nByteCount);
	virtual ByteCount Read(void* out_pDest, ByteCount in_pBytesToRead);
	virtual void SetPos(Anchor in_Anchor, ByteCount in_nDistance);
	virtual StreamPos GetPos() const;
	virtual LegalOpsPtr GetLegalOps() const;

	virtual void Disconnect();
	virtual void Connect();
	virtual vbool IsConnected() const;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTREAMTOOFFLINESTREAMWRAPPER_H
