//TODO: correct file guard
#ifndef V3D_IVFileSystemObject_H
#define V3D_IVFileSystemObject_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------
class IVAccessRights;

/**
 * Basic infos for files and directories
 */
class IVFileSystemObject
{
public:
	virtual ~IVFileSystemObject() {}

	typedef const IVAccessRights* AccessRightsPtr;

	virtual VStringRetVal GetName() const = 0;
	virtual VStringRetVal GetPath() const = 0;
	virtual AccessRightsPtr GetAccessRights() const = 0;
};

inline bool operator==(const IVFileSystemObject& pA, const IVFileSystemObject& pB)
{
	return pA.GetName() == pB.GetName() && pA.GetPath() == pB.GetPath();
}
//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVFileSystemObject_H
