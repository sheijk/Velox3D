#include "VBufferStreamGuard.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VBufferStreamGuard::VBufferStreamGuard(IVBufferStream* in_pStreamToGuard)
	: VStreamGuardTempl<IVBufferStream>(in_pStreamToGuard)
{
}

/**
 * d'tor
 */
VBufferStreamGuard::~VBufferStreamGuard()
{
}

void VBufferStreamGuard::Disconnect()
{
	GetGuardedStream().Disconnect();
}

void VBufferStreamGuard::Connect()
{
	GetGuardedStream().Connect();
}

vbool VBufferStreamGuard::IsConnected() const
{
	return GetGuardedStream().IsConnected();
}

IVStream::ByteCount VBufferStreamGuard::GetSize()
{
	return GetGuardedStream().GetSize();
}

void VBufferStreamGuard::SetSize(ByteCount in_nNewSize)
{
	GetGuardedStream().SetSize(in_nNewSize);
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
