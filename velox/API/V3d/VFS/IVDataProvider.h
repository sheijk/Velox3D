#ifndef V3D_IVDataProvider_H
#define V3D_IVDataProvider_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/VFlags.h>
#include <v3d/VFS/IVOfflineStream.h>
#include <v3d/VFS/VMountOptions.h>
#include <v3d/VFS/IVDirectory.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * A "plugin" that can create a stream from a xml file descriptions. 
 * Registers itself to the vfs, handles all file descriptions with 
 * a specific "type" attribute
 */
class IVDataProvider
{
public:
	virtual ~IVDataProvider() {}

	typedef VPointer<IVOfflineStream>::SharedPtr StreamPtr;
	typedef VPointer<IVDirectory>::SharedPtr DirPtr;

	/** returns the type id */
	virtual VStringRetVal GetId() const = 0;

	/** opens a (virtual) file */
	virtual StreamPtr OpenFile(
		VStringParam in_strSource, 
		VAccessModeFlags in_Access) = 0;

	/** creates a dir from mount info */
	virtual DirPtr CreateMountedDir(const VMountOptions& in_MountOptions) = 0;

	// create files (?)
};

//-----------------------------------------------------------------------------
} // namespace vfs 
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDataProvider_H
