/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VOfflineStreamGuard.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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

