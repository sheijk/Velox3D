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
	VDirectory* m_pRootDir;
	DirectoryPtr m_pRootDirSP;

	// the data provider pool

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

};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSimpleVfs_H
