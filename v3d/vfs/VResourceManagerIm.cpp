#include "VResourceManagerIm.h"
//--------------------------------------------------------------------
#pragma warning( disable: 4786 )

#include <VFS/VFileStream.h>
#include <Vfs/VOpenFlags.h>
#include <Error/VException.h>
#include <Vfs/VFileTools.h>
#include <Vfs/VStringList.h>
#include <fstream>

//fix
class VDir
{

};

using namespace std;

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

VResourceManagerIm::VResourceManagerIm() :
	m_Resources()	
{

}

VResourceManagerIm::~VResourceManagerIm()
{

}

/*************************************************************
Gibt ein VDir Objekt zurück, dass das in strDirName angegebene
Verzeichnis repräsentiert
*************************************************************/
VDir VResourceManagerIm::GetDir(std::string strDirName)
{
	return VDir();
}

vbool IsValidArchive( std::string strName )
{
	return false;
}

/*************************************************************
Mountes einen Teil des echten Dateisystems ins virtual file system
Es können Verzeichnisse, Archive sowie einzelne Dateien 
gemountet werden
*************************************************************/
void VResourceManagerIm::Mount(const std::string & strDest, const std::string & strPath, vint16 nFlags) 
{
	string path = strPath;

	string str, str2;

	// if an archive shall be mounted
	if( IsValidArchive( strPath ) )
	{
		// for each file
		// add it to list
	}
	// if a single file shall be mounted
	else if( IsValidFile( strPath) )
	{	
		// mount file
		MountOneResource(strPath,strDest,nFlags);
	}
	// if a directory shall be mounted
	else if( IsValidDir( strPath ) )
	{
		VStringList reslist;

		AdjustSlashesInPath(path);
		if( path[path.size()-1] != '/' ) path += '/';

		// list dir content
		ListDirContent(path, reslist);

		// mount all resources from mount list
		for( VStringList::iterator it = reslist.begin(); it != reslist.end(); ++it )
		{
			str2 = path + *it;
			str = *it;
			MountOneResource( path + *it, strDest + *it, nFlags );
		}
	}

}

/*************************************************************
Gibt einen VIFileStream, der die angegebene Resource geöffnet
hat zurück (sollte vielleicht auf createfilestream umbenannt
werden ?)
*************************************************************/
IVFileStream* VResourceManagerIm::Open(const std::string & strName, const vint16 nFlags)
{
	ELocationType type = ltNone;
	IVFileStream* stream = 0;

	// check if resource exists
	ResourceMap::iterator it = m_Resources.find(strName);

	// if resource exists
	if( it != m_Resources.end() )
	{
		// check access rights
		if( it->second.m_bReadOnly && nFlags & v3d_vfs::write_access )
		{
			return 0;
		}

		// get resource type
		type = it->second.m_Location;

		// create data loader
		switch( type )
		{
		case ltFile:
			// try to open data
			try
			{
				stream = new VFileStream(it->second.m_strPathAndName, nFlags, VFileStream::openexisting);
			}
			// if stream could not be opened
			catch( VException e )
			{
				return 0;
			}
			break;

		// location type is not supported
		default:
			return 0;
		}

		// add data processor

		// return the stream
		return stream;
	}
	// if resource does not exist, fail
	else return 0;

}

/*************************************************************
*************************************************************/
bool VResourceManagerIm::MountOneResource(std::string strPathAndName, std::string strDest, vint16 nFlags)
{
	// if mount dest has not already been mounted
	ResourceMap::iterator it = m_Resources.find( strDest );

	// if resource doesnt already exist
	if( it == m_Resources.end() )
	{
		// check if res is valid

		// create resource info
		VResourceInfo info;
		info.m_Location = ltFile;
		info.m_strPathAndName = strPathAndName;
		info.m_bReadOnly = nFlags & v3d_vfs::mount_readonly;
		
		// add it to resource map
		m_Resources.insert( ResourceMap::value_type( strDest, info ) );

		return true;
	}
	// if resource already exists, fail
	else return false;
}
