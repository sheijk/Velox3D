// VFileStream.cpp: Implementierung der Klasse VFileStream.
//
//////////////////////////////////////////////////////////////////////

#include <Vfs/VFileStream.h>
#include <Error/VException.h>

#include <sstream>

using namespace std;
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

/*!
	\param strFileName name of file to be opened
	\param nAccess write_access for writing, read_access for reading
	\param nCreation createion mode. createnew, createalways, openexisting, openalways, truncate

	Creates the stream and opens a file
*/
VFileStream::VFileStream(string strFileName, vuint nAccess, vuint nCreation ):
	hFile( INVALID_HANDLE_VALUE )
{
	DWORD dwDesAccess = 0;
	DWORD dwCreation = 0;

	if( nAccess == 0 ) V3D_THROW( VException, "invalid file open mode" );

	// set acces flags
	if( nAccess & v3d_vfs::read_access ) dwDesAccess |= GENERIC_READ;
	if( nAccess & v3d_vfs::write_access ) dwDesAccess |= GENERIC_WRITE;

	// set creation mode
	switch( nCreation )
	{
	case createnew:
		dwCreation = CREATE_NEW;
		break;
	case createalways:
		dwCreation = CREATE_ALWAYS;
		break;
	case openexisting:
		dwCreation = OPEN_EXISTING;
		break;
	case openalways:
		dwCreation = OPEN_ALWAYS;
		break;
	case truncate:
		dwCreation = TRUNCATE_EXISTING;
		break;
	default:
		ostringstream str;
		str << "invalid file creation mode for file \"";
		str << strFileName;
		str << "\" :";
		str << nCreation << endl;

		V3D_THROW( VException, str.str() )
	}

	// open the file
	hFile = CreateFile( strFileName.c_str(), 
							  dwDesAccess,
							  0, 
							  0, 
							  dwCreation, 
							  FILE_ATTRIBUTE_NORMAL, 
							  0 );

	// if file could not be opened
	if( hFile == INVALID_HANDLE_VALUE )
	{
		// throw error
		V3D_THROW( VException, string("could not open file: \"")+strFileName+string( "\"" ) );
	}	

	SetFilePointer( hFile, 0, 0, FILE_BEGIN );

	DWORD filesize = GetFileSize( hFile, 0 );
}

VFileStream::VFileStream() :
	hFile( INVALID_HANDLE_VALUE )
{
}

/*!
	automatically closes file if opened
*/
VFileStream::~VFileStream()
{
	Close();
}


VRESULT VFileStream::Read(void* pDest, vlong const nBytesToRead)
{
	DWORD dwBytesRead = 0;

	// if file not opened, fail
	if( hFile == INVALID_HANDLE_VALUE ) return VERROR_VFS_NOFILEOPENED;

	// read data
	ReadFile( hFile, pDest, nBytesToRead, &dwBytesRead, 0 );

	if( dwBytesRead != nBytesToRead )
	{
		// return error
		return VERROR_VFS_READFAILED;
	}
	else 
	{
		return VOK;
	}
}


VRESULT VFileStream::Write(const void* pSource, vulong const nBytesToWrite)
{
	DWORD dwBytesWritten = 0;

	WriteFile( hFile, pSource, nBytesToWrite, &dwBytesWritten, 0 );

	// if write failed
	if( dwBytesWritten != nBytesToWrite )
	{
		// return error
		return VERROR_VFS_WRITEFAILED;
	}
	else
	{
		return VOK;
	}
}

void VFileStream::SetPos(EAnchor nFromWhere, StreamPos nDiff)
{	
	DWORD dwMethod = 0;

	switch( nFromWhere )
	{
	case begin:
		dwMethod = FILE_BEGIN;
		break;
	case end:
		dwMethod = FILE_END;
		break;
	case current:
		dwMethod = FILE_CURRENT;
		break;
	default:
		return;
	}

	SetFilePointer( hFile, nDiff, 0, dwMethod );
}

IVStream::StreamPos VFileStream::GetPos()
{
	return SetFilePointer(hFile, 0, 0, FILE_CURRENT);
}

void VFileStream::Close()
{
	// if a file is opened
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// close it
		if( !CloseHandle( hFile ) )
		{
			// throw error
			V3D_THROW(VException, "could not close file");
		}

		hFile = INVALID_HANDLE_VALUE;
	}
}

