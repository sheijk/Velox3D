//TODO: correct file guard
#ifndef V3D_VOfflineStreamGuard_H
#define V3D_VOfflineStreamGuard_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVOfflineStream.h>

#include "VStreamGuard.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Checks whether performed operations are allowed for an IVOfflineStream
 */
class VOfflineStreamGuard : public VStreamGuardTempl<IVOfflineStream>
{
public:
	VOfflineStreamGuard(IVOfflineStream* in_pStreamToGuard);
	virtual ~VOfflineStreamGuard();

	/** calls Disconnect() on guarded stream */
	virtual void Disconnect();

	/** calls Connect() on guarded stream */
	virtual void Connect();

	/** returns IsConnected() of guarded stream */
	virtual vbool IsConnected() const;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VOfflineStreamGuard_H
