#include "VFileStream.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VException.h>

#include <sstream>
#include <iostream>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------
using namespace vfs;

/*!
	\param strFileName name of file to be opened
	\param nAccess write_access for writing, read_access for reading
	\param nCreation createion mode. createnew, createalways, openexisting, openalways, truncate

	Creates the stream and opens a file
*/
VFileStream::VFileStream(
	VStringParam in_strFileName, 
	VAccessModeFlags in_nAccess, 
	VCreationFlags in_nCreation )
{
	m_hFile = INVALID_HANDLE_VALUE;
	m_nAccessMode = 0;
	m_nCreationMode = 0;
	m_nFilePos = 0;
	m_bConnected = false;
	m_strFileName = in_strFileName;
		
	//TODO: vfs exception klasse benutzen
	if( in_nAccess == 0 ) V3D_THROW( VException, "invalid file open mode" );

	// set acces flags
	if( in_nAccess & VReadAccess ) m_nAccessMode |= GENERIC_READ;
	if( in_nAccess & VWriteAccess ) m_nAccessMode |= GENERIC_WRITE;

	// set creation mode
	switch( in_nCreation )
	{
	case VCreateNew:
		m_nCreationMode = CREATE_NEW;
		break;
	case VCreateAlways:
		m_nCreationMode = CREATE_ALWAYS;
		break;
	case VOpenExisting:
		m_nCreationMode = OPEN_EXISTING;
		break;
	case VOpenAlways:
		m_nCreationMode = OPEN_ALWAYS;
		break;
	case VTruncate:
		m_nCreationMode = TRUNCATE_EXISTING;
		break;
	default:
		ostringstream str;
		str << "invalid file creation mode for file \"";
		str << in_strFileName;
		str << "\" :";
		str << in_nCreation << endl;

		//TODO: durch vfs exception ersetzen
		V3D_THROW( VException, str.str().c_str() );
	}

	// create legal op class
	vbool bReadAccess =  in_nAccess & VReadAccess;
	vbool bWriteAccess = in_nAccess & VWriteAccess;

	// open file
	Connect();

	DWORD filesize = GetFileSize( m_hFile, 0 );
}

/*!
	automatically closes file if opened
*/
VFileStream::~VFileStream()
{
	// no exception should escape a destructor
	try
	{
		Close();
	}
	catch(VException e)
	{
		//TODO: debug message senden
		//vout << "Warning: error while closing file" << endl;
	}
}


IVStream::ByteCount VFileStream
	::Read(void* out_pDest, ByteCount in_pBytesToRead)
{
	DWORD dwBytesRead = 0;

	// if file not opened, fail
	if( !IsConnected() || m_hFile == INVALID_HANDLE_VALUE ) 
	{
		V3D_THROW(VException, "file not opened");
	}

	// read data
	ReadFile( m_hFile, out_pDest, in_pBytesToRead, &dwBytesRead, 0 );

	//if( dwBytesRead != in_pBytesToRead )
	//{
	//	V3D_THROW(VException, "read error");
	//}

	return static_cast<ByteCount>(dwBytesRead);
}


void VFileStream::Write(const void* in_pSource, ByteCount in_nBytesToWrite)
{
	DWORD dwBytesWritten = 0;

	WriteFile( m_hFile, in_pSource, in_nBytesToWrite, &dwBytesWritten, 0 );

	// if write failed
	if( dwBytesWritten != in_nBytesToWrite )
	{
		//TODO: vfs exc.
		V3D_THROW(VException, "could not write");
	}
}

void VFileStream::SetPos(Anchor in_Anchor, ByteCount in_nDistance)
{	
	DWORD dwMethod = 0;

	switch( in_Anchor )
	{
	case Begin:
		dwMethod = FILE_BEGIN;
		break;
	case End:
		dwMethod = FILE_END;
		break;
	case CurrentPos:
		dwMethod = FILE_CURRENT;
		break;
	default:
		return;
	}

	SetFilePointer( m_hFile, in_nDistance, 0, dwMethod );
}

IVStream::StreamPos VFileStream::GetPos() const
{
	return SetFilePointer(m_hFile, 0, 0, FILE_CURRENT);
}

IVStream::LegalOpsPtr VFileStream::GetLegalOps() const
{
	//TODO: schoener machen :)
	return NULL;
}

void VFileStream::Close()
{
	// close file
	Disconnect();

	// forget which file we opened
	m_strFileName.clear();
	m_nAccessMode = 0;
	m_nCreationMode = 0;
	m_nFilePos = 0;
	m_bConnected = true;
}

void VFileStream::Disconnect()
{
	if( IsConnected() )
	{
		// if a file is opened
		if( m_hFile != INVALID_HANDLE_VALUE )
		{
			// save file position
			m_nFilePos = GetPos();

			// close it
			if( !CloseHandle( m_hFile ) )
			{
				// throw error
				//TODO: vfs exc.
				V3D_THROW(VException, "could not close file");

			}

			m_hFile = INVALID_HANDLE_VALUE;
		}
	}

	m_bConnected = false;
}

void VFileStream::Connect()
{
	if( !m_bConnected )
	{
		// open the file
		m_hFile = CreateFile( 
			m_strFileName.c_str(), 
			m_nAccessMode,
			0, 
			0, 
			m_nCreationMode, 
			FILE_ATTRIBUTE_NORMAL, 
			0 );

		// if file could not be opened
		if( m_hFile == INVALID_HANDLE_VALUE )
		{
			// throw error
			vchar* pMsgBuf;

			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&pMsgBuf,
				0,
				NULL);

			// copy to a VString
			VString str(pMsgBuf);

			// release it
			LocalFree(pMsgBuf);

			//TODO: vfs exc.
			V3D_THROW( VException, 
				VString("could not open file: \"") 
				+ m_strFileName.c_str() + "\"" );
		}	

		SetFilePointer( m_hFile, m_nFilePos, 0, FILE_BEGIN );
	}

	m_bConnected = true;
}

vbool VFileStream::IsConnected() const
{
	return m_bConnected;
}

//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
