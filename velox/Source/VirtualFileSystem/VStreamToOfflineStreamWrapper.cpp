/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VStreamToOfflineStreamWrapper.h"
//-----------------------------------------------------------------------------
#include <V3d/VFS/VIOException.h>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

VStreamToOfflineStreamWrapper
	::VStreamToOfflineStreamWrapper(IVStream* in_pStream)
{
	m_pStream.Assign(in_pStream);
	m_bConnected = true;
}

void VStreamToOfflineStreamWrapper
	::Write(const void* in_pSource, ByteCount in_nByteCount)
{
	if( m_bConnected )
	{
		m_pStream->Write(in_pSource, in_nByteCount);
	}
	else
	{
		V3D_THROW(VIOException, "Attempted to write to disconnected stream");
	}
}

IVStream::ByteCount VStreamToOfflineStreamWrapper
	::Read(void* out_pDest, ByteCount in_pBytesToRead)
{
	if( m_bConnected )
	{
		return m_pStream->Read(out_pDest, in_pBytesToRead);
	}
	else
	{
		V3D_THROW(VIOException, "Attempted to read from disconnected stream");
	}
}

void VStreamToOfflineStreamWrapper
	::SetPos(Anchor in_Anchor, ByteCount in_nDistance)
{
	if( m_bConnected )
	{
		m_pStream->SetPos(in_Anchor, in_nDistance);
	}
	else
	{
		V3D_THROW(VIOException, 
			"Attempted to change pos of disconnected stream");
	}
}

IVStream::StreamPos VStreamToOfflineStreamWrapper
	::GetPos() const
{
	return m_pStream->GetPos();
}

IVStream::LegalOpsPtr VStreamToOfflineStreamWrapper
	::GetLegalOps() const
{
	return m_pStream->GetLegalOps();
}

void VStreamToOfflineStreamWrapper
	::Disconnect()
{
	m_bConnected = false;
}

void VStreamToOfflineStreamWrapper
	::Connect()
{
	m_bConnected = true;
}

vbool VStreamToOfflineStreamWrapper
	::IsConnected() const
{
	return m_bConnected;
}

//-----------------------------------------------------------------------------
} // namspace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

