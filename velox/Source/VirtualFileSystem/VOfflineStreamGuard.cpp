#include "VOfflineStreamGuard.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VOfflineStreamGuard::VOfflineStreamGuard(IVOfflineStream* in_pStreamToGuard)
	: VStreamGuardTempl<IVOfflineStream>(in_pStreamToGuard)
{
}

/**
 * d'tor
 */
VOfflineStreamGuard::~VOfflineStreamGuard()
{
}

void VOfflineStreamGuard::Disconnect()
{
	GetGuardedStream().Disconnect();
}

void VOfflineStreamGuard::Connect()
{
	GetGuardedStream().Connect();
}

vbool VOfflineStreamGuard::IsConnected() const
{
	return GetGuardedStream().IsConnected();
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
