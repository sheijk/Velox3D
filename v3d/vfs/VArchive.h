#ifndef VArchive_h
#define VArchive_h

#pragma warning(disable:4786)

#include <string>
#include <map>
#include <set>

#include <Core/vtypes.h>
#include <Vfs/VArchiveEntryInfo.h>
#include <Vfs/IVFileStream.h>
#include <Vfs/VArchiveEntryRelease.h>

//! class that loads and writes to v3d archives
class VArchive :public VArchiveEntryRelease
{
private:

	struct VOpenedEntryInfo
	{
		VOpenedEntryInfo();

		std::string strName;
//		vuint nAccessMode;
//		bool bOpened;
	};

	typedef std::map<VArchiveStream*, VOpenedEntryInfo> OpenEntryMap;
	typedef std::map<std::string, VArchiveEntryInfo> EntryMap;

	struct SChunk
	{
		SChunk(): nPos(0), nLen(0) {};
		SChunk(vuint64 pos, vuint64 len): nPos(pos), nLen(len) {};

		bool operator<(const SChunk& other) const
		{
			return nPos < other.nPos;
		}

		vuint64 nPos, nLen;
	};

	typedef std::set<SChunk> ChunkSet;
public:
	//! id of an entry
	typedef unsigned long EntryId;

	//! how a file shall be opened
	enum OpenMode { omCreateNew, omOpenExisting };

	typedef EntryMap::iterator EntryIterator;
	typedef EntryMap::const_iterator ConstEntryIterator;

private:
	void WriteEntryToFile(VArchiveStream* in_pStream);
	void UpdateChunkInfo();
	void LoadEntryToStream(IVStream* out_pStream, std::string in_strEntryName);
//	vbool WriteOpenedEntriesToFile(IVStream* out_pStream);
	vbool CreateArchiveFile(std::string in_strFileName);
	vbool OpenArchiveFile(std::string in_strArchiveFile);
	OpenEntryMap::iterator FindOpenedEntry(const std::string in_strEntryName);
	void ReleaseEntry(VArchiveStream* in_pStream);


	std::string m_strFileName;
	bool m_bFileAssigned;

	EntryMap m_Entries;
	OpenEntryMap m_OpenedEntries;

	ChunkSet m_FreeChunks;
public:
	//! creates a stream to read from/write to an entry. stream must be deleted
	IVFileStream* Open(std::string in_strEntryName, vuint in_nAccessMode);

	//! removes an entry from the archive
	void RemoveEntry(const std::string in_strName);

	//! creates a new entry
	vbool CreateEntry(const std::string in_strName);//, const v3d_vfs::VEResourceOpenFlags in_nAccessRights);

	//! closes the archives
	vbool Close();

	//! assigns an archive file to the archive object
	vbool Assign(std::string in_strEntryName, OpenMode in_eOpenMode);


	//! temp. zum debuggen
	void dump_info();

	VArchive();
	virtual ~VArchive();
};

#endif
