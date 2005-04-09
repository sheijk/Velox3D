#ifndef V3D_VSimpleVfs_H
#define V3D_VSimpleVfs_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVFileSystem.h>

#include "VDirectory.h"
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

    void ParseInitFile();
public:
	VSimpleVfs(
		VStringParam in_strName, 
		VStringParam in_strCfgFile,
		VNamedObject* in_pParent = 0);

	virtual ~VSimpleVfs();

	virtual FileStreamPtr OpenFile(
		VStringParam in_strPathAndName,
		VAccessModeFlags in_Access);

	virtual IVDirectory* GetDir(VStringParam in_strDir);

	virtual vbool ExistsDir(VStringParam in_strDir);
	virtual vbool ExistsFile(VStringParam in_strFile);
	virtual vbool Exists(VStringParam in_strFSObject);
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSimpleVfs_H
