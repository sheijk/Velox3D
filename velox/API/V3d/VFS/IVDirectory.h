#ifndef V3D_IVDirectory_H
#define V3D_IVDirectory_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VIterator.h>
#include <v3d/VFS/IVFileSysObject.h>
#include <v3d/VFS/IVFile.h>

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

	typedef VBirectionalIterator<IVDirectory> DirIter;
	typedef VBirectionalIterator<IVFile> FileIter;

	typedef VBirectionalIterator<const IVDirectory> ConstDirIter;
	typedef VBirectionalIterator<const IVFile> ConstFileIter;

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
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDirectory_H
