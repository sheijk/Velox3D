/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VFILEDATAPROVIDER_H
#define V3D_VFILEDATAPROVIDER_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/VFS/IVDataProvider.h>
#include <V3d/VFS/IVStreamFactory.h>
//-----------------------------------------------------------------------------
#include "VDirectory.h"
//-----------------------------------------------------------------------------
#include <boost/filesystem/convenience.hpp>
#include <string>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
//TODO: insert documentation here
*/
class VFileDataProvider : public IVDataProvider
{
	std::string m_strType;
	static IVStreamFactory* s_pStreamFact;

	static IVStreamFactory* GetStreamFactory();

	void AddDirContent(
		VDirectory& io_Dir, 
		boost::filesystem::path in_Dir,
		VDirectory::SharedAccessRightsPtr in_pAR);

public:
	VFileDataProvider();
	virtual ~VFileDataProvider();

	virtual VStringRetVal GetId() const;
	virtual StreamPtr OpenFile(
		VStringParam in_strSource, 
		VAccessModeFlags in_Access);

	virtual DirPtr CreateMountedDir(
		IVDirectory* in_pParent, const VMountOptions& in_MountOptions);

	virtual vbool IsDirectory(VStringParam in_strPossibleDir);
	virtual vbool IsFile(VStringParam in_strPossibleFile);

	virtual DirPtr CreateDir(const VMountOptions& in_Options);
	virtual void DeleteDir(VStringParam in_strDir);
	virtual FilePtr CreateFile(const VMountOptions& in_Options);
	virtual void DeleteFile(VStringParam in_strSource);
	virtual void UpdateDir(const std::string& path, VDirectory* io_pDir);
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VFILEDATAPROVIDER

