#ifndef VFILESTREAM_H
#define VFILESTREAM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Vfs/IVFileStream.h>
#include <Vfs/VOpenFlags.h>

#include <string>
#include <windows.h>

/*!
	stream class for reading/writing files
*/
class VFileStream :public IVFileStream
{
private:
	VFileStream();	

	HANDLE hFile;
public:
	//! modes for creation:
	enum 
	{
		createnew = 1, 
		createalways,
		openexisting,
		openalways,
		truncate
	};

	//! opens a file
	VFileStream( std::string strFileName, vuint nMode, vuint nCreation );

	//! destructor, automatically closes opened file
	virtual ~VFileStream();

	//! closes the file
	void Close();

	//! read data, see IVStream::Read
	VRESULT Read(void* pDest, vlong const nBytesToRead);

	//! write data, see IVStream::Write
	VRESULT Write(const void* pSource, vulong const nBytesToWrite);

	//! set read/write pos, see IVStream::SetPos
	void SetPos(EAnchor nFromWhere, StreamPos nDiff);

	//! get read/write pos
	StreamPos GetPos();
};

#endif // !defined(AFX_VFILESTREAM_H__B5F8ED40_744A_11D6_9E97_0030840D38C5__INCLUDED_)
