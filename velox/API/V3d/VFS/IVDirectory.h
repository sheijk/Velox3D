#ifndef V3D_IVDirectory_H
#define V3D_IVDirectory_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VIterator.h>
#include <v3d/VFS/IVFileSysObject.h>
#include <v3d/VFS/IVFile.h>
#include <v3d/VFS/VAccessRightsFlags.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Represents a directory. Use it to access sub dirs, files, 
 * create and delete files and subdirs
 */
class IVDirectory : public IVFileSystemObject
{
public:
	//TODO: documentation
	virtual ~IVDirectory() {};

	typedef VBidirectionalIterator<IVDirectory> DirIter;
	typedef VBidirectionalIterator<IVFile> FileIter;

	typedef VBidirectionalIterator<const IVDirectory> ConstDirIter;
	typedef VBidirectionalIterator<const IVFile> ConstFileIter;

	//TODO: in eigene Datei
	template<typename T> struct Range
	{
		Range(T b, T e) : Begin(b), End(e) {}

        T Begin, End;
	};
	
	typedef Range<DirIter> DirIterRange;
	typedef Range<FileIter> FileIterRange;

	typedef Range<ConstDirIter> ConstDirIterRange;
	typedef Range<ConstFileIter> ConstFileIterRange;

	/** get sub directory iterators */
	virtual DirIterRange SubDirs() = 0;
	virtual ConstDirIterRange SubDirs() const = 0;

	/** get file iterators */
	virtual FileIterRange Files() = 0;
	virtual ConstFileIterRange Files() const = 0;

	// Create/Delete File/Dir
	/** create a sub directory */
	virtual IVDirectory& CreateSubdir(
		VStringParam in_strName,
		const VAccessRightsFlags& in_AccessRights) = 0;

	/** delete a subdirectory */
	virtual void DeleteSubdir(VStringParam in_strName) = 0;

	/** create a file */
	virtual void CreateFile(
		VStringParam in_strName,
		const VAccessRightsFlags& in_AccessRights) = 0;

	/** delete file */
	virtual void DeleteFile(VStringParam in_strName) = 0;

	/** create a file */
	//virtual IVFile* CreateFile(
	//	VStringParam in_strName,
	//	AccessRightsPtr in_pAccessRights) = 0;

	/** delete a file */
	//virtual void DeleteFile(VStringParam in_strName) = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDirectory_H
