#include "VArchive.h"

#include <iostream>

#include <Vfs/VArchiveFileHeader.h>
#include <Vfs/VFileStream.h>
#include <Vfs/VFileTools.h>
#include <Vfs/VArchiveStream.h>
#include <Error/VAssert.h>

using std::string;
using std::cout;
using std::endl;


VArchive::VOpenedEntryInfo::VOpenedEntryInfo() 
//	bOpened(false)
//	nAccessMode(0)
{
}

void ReadStringFromStream(std::string& out_strString, IVStream* in_pStream)
{
	char* pChars;
	vuint64 ui64Len;

	// read stream length
	in_pStream->Read(&ui64Len, sizeof(ui64Len));

	if( ui64Len > 0 )
	{
		// create buffer
		pChars = new char[(vint)ui64Len+1];

		// load data
		in_pStream->Read(pChars, (vulong)ui64Len);

		// set ending ascii 0
		pChars[ui64Len] = '\0';

		// copy to string
		out_strString = pChars;

		delete[] pChars;
	}
}

void WriteStringToStream(const std::string in_strString, IVStream* out_pStream)
{
	vuint64 ui64Len;

	// write length
	ui64Len = in_strString.length();
	out_pStream->Write(&ui64Len, sizeof(ui64Len));

	// write chars
	out_pStream->Write(in_strString.c_str(), (vulong)ui64Len);
}



VArchive::VArchive():
	m_bFileAssigned(false)
{

}

VArchive::~VArchive()
{
	if( m_bFileAssigned )
	{
		Close();
	}
}

/*!
	\param in_strEntryName the name of the file to be opened/created
	\param in_eOpenMode omCreateNew to create a new file, omOpenExisting to open an existing file
	\return true if succeeded, false if function failed

	Assign the archive to a file. File must not be changed while lifetime of object.
*/
vbool VArchive::Assign(string in_strEntryName, VArchive::OpenMode in_eOpenMode)
{
	bool ret = false;

	// close current archive
	Close();

	// if file already exists
	if( IsValidFile(in_strEntryName) )
	{
		// if new file shall be created
		if( in_eOpenMode == omCreateNew )
		{
			// delete existing and create new

			ret = CreateArchiveFile(in_strEntryName);
		}
		// if file shall be opened
		if( in_eOpenMode == omOpenExisting )
		{
			// open it
			ret = OpenArchiveFile(in_strEntryName);
		}
	}
	// if file does not exist
	else
	{
		// if new one shall be created
		if( in_eOpenMode == omCreateNew )
		{
			// create it
			ret = CreateArchiveFile(in_strEntryName);
		}
		// if existing shall be opened
		else if( in_eOpenMode = omOpenExisting )
		{
			// fail
			ret = false;
		}
	}

	if( true == ret )
	{
		m_strFileName = in_strEntryName;
		m_bFileAssigned = true;
	}

	return ret;
}

/*!
	\param in_strEntryName specifies name and path of new entry
	\param in_nAccessRights the access rights for the file
	\return true - succeeded, false - failed

	Creates a new entry and adds it to the directory structure
*/
vbool VArchive::CreateEntry(const string in_strName)//, const v3d_vfs::VEResourceOpenFlags in_nAccessRights)
{
	EntryMap::iterator it = m_Entries.find(in_strName);

	// if entry already exists
	if( it != m_Entries.end() )
	{
		// indicate failure
		return false;
	}
	// entry does not exist
	else
	{
		// create entry information
		VArchiveEntryInfo EntryInfo;

//		EntryInfo.m_nAccessRights = in_nAccessRights;
		EntryInfo.m_nStart = 0;
		EntryInfo.m_nSize = 0;
//		EntryInfo.m_nFormat = VArchiveEntryInfo::fRaw;

		// add it to list
		m_Entries.insert( EntryMap::value_type(in_strName, EntryInfo) );

		return true;
	}
}

/*!
	\param in_nId the id of the entry to be deleted

	Removes an entry from the archive. all data saved to it will be lost. Entry will also be
	removed from directory structure
*/
void VArchive::RemoveEntry(const string in_strName)
{
	// if entry was opened, close it

	// remove entry from list
	m_Entries.erase(in_strName);
}

void VArchive::dump_info()
{
	EntryIterator it;

	for( it = m_Entries.begin(); it != m_Entries.end(); ++it )
	{
		cout << it->first
//			 << ", rights: " 
//			 << it->second.m_nAccessRights 
			 << endl;
	}	

	cout << "number of Entries in archive: " << m_Entries.size() << endl;
}

/*!
	\param in_strFileName The path and file name of the file to be created
	\return true if succeeded, false if failed

	Creates a new archive file. Means that all data is cleared, file will be written
	when Close() is called
*/
vbool VArchive::CreateArchiveFile(string in_strFileName)
{
	// create new file
	VFileStream File(in_strFileName, v3d_vfs::write_access, VFileStream::createalways);
	VArchiveFileHeader Header;
	vuint64 ui64EntryCount;

	// close opened file
	Close();

	// write header
	Header.nFileListPos = sizeof(Header);
	File.Write(&Header, sizeof(Header));

	// write entry list
	ui64EntryCount = 0;
	File.Write(&ui64EntryCount, sizeof(ui64EntryCount));

	return true;
}

/*
	\param in_strArchiveFile Path and file to be opened
	\return true if succeeded, false if failed

	Opens an existing archive and reads it's data from it.
*/
vbool VArchive::OpenArchiveFile(string in_strArchiveFile)
{	
	VFileStream File(in_strArchiveFile, v3d_vfs::read_access, VFileStream::openexisting);
	VArchiveFileHeader Header;
	vuint64 ui64EntryCount = 0;
	vuint64 ui64CurrEntry;
	VArchiveEntryInfo EntryInfo;
	string strEntryName;

	// if file does not exist, fail

	// read header
	File.Read( &Header, sizeof(Header) );

	// check major version
	if( Header.nMajorVersion != 0 ) return false;

	// read entry list
	File.SetPos(IVStream::begin, Header.nFileListPos);

	// read number of entries
	File.Read(&ui64EntryCount, sizeof(ui64EntryCount));
	for(ui64CurrEntry = 0; ui64CurrEntry < ui64EntryCount; ++ui64CurrEntry)
	{
		// read name
		ReadStringFromStream(strEntryName, &File);

		// read info
		File.Read(&EntryInfo, sizeof(EntryInfo));

		// add to list
		m_Entries.insert( EntryMap::value_type(strEntryName, EntryInfo) );
	}

	return true;
}

/*!
	\return true if archive could be closed, false if errors occured while saving data

	Closes the archive and writes all data to disk. If not all data could be saved the 
	function returns false and keeps all data in memory.
*/
vbool VArchive::Close()
{
	if( m_bFileAssigned )
	{
		VArchiveFileHeader Header;
		vuint64 ui64EntryCount, ui64FileListPos;
		EntryIterator it;

		// close all opened files
		while( ! m_OpenedEntries.empty() )
		{
			m_OpenedEntries.begin()->first->Close();
		}

		// goto end of file
		UpdateChunkInfo();

		// open file
		VFileStream File(m_strFileName, v3d_vfs::write_access, VFileStream::openexisting);


		if( ! m_FreeChunks.empty() )
		{
			ChunkSet::iterator chunk_it = m_FreeChunks.end();
			--chunk_it;

			File.SetPos(IVStream::begin, chunk_it->nPos);
		}
		else
		{
			File.SetPos(IVStream::begin, sizeof(Header));
		}

		// save number of entries
		ui64FileListPos = File.GetPos();

		File.SetPos(IVStream::begin, 0);
		File.Read(&Header, sizeof(Header));

		Header.nFileListPos = ui64FileListPos;

		File.SetPos(IVStream::begin, 0);
		File.Write(&Header, sizeof(Header));

		File.SetPos(IVStream::begin, ui64FileListPos);

		// save number of entries
		ui64EntryCount = m_Entries.size();
		File.Write(&ui64EntryCount, sizeof(ui64EntryCount));

		// save entry list
		for( it = m_Entries.begin(); it != m_Entries.end(); ++it )
		{
			// write name
			WriteStringToStream(it->first, &File);

			// write data
			File.Write(&(it->second), sizeof(it->second));
		}

		// fill end of files with #'s
		vuint64 nl, np = File.GetPos();
		int i;
		char c = '#';
		File.SetPos(IVStream::end, 0);
		nl = File.GetPos() - np;
		File.SetPos(IVStream::begin, np);
		for(i = 0; i < nl; ++i)
			File.Write(&c, 1);

		//-----------
		// clear data

		// close streams/forget them
		m_OpenedEntries.erase(m_OpenedEntries.begin(), m_OpenedEntries.end());

		// clear entry list
		m_Entries.erase(m_Entries.begin(), m_Entries.end());

		m_bFileAssigned = false;
		return true;
	}
	else return false;
}

/*!
	\param in_strEntryName name of entry to be opened
	\param in_nAccessMode access mode. write_access, read_access
	\return pointer to a stream which can be used to access the entry

	Opens an entry so you can read from and write to it. Returns a stream that must be
	manually deleted. To close the entry, call close. The archive owns the stream, so 
	the stream must not be deleted manually
*/
IVFileStream* VArchive::Open(string in_strEntryName, vuint in_nAccessMode)
{
	EntryMap::iterator entry_it = m_Entries.find(in_strEntryName);

	// if entry exists
	if( entry_it != m_Entries.end() )
	{
		OpenEntryMap::iterator openentry_it = FindOpenedEntry(in_strEntryName);

		// if entry is already opened
		if( openentry_it != m_OpenedEntries.end() )
		{
			return 0;
		}
		// if entry is not opened yet
		else
		{
			// create archive stream
			VArchiveStream* pArchiveStream = new VArchiveStream(this);

			// load data
			LoadEntryToStream(pArchiveStream, in_strEntryName);

			// mark space used by entry as free
			entry_it->second.m_nStart = 0;
			entry_it->second.m_nSize = 0;

			// add it to list of opened entries
			VOpenedEntryInfo Info;
			Info.strName = in_strEntryName;			

			m_OpenedEntries.insert( OpenEntryMap::value_type(pArchiveStream, Info) );

			// return the stream
			return pArchiveStream;
		}
	}
	// if entry does not exist
	else
	{
		return 0;
	}
}

/*!
	\param in_strEntryName name of entry to be released
	\param in_pStream pointer to the stream which has been closed

	Indicates that an archive stream has been closed
*/
void VArchive::ReleaseEntry(VArchiveStream* in_pStream)
{
	// only proceed if stream is really opened
	if( m_OpenedEntries.count(in_pStream) )
	{
		// update chunk info
		UpdateChunkInfo();

		// write entry to archive file
		WriteEntryToFile(in_pStream);

		// remove it from list of opened entries
		m_OpenedEntries.erase(in_pStream);
	}
}

/*!
	\param in_strEntryName name of the opened entry to be searched
	\return iterator that points to the entry, m_OpenedEntries.end() indicates the end

	returns an iterator for the opened entry. if entry is not opened m_OpenedEntries.end()
	will be returned
*/
VArchive::OpenEntryMap::iterator VArchive::FindOpenedEntry(const string in_strEntryName)
{
	OpenEntryMap::iterator it;

	// for each entry
	for( it = m_OpenedEntries.begin(); it != m_OpenedEntries.end(); ++it )
	{
		// check if entry is the searched one
		if( it->second.strName == in_strEntryName )
		{
			return it;
		}
	}

	return m_OpenedEntries.end();
}

/*vbool VArchive::WriteOpenedEntriesToFile(IVStream *out_pStream)
{
	V3D_ASSERT(out_pStream);

	typedef std::set<SChunk> ChunkList;

	ChunkList freeChunks, usedChunks;
	EntryMap::iterator entry_it;
	OpenEntryMap::iterator openentry_it;
	vint64 nDataEndPos = out_pStream->GetPos();

	// if there are no entries nothing need to be written
	if( m_Entries.size() == 0 ) return true;

	// generate chunk list of used chunks
	for( entry_it = m_Entries.begin(); entry_it != m_Entries.end(); ++entry_it )
	{
		string str = entry_it->first;
		VArchiveEntryInfo info = entry_it->second;

		// if entry is not opened
		if( FindOpenedEntry(entry_it->first) == m_OpenedEntries.end() )
		{
			// add a chunk to list
			usedChunks.insert( SChunk(entry_it->second.m_nStart, entry_it->second.m_nSize) );
		}
	}

	// generate list of free chunks
	if( usedChunks.size() > 0 )
	{
		ChunkList::iterator chunk_it = usedChunks.begin();
		ChunkList::iterator lastchunk_it;
		vint64 lastend;
		SChunk chunk = *chunk_it;
		SChunk lastchunk;

		// if first used chunk doesn't start at chunkpos
		if( chunk_it->nPos > out_pStream->GetPos() )
		{
			// add a free chunk there
			freeChunks.insert( SChunk(out_pStream->GetPos(), chunk_it->nPos - out_pStream->GetPos()) );
		}

		++chunk_it;
		lastchunk_it = chunk_it;
		for( ; chunk_it != usedChunks.end(); lastchunk_it = chunk_it, ++chunk_it )
		{
			chunk = *chunk_it;
			lastchunk = *lastchunk_it;

			// if there's place between current chunk and last chunk
			lastend = lastchunk_it->nPos + lastchunk_it->nLen;
			if( lastend < chunk_it->nPos )
			{
				// add a free chunk
				freeChunks.insert( SChunk(lastend, chunk_it->nPos - lastend) );
			}
		} // for each used chunk
	} // if more than one used chunk

	// add 'unlimited' sized free chunk at the end
	freeChunks.insert( SChunk(nDataEndPos, 0xFFFFFFFFFFFFFFFF) );

	if( usedChunks.size() > 0 )
	{
		nDataEndPos = (usedChunks.end()--)->nPos + (usedChunks.end()--)->nLen;
	}
	else
	{
		nDataEndPos = out_pStream->GetPos();
	}

	// save opened entries

	// for each opened entry that has been changed
	for( openentry_it = m_OpenedEntries.begin(); openentry_it != m_OpenedEntries.end(); ++openentry_it )
	{		
		vint64 nBytesWritten = 0;
		VArchiveStream* pCurrStream = openentry_it->first;
		vint64 nBytesToWrite;

		// get size of stream
		pCurrStream->SetPos(IVStream::end, 0);
		nBytesToWrite = pCurrStream->GetPos();

		pCurrStream->SetPos(IVStream::begin, 0);

		// update entry info
		entry_it = m_Entries.find( openentry_it->second.strName );
		entry_it->second.m_nStart = freeChunks.begin()->nPos;
		entry_it->second.m_nSize = nBytesToWrite;
		entry_it->second.m_nFormat = VArchiveEntryInfo::fRaw;
		
		// until whole entry is written
		while( nBytesWritten < nBytesToWrite )
		{
			vint64 nPos;
			vint64 i64NextChunkPos;
			vint64 i64ToWrite;

			// get first chunk
			nPos = freeChunks.begin()->nPos;

			// if remaining data fits in chunk
			if( nBytesToWrite - nBytesWritten <= freeChunks.begin()->nLen - sizeof(vint64)*2 )
			{
				i64NextChunkPos = 0;
				i64ToWrite = nBytesToWrite - nBytesWritten - sizeof(vint64)*2;

				// decrease size of chunk
				freeChunks.begin()->nPos += i64ToWrite;
				freeChunks.begin()->nLen -= i64ToWrite;
			}
			// if remaining data does not fit in chunk
			else
			{
				// set chunk size
				i64ToWrite = freeChunks.begin()->nLen - sizeof(vint64)*2;

				// remove first free chunk
				freeChunks.erase(freeChunks.begin());

				// store pos of next chunk
				i64NextChunkPos =  freeChunks.begin()->nPos;
			}

			// write data
			out_pStream->SetPos(IVStream::begin, nPos);
			out_pStream->Write(&i64NextChunkPos, sizeof(i64NextChunkPos));
			out_pStream->Write(&i64ToWrite, sizeof(i64ToWrite));

			// save chunk data
			char* chr = new char[i64ToWrite];
			pCurrStream->Read(chr, i64ToWrite);
			out_pStream->Write(chr, i64ToWrite);
			nBytesWritten += i64ToWrite;
			delete[] chr;
		}
	}

	// if file is too defragmented or there's too much space wasted
		// defragment archive

	return true;
}*/
/*
			// store current chunk
			nPos = freeChunks.begin()->nPos;
			i64ChunkSize = freeChunks.begin()->nLen;

			i64ChunkSize -= sizeof(i64ChunkSize) - sizeof(i64NextChunkPos);

			// remove it from list
			freeChunks.erase(freeChunks.begin());

			// save chunk info to stream
			i64ToWrite = max(i64ChunkSize, nBytesToWrite - nBytesWritten);

			if( i64ToWrite <= 0 ) nNexChunkPos = 0;

			// if not the whole chunk was filled, add a new free chunk
			if( i64ToWrite < i64ChunkSize )
			{
				freeChunks.insert( SChunk(nPos+i64ToWrite, i64ChunkSize - i64ToWrite) );
			}

			out_pStream->SetPos(IVStream::begin, nPos);
			out_pStream->Write(&i64NextChunkPos, sizeof(i64NextChunkPos));
			out_pStream->Write(&i64ToWrite, sizeof(i64ToWrite));

			// save chunk data
			char* chr = new char[i64ChunkSize];
			openentry_it->first->Read(chr, i64ChunkSize);
			out_pStream->Write(chr, i64ChunkSize);
			nBytesWritten += i64ChunkSize;
			delete[] chr;
*/

/*
	\param out_pStream stream to load entry into
	\param in_strEntryName name of entry to be loaded
*/
void VArchive::LoadEntryToStream(IVStream *out_pStream, string in_strEntryName)
{
	// get entry desc
	vint64 nPos, nLen, nTotalLen;
	EntryMap::iterator entry_it = m_Entries.find(in_strEntryName);
	VFileStream File(m_strFileName, v3d_vfs::read_access, VFileStream::openexisting);
	
	nPos = entry_it->second.m_nStart;
	nTotalLen = entry_it->second.m_nSize;

	// load each chunk
	while( nPos > 0 )
	{
		// go to chunk
		File.SetPos(IVStream::begin, nPos);

		// load pos of next chunk
		File.Read(&nPos, sizeof(nPos));

		// load length of this chunk
		File.Read(&nLen, sizeof(nLen));

		// load chunk
		char* chr = new char[(vint)nLen];
		File.Read(chr, (vlong)nLen);
		out_pStream->Write(chr, (vulong)nLen);
		delete[] chr;
	}
}

void VArchive::UpdateChunkInfo()
{
	VFileStream File(m_strFileName, v3d_vfs::read_access, VFileStream::openexisting);
	ChunkSet usedChunks;
	EntryMap::iterator entry_it = m_Entries.begin();
	vuint64 nPos, nNextPos, nLen;

	// generate list of used chunks

	// for each entry, add it's chunks
	for( ; entry_it != m_Entries.end(); ++entry_it )
	{
		nPos = entry_it->second.m_nStart;

		while( nPos > 0 )
		{
			// read pos and length of next chunk
			File.SetPos(IVStream::begin, nPos);

			// pos of next chunk
			File.Read(&nNextPos, sizeof(nNextPos));
			File.Read(&nLen, sizeof(nLen));

			nLen += sizeof(vuint64)*2;

			// add chunk to used chunk list
			usedChunks.insert( SChunk(nPos, nLen) );

			nPos = nNextPos;
		}		
	}

	// add header as used chunk
	usedChunks.insert( SChunk(0, sizeof(VArchiveFileHeader)) );

	// generate list of free chunks
	m_FreeChunks.erase(m_FreeChunks.begin(), m_FreeChunks.end());

	vuint64 nLastChunkEndPos = sizeof(VArchiveFileHeader);

	// if there are any used chunks
	if( ! usedChunks.empty() )
	{	
		vint64 nLastChunkEnd, nNextChunkStart;

		ChunkSet::iterator	lastchunk_it = usedChunks.begin(),
							chunk_it = lastchunk_it;

		// for all used chunks
		for( ++chunk_it; chunk_it != usedChunks.end(); ++chunk_it )
		{
			vuint64 np, nl;
			np = lastchunk_it->nPos; nl = lastchunk_it->nLen;

			nLastChunkEnd = lastchunk_it->nPos + lastchunk_it->nLen;
			nNextChunkStart = chunk_it->nPos;

			// if there is space between two used chunks
			if( nLastChunkEnd + sizeof(vint64)*2 < nNextChunkStart )
			{
				// add a free chunk there
				m_FreeChunks.insert( SChunk(nLastChunkEnd, nNextChunkStart - nLastChunkEnd) );
			}

			// update last pos
			nLastChunkEndPos = chunk_it->nPos + chunk_it->nLen;

			lastchunk_it = chunk_it;
		}

	}

	// add ending "unlimited sized" free chunk
	m_FreeChunks.insert( SChunk(nLastChunkEndPos, 0 ) );

	ChunkSet::iterator it;

	cout << endl << "used:  ";

	for( it = usedChunks.begin(); it != usedChunks.end(); ++it )
	{
		cout << it->nPos << "(" << it->nLen << "),  ";
	}

	cout << endl << "free: ";

	for( it = m_FreeChunks.begin(); it != m_FreeChunks.end(); ++it )
	{
		cout << it->nPos << "(" << it->nLen << "),  ";
	}

	cout << endl << "data end: " << nLastChunkEndPos;
}

/*
	\param in_pStream contains the entry data
	
	writes opened entry to file
*/
void VArchive::WriteEntryToFile(VArchiveStream *in_pStream)
{
	VFileStream File(m_strFileName, v3d_vfs::write_access, VFileStream::openexisting);
	ChunkSet::iterator chunk_it;
	vuint64 nCurrentChunkPos=0, nNextChunkPos=0, nCurrentChunkLen=0, nRemainingBytes=0;

	OpenEntryMap::iterator oe_it = m_OpenedEntries.find(in_pStream);
	EntryMap::iterator entry_it;

	// get number of bytes to write
	in_pStream->SetPos(IVStream::end,0);
	nRemainingBytes = in_pStream->GetPos();

	in_pStream->SetPos(IVStream::begin, 0);

	// if stream is not opened, abort
	if( oe_it == m_OpenedEntries.end() ) return;

	entry_it = m_Entries.find(oe_it->second.strName);

	// if file does not exist, abort
	if( entry_it == m_Entries.end() ) return;

	// update entry info
	vint64 t = m_FreeChunks.begin()->nPos;
	entry_it->second.m_nStart = t;
	entry_it->second.m_nSize = nRemainingBytes;

	while( nRemainingBytes > 0 )
	{
		// get a free chunk
		nCurrentChunkPos = m_FreeChunks.begin()->nPos;
		nCurrentChunkLen = m_FreeChunks.begin()->nLen;

		// if all data fits inside this chunk (size = 0 means unlimited size)
		if( (nRemainingBytes <= nCurrentChunkLen - 2*sizeof(vuint64)) || nCurrentChunkLen == 0 )
		{
			File.SetPos(IVStream::begin, nCurrentChunkPos);

			nNextChunkPos = 0;
			nCurrentChunkLen = nRemainingBytes;// + 2*sizeof(vuint64);

			// write chunk header
			File.Write(&nNextChunkPos, sizeof(nNextChunkPos));
			File.Write(&nCurrentChunkLen, sizeof(nCurrentChunkLen));
			
			// write data
			char* pDat = new char[(vint)nRemainingBytes];
			in_pStream->Read(pDat, (vlong)nRemainingBytes);
			File.Write(pDat, (vulong)nRemainingBytes);
			delete[] pDat;

			// adjust chunk !fix unnötig (?), denn chunk info wird vorm nächsten mal neu generiert
			SChunk Chunk = *m_FreeChunks.begin();

			if( Chunk.nLen != 0 )
			{
				m_FreeChunks.erase(m_FreeChunks.begin());

				Chunk.nPos += nRemainingBytes + 2*sizeof(vuint64);
				Chunk.nLen -= nRemainingBytes + 2*sizeof(vuint64);

				// if chunk would become too small, dump it
				if( Chunk.nLen > 2*sizeof(vuint64) )
				{
					m_FreeChunks.insert(Chunk);
				}
			}

			nRemainingBytes = 0;
		}
		// data does not fit inside chunk completely
		else
		{
			// erase chunk
			m_FreeChunks.erase(m_FreeChunks.begin());

			nNextChunkPos = m_FreeChunks.begin()->nPos;
			nCurrentChunkLen -= 2*sizeof(vuint64);

			// write chunk header
			File.SetPos(IVStream::begin, nCurrentChunkPos);
			File.Write(&nNextChunkPos, sizeof(nNextChunkPos));
			File.Write(&nCurrentChunkLen, sizeof(nCurrentChunkLen));

			// write data
			char* pDat = new char[(vint)nCurrentChunkLen];
			in_pStream->Read(pDat, (vlong)nCurrentChunkLen);
			File.Write(pDat, (vulong)nCurrentChunkLen);
			delete[] pDat;

			nRemainingBytes -= nCurrentChunkLen;
		}
	}
}
