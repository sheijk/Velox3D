#ifndef VArchiveEntryInfo_h
#define VArchiveEntryInfo_h

#include <Core/vtypes.h>
#include <Vfs/VOpenFlags.h>

struct VArchiveEntryInfo
{
	typedef vint64 Pos;

/*	enum EFormat
	{
		fRaw, 
		fEncrypted, 
		fCompressed
	};*/

	Pos m_nStart;
	Pos m_nSize;
//	v3d_vfs::VEResourceOpenFlags m_nAccessRights;
//	vbyte m_nFormat;
};

#endif