#pragma warning( disable: 4786 )

#include <Vfs/VFileTools.h>

#include <fstream>
#include <windows.h>

using namespace std;

vbool IsValidFile( std::string strName )
{
	DWORD attr = 0;

	attr = GetFileAttributes( strName.c_str() );

	if( attr == 0xFFFFFFFF ) return false;

	if( attr & FILE_ATTRIBUTE_DIRECTORY ) return false;
	else return true;

	/*
	// try to open file
	ifstream file( strName.c_str() );

	// if file could be opened return true
	if( file )
	{
		return true;
	}
	// otherwise return false
	else return false;
	*/
}

vbool IsValidDir( std::string strName )
{
	DWORD attr = 0;

	attr = GetFileAttributes( strName.c_str() );

	if( attr == 0xFFFFFFFF ) return false;

	if( attr & FILE_ATTRIBUTE_DIRECTORY ) return true;
	else return false;
}

void AdjustSlashesInPath( std::string& strPath )
{
	for( int n = 0; n < strPath.length(); n++ )
	{
		if( strPath[n] == '\\' ) strPath[n] = '/';
	}
}

void DividePathAndFileName( const std::string& strFileAndPath, std::string& strPath, std::string& strFileName )
{
	string pathandfile = strFileAndPath;
	string::size_type size;

	AdjustSlashesInPath( pathandfile );
	size = pathandfile.find_last_of( "/" );

	if( size == string::npos )
	{
		strPath = "";
	}
	else
	{
		strPath = pathandfile.substr( 0, size );
	}

	strFileName = pathandfile.substr( size + 1 );
}

void ListDirContent( const std::string strDir, VStringList& list )
{
	WIN32_FIND_DATA w32finddat;
	HANDLE findhandle;
	bool bFound = true;
	string str;
	string dir = strDir;

	if( dir.size() <= 0 ) return;

	AdjustSlashesInPath(dir);

	// append ending slash if necessary
	if( dir[dir.size()-1] != '/' ) dir += "/";

	// find first file in dir
	findhandle = FindFirstFile( string(dir + "*").c_str(), &w32finddat );

	// if no file was found
	if( INVALID_HANDLE_VALUE == findhandle ) return;

	// for each found file
	while( bFound )
	{
		str = w32finddat.cFileName;

		// add file to list
		if( str != "." && str != ".." )
		{
			list.insert( str );
		}

		// search next file		
		bFound = FindNextFile( findhandle, &w32finddat );
	}

	FindClose(findhandle);	
}
