/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSimpleVfs_H
#define V3D_VSimpleVfs_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/VFS/IVFileSystem.h>

#include "VDirectory.h"

#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
//TODO: insert documentation here
 */
class VSimpleVfs : public IVFileSystem
{
	// the file structure tree
	VSharedPtr<VDirectory> m_pRootDirSP;

	virtual void MountFromXML(VStringParam in_strFileName);
    
public:
	VSimpleVfs(
		VStringParam in_strName, 
		VStringParam in_strCfgFile,
		VNamedObject* in_pParent = 0);

	virtual ~VSimpleVfs();

	virtual FileStreamPtr OpenFile(
		VStringParam in_strPathAndName,
		VAccessModeFlags in_Access);

	virtual std::string GetWorkingDir() const;
	virtual void SetWorkingDir(const std::string& in_strNewWorkingDir);

	vbool ExistsFile(const std::string& in_strPath) const;

	// removed from IVFileSystem
	virtual IVDirectory* GetDir(VStringParam in_strDir);

	virtual vbool ExistsDir(VStringParam in_strDir) const;
	virtual vbool ExistsFile(VStringParam in_strFile) const;
	virtual vbool Exists(VStringParam in_strFSObject) const;

	virtual void DumpFileSystem() const;
	virtual void DumpDir(vfs::IVDirectory& dir, const std::string& prefix) const;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSimpleVfs_H

