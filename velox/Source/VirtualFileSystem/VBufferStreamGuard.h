//TODO: correct file guard
#ifndef V3D_VBufferStreamGuard_H
#define V3D_VBufferStreamGuard_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVBufferStream.h>

#include "VStreamGuard.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Checks whether performed operations are allowed for an IVOfflineStream
 */
class VBufferStreamGuard : public VStreamGuardTempl<IVBufferStream>
{
public:
	VBufferStreamGuard(IVBufferStream* in_pStreamToGuard);
	virtual ~VBufferStreamGuard();

	/** calls Disconnect() on guarded stream */
	virtual void Disconnect();

	/** calls Connect() on guarded stream */
	virtual void Connect();

	/** returns IsConnected() of guarded stream */
	virtual vbool IsConnected() const;

	/** returns GetSize of guarded stream */
	virtual ByteCount GetSize();

	/** calls SetSize of guarded stream */
	virtual void SetSize(ByteCount in_nNewSize);
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBufferStreamGuard_H
