#ifndef V3D_VStreamGuard_H
#define V3D_VStreamGuard_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVStream.h>
#include <v3d/VFS/VIOException.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * A stream guard "wraps" an IVStream, and checks whether the performed
 * operations (write, read, get/setpos) are allowed by the stream's
 * legal operations
 */
template<typename ParentStream>
class VStreamGuardTempl : public ParentStream
{
	ParentStream* m_pGuardedStream;

protected:
	ParentStream& GetGuardedStream();
	const ParentStream& GetGuardedStream() const;

public:
	using typename ParentStream::ByteCount;
	using typename ParentStream::Anchor;
	using typename ParentStream::StreamPos;
	using typename ParentStream::LegalOpsPtr;

	VStreamGuardTempl(ParentStream* in_pStreamToGuard);
	virtual ~VStreamGuardTempl();

	virtual void Write(const void* in_pSource, ByteCount in_nByteCount);

	virtual ByteCount Read(void* out_pDest, ByteCount in_pBytesToRead);

	virtual void SetPos(Anchor in_Anchor, ByteCount in_nDistance);

	virtual StreamPos GetPos() const;

	virtual LegalOpsPtr GetLegalOps() const;
};

typedef VStreamGuardTempl<IVStream> VStreamGuard;

//-----------------------------------------------------------------------------
#include "VStreamGuard.inl"
//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VStreamGuard_H
