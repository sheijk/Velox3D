#ifndef V3D_VDirectory_H
#define V3D_VDirectory_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/VFS/IVDirectory.h>

#include <string>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Information about a directory, it's files and subdirs
 */
class VDirectory : public IVDirectory
{
public:
	typedef VPointer<IVFile>::SharedPtr FilePtr;
	typedef VPointer<IVDirectory>::SharedPtr DirPtr;

private:
	typedef std::list<FilePtr> FileList;
	typedef std::list<DirPtr> DirList;

	std::string m_strName;
	std::string m_strPath;
	VPointer<IVAccessRights>::SharedPtr m_pAccessRights;

	FileList m_Files;
	DirList m_Dirs;

public:
	VDirectory();
	VDirectory(std::string in_strName, std::string in_strPath);
	~VDirectory();

	virtual VStringRetVal GetName() const;
	virtual VStringRetVal GetPath() const;
	virtual AccessRightsPtr GetAccessRights() const;

	virtual DirIterRange SubDirs();
	virtual ConstDirIterRange SubDirs() const;
	virtual FileIterRange Files();
	virtual ConstFileIterRange Files() const;

	/** add a subdir */
	void AddSubdir(DirPtr in_pSubdir);

	/** add a file */
	void AddFile(FilePtr in_pFile);
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDirectory_H
