#include <vfs/VMemoryStream.h>

//the constructor
VMemoryStream::VMemoryStream():
	m_pBuffer(0),
	m_nSizeofBuffer(0),
	m_pMemStreamFacade(new VMemStreamFacade(m_pBuffer, 0))
{
}

// the destructor
VMemoryStream::~VMemoryStream()
{
	delete m_pMemStreamFacade;
	delete m_pBuffer;
	m_nSizeofBuffer = 0;
}

//the write fkt.
VRESULT VMemoryStream::Write(const void* in_pSource,const vulong in_nBytesToWrite)
{
	// if data does not fit in buffer, enlarge it
	if( m_pMemStreamFacade->GetPos() + in_nBytesToWrite > m_nSizeofBuffer )
	{
		// resize buffer
		ReSize(m_pMemStreamFacade->GetPos() + in_nBytesToWrite);
	}

	// copy data
	return m_pMemStreamFacade->Write(in_pSource, in_nBytesToWrite);
}

VRESULT VMemoryStream::Read(void* pDest, const vlong nBytesToRead)
{
	return m_pMemStreamFacade->Read(pDest, nBytesToRead);
}

void VMemoryStream::SetPos(EAnchor nFromWhere, vuint64 nDiff)
{
	m_pMemStreamFacade->SetPos(nFromWhere,nDiff);
}

vuint64 VMemoryStream::GetPos()
{
	return m_pMemStreamFacade->GetPos();
}

void VMemoryStream::ReSize(const vint in_nNewBufferSize)
{
	// save stream pos
	IVStream::StreamPos nStreamPos = m_pMemStreamFacade->GetPos();

	// create new buffer
	char* pNewBuffer = new char[in_nNewBufferSize];

	// copy data from old buffer to new one
	memcpy(pNewBuffer, m_pBuffer, m_nSizeofBuffer);

	// delete old mem fascade an buffer
	delete m_pMemStreamFacade;
	delete[] m_pBuffer;

	// save new buffer size and new buffer
	m_nSizeofBuffer = in_nNewBufferSize;
	m_pBuffer = pNewBuffer;

	// create new mem fascade that uses the new buffer
	m_pMemStreamFacade = new VMemStreamFacade(m_pBuffer, m_nSizeofBuffer);

	// restore old stream pos
	m_pMemStreamFacade->SetPos(IVStream::begin, nStreamPos);
}

