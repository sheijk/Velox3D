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
	typedef VPointer<IVAccessRights>::SharedPtr SharedAccessRightsPtr;

private:
	typedef std::list<FilePtr> FileList;
	typedef std::list<DirPtr> DirList;

	std::string m_strName;
	std::string m_strPath;
	std::string m_strTypeId;
	std::string m_strSource;

	SharedAccessRightsPtr m_pAccessRights;

	FileList m_Files;
	DirList m_Dirs;

public:
	VDirectory();
	VDirectory(
		std::string in_strName, 
		std::string in_strTypeId,
		std::string in_strSource,
		SharedAccessRightsPtr in_pAccessRights);

	~VDirectory();

	virtual VStringRetVal GetName() const;
	virtual VStringRetVal GetSource() const;
	virtual AccessRightsPtr GetAccessRights() const;

	virtual DirIterRange SubDirs();
	virtual ConstDirIterRange SubDirs() const;
	virtual FileIterRange Files();
	virtual ConstFileIterRange Files() const;

	virtual IVDirectory& CreateSubdir(
		VStringParam in_strName,
		const VAccessRightsFlags& in_AccessRights);

	virtual void DeleteSubdir(VStringParam in_strName);

	virtual void CreateFile(
		VStringParam in_strName,
		const VAccessRightsFlags& in_AccessRights);

	virtual void DeleteFile(VStringParam in_strName);

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
