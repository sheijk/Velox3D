#ifndef V3D_VStreamFactory_H
#define V3D_VStreamFactory_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVStreamFactory.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
//TODO: insert documentation here
*/
class VStreamFactory : public IVStreamFactory
{
public:
	VStreamFactory(VStringParam in_strName);
	virtual ~VStreamFactory();

	virtual OfflineStreamPtr CreateFileStream(
		VStringParam in_strName, 
		VCreationFlags in_OpenMode,
		VAccessModeFlags in_Access);

	virtual OfflineStreamPtr CreateMemoryStream(
		IVStream::ByteCount in_nInitialSize = 0);
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VStreamFactory_H
