// VArchiveStream.cpp: Implementierung der Klasse VArchiveStream.
//
//////////////////////////////////////////////////////////////////////

#include "VArchiveStream.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

VArchiveStream::VArchiveStream(VArchiveEntryRelease *in_pReleaser) :
	m_Mem(),
	m_pReleaser(in_pReleaser)
{
}

VArchiveStream::~VArchiveStream()
{
	Close();
}

VRESULT VArchiveStream::Read(void* pDest, vlong const nBytesToRead)
{
	return m_Mem.Read(pDest, nBytesToRead);
}

VRESULT VArchiveStream::Write(const void* pSource, vulong const nBytesToWrite)
{
	return m_Mem.Write(pSource, nBytesToWrite);
}

void VArchiveStream::SetPos(EAnchor nFromWhere, StreamPos nDiff)
{
	m_Mem.SetPos(nFromWhere, nDiff);
}

IVStream::StreamPos VArchiveStream::GetPos()
{
	return m_Mem.GetPos();
}

void VArchiveStream::Close()
{
//	ReSize(0);

	if( m_pReleaser != 0 )
	{
		m_pReleaser->ReleaseEntry(this);
	}

	m_pReleaser = 0;
}
