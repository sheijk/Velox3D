#include "VResourceManager.h"
//-----------------------------------------------------------
#include "VResourceManagerIm.h"

#pragma warning( disable: 4786 )

class VDir;


VResourceManager::VResourceManager()
{
	impl = new VResourceManagerIm();
}

VResourceManager::VResourceManager(const VResourceManager &cp)
{
	impl = new VResourceManagerIm( *(cp.impl) );
}

void VResourceManager::operator=(const VResourceManager &cp)
{
	*impl = *(cp.impl);
}

VResourceManager::~VResourceManager()
{
	delete impl;
}

//fix
class VDir 
{
};

/*************************************************************
Gibt ein VDir Objekt zur�ck, dass das in strDirName angegebene
Verzeichnis repr�sentiert
*************************************************************/
VDir VResourceManager::GetDir(std::string strDirName)
{
	return impl->GetDir( strDirName );
}

/*************************************************************
Mountes einen Teil des echten Dateisystems ins virtual file system
Es k�nnen Verzeichnisse, Archive sowie einzelne Dateien 
gemountet werden
*************************************************************/
void VResourceManager::Mount(const std::string & strDir, const std::string & strPath, vint16 nFlags) 
{
	impl->Mount( strDir, strPath, nFlags );
}

/*************************************************************
Gibt einen VIFileStream, der die angegebene Resource ge�ffnet
hat zur�ck (sollte vielleicht auf createfilestream umbenannt
werden ?)
*************************************************************/
IVFileStream* VResourceManager::Open(const std::string & strName, const vint16 nFlags)
{
	return impl->Open( strName, nFlags );
}

