#ifndef FILETOOLS_H
#define FILETOOLS_H

#pragma warning(disable: 4786)

#include <Core/vtypes.h>
#include <Vfs/VStringList.h>
#include <string>

// returns true if strName is an existing file
vbool IsValidFile( std::string strName );

// returns true if strName is an existing directory
vbool IsValidDir( std::string strName );

// replaces all \ with /
void AdjustSlashesInPath( std::string& strPath );

// returns path and file name
void DividePathAndFileName( const std::string& strFileAndPath, std::string& strPath, std::string& strFileName );

// add all files of a dir to list
void ListDirContent( const std::string strDir, VStringList& list );

#endif