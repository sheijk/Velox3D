#ifndef V3D_VFileDataProvider_H
#define V3D_VFileDataProvider_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVDataProvider.h>
#include <v3d/VFS/IVStreamFactory.h>

#include "VDirectory.h"

#include <boost/filesystem/convenience.hpp>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
//TODO: insert documentation here
*/
class VFileDataProvider : public IVDataProvider
{
	std::string m_strType;
	static IVStreamFactory* s_pStreamFact;

	static IVStreamFactory* GetStreamFactory();

	static void AddDirContent(
		VDirectory& io_Dir, 
		boost::filesystem::path in_Dir);

public:
	VFileDataProvider();
	virtual ~VFileDataProvider();

	virtual VStringRetVal GetId() const;
	virtual StreamPtr OpenFile(
		VStringParam in_strSource, 
		VAccessModeFlags in_Access);

	virtual DirPtr CreateMountedDir(const VMountOptions& in_MountOptions);
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VFileDataProvider_H
