/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

template<typename ParentStream>
VStreamGuardTempl<ParentStream>
	::VStreamGuardTempl(ParentStream* in_pStreamToGuard)
{
	m_pGuardedStream = in_pStreamToGuard;
}

template<typename ParentStream>
VStreamGuardTempl<ParentStream>
	::~VStreamGuardTempl()
{
	delete m_pGuardedStream;
	m_pGuardedStream = 0;
}

template<typename ParentStream>
ParentStream& VStreamGuardTempl<ParentStream>
	::GetGuardedStream()
{
	return *m_pGuardedStream;
}

template<typename ParentStream>
const ParentStream& VStreamGuardTempl<ParentStream>
	::GetGuardedStream() const
{
	return *m_pGuardedStream;
}

template<typename ParentStream>
void VStreamGuardTempl<ParentStream>
	::Write(const void* in_pSource, ByteCount in_nByteCount)
{
	if( GetLegalOps()->AllowWrite() )
	{
		m_pGuardedStream->Write(in_pSource, in_nByteCount);
	}
	else
	{
		V3D_THROW(VIllegalOperationException, "tried to write to stream "
			"without write permission");
	}
}

template<typename ParentStream>
typename ParentStream::ByteCount VStreamGuardTempl<ParentStream>
	::Read(void* out_pDest, ByteCount in_pBytesToRead)
{
	if( GetLegalOps()->AllowRead() )
	{
		return m_pGuardedStream->Read(out_pDest, in_pBytesToRead);
	}
	else
	{
		V3D_THROW(VIllegalOperationException, "tried to read from "
			"stream without read permission");
	}
}

template<typename ParentStream>
void VStreamGuardTempl<ParentStream>
	::SetPos(Anchor in_Anchor, ByteCount in_nDistance)
{
	if( GetLegalOps()->AllowPositioning() )
	{
		m_pGuardedStream->SetPos(in_Anchor, in_nDistance);
	}
	else
	{
		V3D_THROW(VIllegalOperationException, "tried to set stream pos "
			"of stream without positioning permission");
	}
}

template<typename ParentStream>
typename ParentStream::StreamPos VStreamGuardTempl<ParentStream>
	::GetPos() const
{
	if( GetLegalOps()->AllowGetPosition() )
	{
		return m_pGuardedStream->GetPos();
	}
	else
	{
		V3D_THROW(VIllegalOperationException, "tried to get pos of "
			"of stream without get pos permission");
	}
}

template<typename ParentStream>
typename ParentStream::LegalOpsPtr VStreamGuardTempl<ParentStream>
	::GetLegalOps() const
{
	return m_pGuardedStream->GetLegalOps();
}

