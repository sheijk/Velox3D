/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VFile_H
#define V3D_VFile_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/VFS/IVFile.h>
#include <V3d/Core/Wrappers/VString.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Information about a mounted file
 */
class VFile : public IVFile
{
public:
	typedef VPointer<IVAccessRights>::SharedPtr SharedAccessRightsPtr;

private:
	std::string m_strName;
	std::string m_strPath;
	std::string m_strSource;
	std::string m_strTypeId;
	
	SharedAccessRightsPtr m_pAccessRights;

public:
	struct CreationInfo
	{
		CreationInfo() {}
		std::string name, type, source;
		SharedAccessRightsPtr pAccRights;
	};

	VFile();
	VFile(const CreationInfo& description);

	virtual ~VFile();

	virtual VStringRetVal GetName() const;
	virtual VStringRetVal GetSource() const;
	virtual AccessRightsPtr GetAccessRights() const;

	/** @see IVFile#Open */
	virtual FileStreamPtr Open(VAccessModeFlags in_Access) const;

	virtual void Clear();
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VFile_H

