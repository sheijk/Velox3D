#ifndef VArchiveFileHeader_h
#define VArchiveFileHeader_h

#include <Core/vtypes.h>

struct VArchiveFileHeader
{
	// constructor, init default values
	VArchiveFileHeader();

	// has to be "v3da"
	char cAnswerback[4];

	// major and minor version
	vuint16 nMajorVersion;
	vuint16 nMinorVersion;

	// size of the header
	vuint16 nHeaderSize;

	// position of the file list
	vuint64 nFileListPos;

	// position of the directory structure
	vuint64 nDirStructPos;
};

inline VArchiveFileHeader::VArchiveFileHeader():
	nMajorVersion(0),
	nMinorVersion(0),
	nHeaderSize(sizeof(VArchiveFileHeader)),
	nFileListPos(0),
	nDirStructPos(0)
{
	cAnswerback[0] = 'v';
	cAnswerback[1] = '3';
	cAnswerback[2] = 'd';
	cAnswerback[3] = 'a';	
};

#endif