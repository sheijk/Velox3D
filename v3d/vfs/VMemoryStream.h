#ifndef VMEMORYSTREAM_H
#define VMEMORYSTREAM_H

#include <vfs/IVStream.h>
#include <vfs/VMemStreamFacade.h>
#include <memory.h>

class VMemoryStream : IVStream
{
private:
	VMemStreamFacade* m_pMemStreamFacade;

	void* m_pBuffer;

	vulong m_nSizeofBuffer;
protected:
public:
	// constructor
	VMemoryStream();

	//deconstructor
	~VMemoryStream();

	//! position in a stream
	typedef vuint64 StreamPos;

	//! read data from buffer
    VRESULT Read(void* pDest, vlong const nBytesToRead);

	//! write data to buffer
    VRESULT Write(const void* pSource, vulong const nBytesToWrite);

	//! set current read/write position
    void SetPos(EAnchor nFromWhere, StreamPos nDiff);

	//! get read/write pos
	StreamPos GetPos();

	// resize the buffer to the specific size

	void ReSize(const vint nSizeInBytes);
};

#endif