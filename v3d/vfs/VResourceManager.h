#ifndef VRESOURCEMANAGER_H
#define VRESOURCEMANAGER_H
//------------------------------------------------------------
#pragma warning( disable: 4786 )

#include <Vfs/IVFileStream.h>
#include <Vfs/VOpenFlags.h>

#include <Core/vtypes.h>
#include <string>
#include <map>

class VDir;
class VResourceManagerIm;

//! manages a virtual file system
class VResourceManager 
{
private:
	void operator=(const VResourceManager & cp);
	VResourceManager( const VResourceManager& cp );

	VResourceManagerIm* impl;

public:	
	//! constructor, should become private
	VResourceManager();

	//! destructor, will become private
	~VResourceManager();

	//! open a resource
	IVFileStream* Open(const std::string & strName, const vint16 nFlags);

	// mount files/dirs/archives to file system
	void Mount(const std::string & strDest, const std::string & strPath, vint16 nFlags);

	// returns a specific directory
	VDir GetDir(std::string strDirName);
};

//------------------------------------------------------------
#endif //VRESOURCEMANAGER_H