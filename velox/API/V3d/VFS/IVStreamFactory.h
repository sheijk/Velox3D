//TODO: correct file guard
#ifndef V3D_IVStreamFactory_H
#define V3D_IVStreamFactory_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVOfflineStream.h>
#include <v3d/VFS/VFlags.h>
#include <v3d/Core/VNamedObject.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * A factory for streams. Used for seperating the creation of streams
 * from the rest of the file system.
 */
class IVStreamFactory : public VNamedObject
{
public:
	/** c'tor, registers the factory to the object registry */
	IVStreamFactory(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent) {};

	virtual ~IVStreamFactory() {};

	/** pointer type for returning offline streams */
	typedef VPointer<IVOfflineStream>::SharedPtr OfflineStreamPtr;

	/** creates a stream which directly accesses files */
	virtual OfflineStreamPtr CreateFileStream(
		VStringParam in_strName, 
		VCreationFlags in_OpenMode,
		VAccessModeFlags in_Access) = 0;

	/** creates a stream which automatically reserves as much data as is
		required in memory */
	virtual OfflineStreamPtr CreateMemoryStream(
		IVStream::ByteCount in_nInitialSize = 0) = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVStreamFactory_H
