/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VFSUTILS_H
#define V3D_VFSUTILS_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/VFS/IVFileSysObject.h>

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

