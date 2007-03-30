/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: correct file guard
#ifndef V3D_VBufferStreamGuard_H
#define V3D_VBufferStreamGuard_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/VFS/IVBufferStream.h>

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

