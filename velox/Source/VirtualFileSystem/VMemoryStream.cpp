#include "VMemoryStream.h"
//-----------------------------------------------------------------------------
#include "VLegalOperations.h"
#include <v3d/VFS/VIOException.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

VPointer<IVLegalOperations>::AutoPtr VMemoryStream::s_pLegalOps(
	new VLegalOperations(true, true, true, true) );

//-----------------------------------------------------------------------------

VMemoryStream::VMemoryStream()
{
	m_nRWPos = 0;
}

VMemoryStream::VMemoryStream(ByteCount in_nInitialSize)
{
	m_nRWPos = 0;

	m_Data.resize(in_nInitialSize);
}

VMemoryStream::~VMemoryStream()
{
}

IVStream::ByteCount VMemoryStream::GetSize() const
{
	return (ByteCount)m_Data.size();
}

vchar* VMemoryStream::GetAddressOfByte(ByteCount in_nPos)
{
	return (&m_Data[0]) + in_nPos;
}

void VMemoryStream::Write(void* in_pSource, ByteCount in_nByteCount)
{
	vlong nNewRWPos;
	nNewRWPos = m_nRWPos + in_nByteCount;

	// if data does not fit into buffer resize it
	if( nNewRWPos > GetSize() )
	{
        m_Data.resize(nNewRWPos);		
	}

	// write to buffer
	memcpy(GetAddressOfByte(m_nRWPos), in_pSource, in_nByteCount);
	m_nRWPos = nNewRWPos;
}

IVStream::ByteCount VMemoryStream::Read(void* out_pDest, ByteCount in_pBytesToRead)
{
	vlong nNewRWPos = m_nRWPos + in_pBytesToRead;

	// if read over end of stream throw exception
	if( nNewRWPos > GetSize() )
	{
		in_pBytesToRead -= nNewRWPos - GetSize();
		//V3D_THROW(VIOException, "VMemoryStream: read past end of stream");
	}

	// copy data
	memcpy(out_pDest, GetAddressOfByte(m_nRWPos), in_pBytesToRead);
	m_nRWPos = nNewRWPos;

	return in_pBytesToRead;
}

void VMemoryStream::SetPos(Anchor in_Anchor, ByteCount in_nDistance)
{
	StreamPos nNewPos = 0;

	// calc new pos
	switch(in_Anchor)
	{
	case IVStream::Begin:
		nNewPos = in_nDistance;
		break;
	case IVStream::End:
		nNewPos = GetSize() - in_nDistance;
		break;
	case IVStream::CurrentPos:
		nNewPos = m_nRWPos + in_nDistance;
		break;
	default:
		nNewPos = m_nRWPos;
	}

	// throw error if position is invalid
	if( nNewPos < 0 || nNewPos > GetSize() )
	{
		V3D_THROW(VIOException, "SetPos: invalid position");
	}
	
	// set pos
	m_nRWPos = nNewPos;
}

IVStream::StreamPos VMemoryStream::GetPos() const
{
	return m_nRWPos;
}

IVStream::LegalOpsPtr VMemoryStream::GetLegalOps() const
{
	return s_pLegalOps.Get();
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
