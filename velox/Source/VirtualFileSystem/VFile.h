#ifndef V3D_VFile_H
#define V3D_VFile_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVFile.h>
#include <v3d/Core/Wrappers/VString.h>

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
	virtual VStringRetVal GetPath() const;
	virtual AccessRightsPtr GetAccessRights() const;

	/** @see IVFile#Open */
	virtual FileStreamPtr Open(VAccessModeFlags in_Access) const;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VFile_H
