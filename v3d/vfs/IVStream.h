#ifndef IVSTREAM_H
#define IVSTREAM_H

#include <Core/vtypes.h>

//! interface for streams and buffers
class IVStream 
{
public:    
	//! position in a stream
	typedef vuint64 StreamPos;

	//! destructor
	virtual ~IVStream();

	//! read data from buffer
    virtual VRESULT Read(void* pDest, vlong const nBytesToRead) = 0;

	//! write data to buffer
    virtual VRESULT Write(const void* pSource, vulong const nBytesToWrite) = 0;

	//! anchor for repositioning
	enum EAnchor { begin, end, current };

	//! set current read/write position
    virtual void SetPos(EAnchor nFromWhere, StreamPos nDiff) = 0;

	//! get read/write pos
	virtual StreamPos GetPos() = 0;
};

#endif //VISTREAM_H

// Start of documentation

/*! \file: <Vfs/IVStream.h>
	\brief: Interface for all data streams/buffers
*/

/*! \class IVStream
	Use this interface for all data buffers that can be written to and read from
*/

/*! \fn	virtual IVStream::~IVStream();
	Virtual destructor. Assures the right destructor will be called when deriving classes
*/

/*! \fn	virtual VRESULT IVStream::Read(void* pDest, vlong const nBytesToRead) = 0
	\param pDest The address where read data shall be copied to
	\param nBytesToRead Number of bytes to read
	\return V3D_OK if function succeeded

	Use this function to read data from the buffer
*/

/*! \fn virtual VRESULT IVStream::Write(void* const pSource, vulong const nBytesToWrite) = 0
	\param pSource Address from where memory shall be copied
	\param nBytesToWrite Number of bytes to write
	\return V3D_OK if everything went fine

	Use this function to write to the buffer
*/

/*! \fn virtual void IVStream::SetPos(EAnchor nFromWhere, vlong nDiff) = 0
	\param nFromWhere position the movement shall be relative to
	\param nDiff number of bytes to move

	Move the read/write pointer of the buffer. 
	nFromWhere = begin -> from beginning of buffer
	nFromWhere = end -> from end of buffer
	nFromWhere = current -> from current position
*/

