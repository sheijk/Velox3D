#ifndef V3D_IVDataProvider_H
#define V3D_IVDataProvider_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/VFlags.h>
#include <v3d/VFS/IVOfflineStream.h>
#include <v3d/VFS/VMountOptions.h>
#include <v3d/VFS/IVDirectory.h>
#include <v3d/VFS/IVFile.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

// fix some of the troubles caused by windows.h
#undef CreateFile

/**
 * A "plugin" that can create a stream from an xml file descriptions. 
 * Registers itself to the vfs, handles all file descriptions with 
 * a specific "type" attribute
 */
class IVDataProvider
{
public:
	virtual ~IVDataProvider() {}

	typedef VPointer<IVBufferStream>::SharedPtr StreamPtr;
	typedef VPointer<IVDirectory>::SharedPtr DirPtr;
	typedef VPointer<IVFile>::SharedPtr FilePtr;

	/** returns the type id */
	virtual VStringRetVal GetId() const = 0;

	/** opens a (virtual) file */
	virtual StreamPtr OpenFile(
		VStringParam in_strSource, 
		VAccessModeFlags in_Access) = 0;

	/** creates a dir from mount info */
	virtual DirPtr CreateMountedDir(const VMountOptions& in_MountOptions) = 0;

	virtual vbool IsDirectory(VStringParam in_strPossibleDir) = 0;
	virtual vbool IsFile(VStringParam in_strPossibleFile) = 0;

	// create files (?)
	virtual DirPtr CreateDir(const VMountOptions& in_Options) = 0;
	virtual void DeleteDir(VStringParam in_strDir) = 0;
	virtual FilePtr CreateFile(const VMountOptions& in_Options) = 0;
	virtual void DeleteFile(VStringParam in_strSource) = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs 
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDataProvider_H
