#ifndef VRESOURCEMANAGERIMPL_H
#define VRESOURCEMANAGERIMPL_H

// disable a disturbing stl warning in vc6
#pragma warning( disable: 4786 )

#include <Vfs/VResourceInfo.h>

#include <Core/vtypes.h>
#include <map>

class IVFileStream;
class VDir;

//! hidden implementation of VResourceManager
class VResourceManagerIm
{
private:
	typedef std::map< std::string, VResourceInfo > ResourceMap;

	bool MountOneResource(std::string strPathAndName, std::string strDest, vint16 nFlags);

	ResourceMap m_Resources;

public:
	VResourceManagerIm();
	virtual ~VResourceManagerIm();

	IVFileStream* Open(const std::string & strName, const vint16 nFlags);

	void Mount(const std::string & strDir, const std::string & strPath, vint16 nFlags);

	VDir GetDir(std::string strDirName);
};

// restore default behaviour for warning
//#pragma warning( default: 4786 )

#endif // #ifndef VRESOURCEMANAGERIMPL_H
