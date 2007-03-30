/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDirectory_H
#define V3D_VDirectory_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/SmartPtr/VGuards.h>
#include <V3d/VFS/IVDirectory.h>

#include <string>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------
class IVDataProvider;

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
	IVDataProvider* MyDataProvider() const;

	void Update() const;

	typedef std::list<FilePtr> FileList;
	typedef std::list<DirPtr> DirList;

	IVDirectory* m_pParent;

	std::string m_strName;
	std::string m_strPath;
	std::string m_strTypeId;
	std::string m_strSource;

	SharedAccessRightsPtr m_pAccessRights;

	FileList m_Files;
	DirList m_Dirs;

	IVDirectory* GetSubDir(const VString& name);
	IVFile* GetFile(const VString& name);
public:
	VDirectory();
	VDirectory(
		IVDirectory* in_pParent,
		std::string in_strName, 
		std::string in_strTypeId,
		std::string in_strSource,
		SharedAccessRightsPtr in_pAccessRights);

	~VDirectory();

	virtual VStringRetVal GetName() const;
	virtual VStringRetVal GetSource() const;
	virtual AccessRightsPtr GetAccessRights() const;

	virtual DirIter SubDirs();
	virtual ConstDirIter SubDirs() const;
	virtual FileIter Files();
	virtual ConstFileIter Files() const;

	virtual IVDirectory* GetParent();
	virtual const IVDirectory* GetParent() const;

	virtual std::string GetQualifiedName() const;

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

