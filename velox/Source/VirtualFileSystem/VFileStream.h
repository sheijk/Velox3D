#ifndef V3D_VFILESTREAM_H
#define V3D_VFILESTREAM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/VFS/IVOfflineStream.h>
#include <v3d/VFS/VFlags.h>

#include "VLegalOperations.h"

#include <string>
#include <windows.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * stream class for reading/writing files
 */
class VFileStream :public IVOfflineStream
{
private:
	VFileStream();	

	HANDLE m_hFile;
	std::string m_strFileName;
	DWORD m_nAccessMode;
	DWORD m_nCreationMode;
	LONG m_nFilePos;
	vbool m_bConnected;
	VPointer<VLegalOperations>::AutoPtr m_pLegalOps;

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
	virtual void Write(void* in_pSource, ByteCount in_nByteCount);

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
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // !defined(AFX_V3D_VFILESTREAM_H__B5F8ED40_744A_11D6_9E97_0030840D38C5__INCLUDED_)
