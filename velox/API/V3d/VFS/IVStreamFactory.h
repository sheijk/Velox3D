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
//TODO: insert documentation here
*/
class IVStreamFactory : public VNamedObject
{
public:
	IVStreamFactory(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent) {};

	virtual ~IVStreamFactory() {};

	typedef VPointer<IVOfflineStream>::SharedPtr OfflineStreamPtr;

	virtual OfflineStreamPtr CreateFileStream(
		VStringParam in_strName, 
		VCreationFlags in_OpenMode,
		VAccessModeFlags in_Access) = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVStreamFactory_H
