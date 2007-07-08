/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VFILESTREAM_H
#define V3D_VFILESTREAM_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/SmartPtr/VGuards.h>
#include <V3d/VFS/IVBufferStream.h>
#include <V3d/VFS/VFlags.h>
#include "VLegalOperations.h"

#include <string>

#ifdef V3D_WIN32
#include <windows.h>
#endif
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * stream class for reading/writing files
 */
class VFileStream : public IVBufferStream
{
private:
	VFileStream();	
//todo: hack
#ifdef V3D_WIN32
	HANDLE m_hFile;
	DWORD m_nAccessMode;
	DWORD m_nCreationMode;
	LONG m_nFilePos;
#else
	int m_hFile;
	int m_nAccessMode;
	int m_nCreationMode;
	int m_nFilePos;
#endif

	std::string m_strFileName;
	vbool m_bConnected;
	VSharedPtr<VLegalOperations> m_pLegalOps;

public:
	//! opens a file
	VFileStream(
		VStringParam in_strFileName, 
		VAccessModeFlags in_nMode, 
		VCreationFlags in_nCreation);

	//! destructor, automatically closes opened file
	virtual ~VFileStream();

	//! closes the file
	void Close();

	// from IVStream:

	/** write data to stream */
	virtual void Write(const void* in_pSource, ByteCount in_nByteCount);

	/** read data from stream */
	virtual ByteCount Read(void* out_pDest, ByteCount in_pBytesToRead);

	/** reset r/w position */
	virtual void SetPos(Anchor in_Anchor, ByteCount in_nDistance);

	/** get r/w position */
	virtual StreamPos GetPos() const;

	/** get a list of legal operations */
	virtual LegalOpsPtr GetLegalOps() const;

	// from IVOfflineStream:

	/** disconnect the stream */
	virtual void Disconnect();

	/** (re-)connect the stream */
	virtual void Connect();

	/** true -> read, write, set/get pos possible */
	virtual vbool IsConnected() const;

	/** return the size of the buffer in bytes */
	virtual ByteCount GetSize();

	/** change the size of the buffer */
	virtual void SetSize(ByteCount in_nNewSize);
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // !defined(AFX_V3D_VFILESTREAM_H__B5F8ED40_744A_11D6_9E97_0030840D38C5__INCLUDED_)

