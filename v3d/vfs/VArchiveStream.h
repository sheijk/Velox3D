// VArchiveStream.h: Schnittstelle für die Klasse VArchiveStream.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARCHIVESTREAM_H__A550F81D_62B6_48AF_BCA4_C937C196F63E__INCLUDED_)
#define AFX_VARCHIVESTREAM_H__A550F81D_62B6_48AF_BCA4_C937C196F63E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Vfs\VMemoryStream.h>
#include <Vfs\IVFileStream.h>
#include <Vfs\VArchiveEntryRelease.h>
/*!
	stream class for internal use by VArchive
*/
class VArchiveStream : 
	public IVFileStream
{
private:
	VArchiveEntryRelease* m_pReleaser;
	VMemoryStream m_Mem;

	//! no standard constructor available
	VArchiveStream();

public:
	VArchiveStream(VArchiveEntryRelease* in_pReleaser);
	virtual ~VArchiveStream();

	//! read data from buffer
    virtual VRESULT Read(void* pDest, vlong const nBytesToRead);

	//! write data to buffer
    virtual VRESULT Write(const void* pSource, vulong const nBytesToWrite);

	//! set current read/write position
    virtual void SetPos(EAnchor nFromWhere, StreamPos nDiff);

	//! get read/write pos
	virtual StreamPos GetPos();

	//! close the connected data source
	void Close();
};

#endif // !defined(AFX_VARCHIVESTREAM_H__A550F81D_62B6_48AF_BCA4_C937C196F63E__INCLUDED_)
