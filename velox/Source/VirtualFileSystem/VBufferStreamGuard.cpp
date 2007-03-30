/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VBufferStreamGuard.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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

