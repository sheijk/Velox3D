#ifndef V3D_VFSUTILS_H
#define V3D_VFSUTILS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVFileSysObject.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

	class VCompareFSOName
	{
		VString m_strDirName;
	public:
		VCompareFSOName(std::string name)
		{
			m_strDirName = VString(name.c_str());
		}

		bool operator()(IVFileSystemObject& dir)
		{
			return dir.GetName() == m_strDirName;
		}
	};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VFSUTILS_H
