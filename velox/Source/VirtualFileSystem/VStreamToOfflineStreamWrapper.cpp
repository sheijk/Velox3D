#include "VStreamToOfflineStreamWrapper.h"
//-----------------------------------------------------------------------------
#include <v3d/VFS/VIOException.h>

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
	::Write(void* in_pSource, ByteCount in_nByteCount)
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

void VStreamToOfflineStreamWrapper
	::Read(void* out_pDest, ByteCount in_pBytesToRead)
{
	if( m_bConnected )
	{
		m_pStream->Read(out_pDest, in_pBytesToRead);
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
